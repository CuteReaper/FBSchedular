cmake_minimum_required(VERSION 3.16)

project(Fbschedular VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Concurrent Multimedia MultimediaWidgets)

# Explicitly point to your local curl folder
set(LOCAL_CURL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/curl-8.16.0_3-win64-mingw")
include_directories("${LOCAL_CURL_DIR}/include")
link_directories("${LOCAL_CURL_DIR}/lib")

qt_add_executable(Fbschedular
    MANUAL_FINALIZATION

    main.cpp
    mainwindow.cpp
    postwidget.cpp
    FacebookScheduler.cpp

    mainwindow.h
    postwidget.h
    postjob.h
    FacebookScheduler.h

    mainwindow.ui
    postwidget.ui
)

target_link_libraries(Fbschedular PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Concurrent
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    curl
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_plugins(Fbschedular)
    qt_finalize_executable(Fbschedular)
endif()