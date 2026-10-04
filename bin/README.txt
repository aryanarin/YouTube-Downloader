YouTube Downloader - Binary Dependencies
==========================================

This folder should contain the following executables:

1. yt-dlp.exe (or yt-dlp on Linux)
   - Download from: https://github.com/yt-dlp/yt-dlp/releases
   - Get the latest yt-dlp.exe file

2. ffmpeg.exe (or ffmpeg on Linux)
   - Download from: https://github.com/BtbN/FFmpeg-Builds/releases
   - Windows: Get ffmpeg-master-latest-win64-gpl.zip
   - Extract ffmpeg.exe from the bin folder

These executables are required for the YouTube Downloader to function.

NOTE: These binaries are not included in the source repository due to size.
      You must download them separately when building from source.

For release builds, these will be automatically copied to the build output
directory by CMake.

Linux users: Install via package manager instead:
  sudo apt install yt-dlp ffmpeg
