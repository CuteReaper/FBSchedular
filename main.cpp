#include "mainwindow.h"
#include <QApplication>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    curl_global_init(CURL_GLOBAL_ALL);

    MainWindow w;
    w.show();

    int result = a.exec();
    curl_global_cleanup();
    return result;
}