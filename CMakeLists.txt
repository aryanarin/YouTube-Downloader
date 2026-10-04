cmake_minimum_required(VERSION 3.25)
project(YouTubeDownloader)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# On Windows, produce a windowed app (no console window pops up)
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE TRUE)
endif()

add_executable(YouTubeDownloader
        main.cpp
        Window.cpp
        Window.h)

target_link_libraries(YouTubeDownloader
        Qt6::Core
        Qt6::Widgets)

# Copy yt-dlp and ffmpeg binaries to the build output directory on Windows
if(WIN32)
    add_custom_command(TARGET YouTubeDownloader POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/bin/yt-dlp.exe"
            "$<TARGET_FILE_DIR:YouTubeDownloader>/yt-dlp.exe"
        COMMENT "Copying yt-dlp.exe to output"
    )
    add_custom_command(TARGET YouTubeDownloader POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/bin/ffmpeg.exe"
            "$<TARGET_FILE_DIR:YouTubeDownloader>/ffmpeg.exe"
        COMMENT "Copying ffmpeg.exe to output"
    )
endif()
