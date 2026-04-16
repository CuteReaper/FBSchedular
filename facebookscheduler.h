#ifndef FACEBOOKSCHEDULER_H
#define FACEBOOKSCHEDULER_H

#include <string>
#include <ctime>
#include <vector>

struct ApiResponse {
    bool success;
    std::string message;
};

struct FacebookPage {
    std::string name;
    std::string id;
    std::string token;
};

class FacebookScheduler {
public:
    FacebookScheduler(const std::string& pageId, const std::string& accessToken);
    
    ApiResponse scheduleVideo(const std::string& videoPath, const std::string& description, time_t publishTime);
    ApiResponse schedulePhoto(const std::string& photoPath, const std::string& caption, time_t publishTime);

    static std::vector<FacebookPage> fetchManagedPages(const std::string& token);

private:
    std::string m_pageId;
    std::string m_accessToken;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif // FACEBOOKSCHEDULER_H