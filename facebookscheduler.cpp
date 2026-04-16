#include "FacebookScheduler.h"
#include <curl/curl.h>
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

const std::string CERT_PATH = "C:/Users/himak/OneDrive/Documents/Fbschedular/3rdparty/curl-8.16.0_3-win64-mingw/bin/curl-ca-bundle.crt";

FacebookScheduler::FacebookScheduler(const std::string& pageId, const std::string& accessToken)
    : m_pageId(pageId), m_accessToken(accessToken) {}

size_t FacebookScheduler::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<FacebookPage> FacebookScheduler::fetchManagedPages(const std::string& token) {
    std::vector<FacebookPage> pages;
    CURL* curl = curl_easy_init();
    if (!curl) return pages;

    std::string response_string;
    std::string url = "https://graph.facebook.com/v20.0/me/accounts?access_token=" + token;

    curl_easy_setopt(curl, CURLOPT_CAINFO, CERT_PATH.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);

    CURLcode res = curl_easy_perform(curl);
    
    if (res == CURLE_OK) {
        try {
            json res_json = json::parse(response_string);
            if (res_json.contains("data")) {
                for (const auto& item : res_json["data"]) {
                    FacebookPage page;
                    page.name = item.value("name", "");
                    page.id = item.value("id", "");
                    page.token = item.value("access_token", "");
                    pages.push_back(page);
                }
            }
        } catch (...) {}
    }

    if (pages.empty()) {
        response_string.clear();
        url = "https://graph.facebook.com/v20.0/me?access_token=" + token;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json res_json = json::parse(response_string);
                if (res_json.contains("name") && res_json.contains("id")) {
                    FacebookPage page;
                    page.name = res_json.value("name", "");
                    page.id = res_json.value("id", "");
                    page.token = token; 
                    pages.push_back(page);
                }
            } catch (...) {}
        }
    }

    curl_easy_cleanup(curl);
    return pages;
}

ApiResponse FacebookScheduler::scheduleVideo(const std::string& videoPath, const std::string& description, time_t publishTime) {
    CURL* curl = curl_easy_init();
    if (!curl) return {false, "Curl init failed"};

    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_CAINFO, CERT_PATH.c_str());

    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3600L); 
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 60L); 
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Expect:"); 
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string url = "https://graph-video.facebook.com/v19.0/" + m_pageId + "/videos";

    curl_mime* mime = curl_mime_init(curl);
    curl_mimepart* part;

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "access_token");
    curl_mime_data(part, m_accessToken.c_str(), CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "description");
    curl_mime_data(part, description.c_str(), CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "source");
    curl_mime_filedata(part, videoPath.c_str());

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "published");
    curl_mime_data(part, "false", CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "scheduled_publish_time");
    curl_mime_data(part, std::to_string(publishTime).c_str(), CURL_ZERO_TERMINATED);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    
    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    } else {
        response_string = "Curl error: " + std::string(curl_easy_strerror(res));
    }

    curl_slist_free_all(headers);
    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    
    return {res == CURLE_OK && http_code == 200, response_string};
}

ApiResponse FacebookScheduler::schedulePhoto(const std::string& photoPath, const std::string& caption, time_t publishTime) {
    CURL* curl = curl_easy_init();
    if (!curl) return {false, "Curl init failed"};

    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_CAINFO, CERT_PATH.c_str());
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 60L);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Expect:"); 
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string upload_url = "https://graph.facebook.com/v20.0/" + m_pageId + "/photos";
    curl_mime* mime = curl_mime_init(curl);
    curl_mimepart* part;

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "access_token");
    curl_mime_data(part, m_accessToken.c_str(), CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "published");
    curl_mime_data(part, "false", CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "source");
    curl_mime_filedata(part, photoPath.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, upload_url.c_str());
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);
    curl_mime_free(mime);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        curl_slist_free_all(headers);
        return {false, "Step 1 (Upload) failed: " + std::string(curl_easy_strerror(res))};
    }

    std::string photo_id;
    try {
        json res_json = json::parse(response_string);
        photo_id = res_json.value("id", "");
    } catch (const json::parse_error& e) {
        curl_slist_free_all(headers);
        return {false, "Failed to parse JSON from Facebook: " + response_string};
    }

    if (photo_id.empty()) {
        curl_slist_free_all(headers);
        return {false, "Photo upload succeeded but no ID was returned: " + response_string};
    }

    response_string.clear();
    curl = curl_easy_init();
    if (!curl) {
        curl_slist_free_all(headers);
        return {false, "Curl init failed for Step 2"};
    }

    curl_easy_setopt(curl, CURLOPT_CAINFO, CERT_PATH.c_str());
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 60L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    std::string feed_url = "https://graph.facebook.com/v20.0/" + m_pageId + "/feed";
    
    mime = curl_mime_init(curl);

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "message");
    curl_mime_data(part, caption.c_str(), CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "access_token");
    curl_mime_data(part, m_accessToken.c_str(), CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "published");
    curl_mime_data(part, "false", CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_name(part, "scheduled_publish_time");
    curl_mime_data(part, std::to_string(publishTime).c_str(), CURL_ZERO_TERMINATED);

    std::string attached_media_json = "[{\"media_fbid\":\"" + photo_id + "\"}]";
    part = curl_mime_addpart(mime);
    curl_mime_name(part, "attached_media");
    curl_mime_data(part, attached_media_json.c_str(), CURL_ZERO_TERMINATED);

    curl_easy_setopt(curl, CURLOPT_URL, feed_url.c_str());
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    res = curl_easy_perform(curl);
    long http_code = 0;
    
    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    } else {
        response_string = "Step 2 (Schedule) failed: " + std::string(curl_easy_strerror(res));
    }

    curl_mime_free(mime);
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return {res == CURLE_OK && http_code == 200, response_string};
}