cmake_minimum_required(VERSION 3.16)

project(Fbschedular VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt's automatic tools
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 1. Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Concurrent Multimedia MultimediaWidgets)

# 2. Define the project structure
set(PROJECT_SOURCES
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

# 3. Create the executable (Removed binary files from here)
qt_add_executable(Fbschedular
    WIN32
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    3rdparty/curl-8.16.0_3-win64-mingw/bin/curl-ca-bundle.crt 3rdparty/curl-8.16.0_3-win64-mingw/bin/libcurl-x64.dll
)

# 4. Modern Dependency Management (Target-based)
set(LOCAL_CURL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/curl-8.16.0_3-win64-mingw")

target_include_directories(Fbschedular PRIVATE "${LOCAL_CURL_DIR}/include")
target_link_directories(Fbschedular PRIVATE "${LOCAL_CURL_DIR}/lib")

# 5. Link Libraries
target_link_libraries(Fbschedular PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Concurrent
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    curl
)

# 6. Smart Deployment Logic (Updated for libcurl-x64.dll)
set(CURL_BIN_DIR "${LOCAL_CURL_DIR}/bin")

set(CURL_FILES
    "${CURL_BIN_DIR}/libcurl-x64.dll"
    "${CURL_BIN_DIR}/curl-ca-bundle.crt"
)

foreach(FILE_PATH ${CURL_FILES})
    if(EXISTS ${FILE_PATH})
        file(COPY ${FILE_PATH} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    else()
        message(WARNING "Deployment Warning: ${FILE_PATH} not found. Check your 3rdparty folder!")
    endif()
endforeach()

# 7. Qt Finalization
if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_plugins(Fbschedular)
    qt_finalize_executable(Fbschedular)
endif()