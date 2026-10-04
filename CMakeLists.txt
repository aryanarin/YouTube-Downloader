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

# Embed application icon on Windows
if(WIN32)
    # windres's preprocessor breaks on build paths containing spaces when -I flags
    # are passed, so compile the resource with a custom command without includes.
    set(APP_RES_OBJ "${CMAKE_CURRENT_BINARY_DIR}/app_res.obj")
    add_custom_command(OUTPUT "${APP_RES_OBJ}"
        COMMAND C:/Qt/Tools/mingw1310_64/bin/windres.exe -O coff
            "${CMAKE_CURRENT_SOURCE_DIR}/app.rc" "${APP_RES_OBJ}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/app.rc" "${CMAKE_CURRENT_SOURCE_DIR}/app.ico"
        COMMENT "Compiling application icon resource"
    )
    target_sources(YouTubeDownloader PRIVATE "${APP_RES_OBJ}")
endif()

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
