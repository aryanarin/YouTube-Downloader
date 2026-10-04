# Quick Start Guide

Get YouTube Downloader up and running in minutes!

## For Users (Pre-built Release)

### Windows

1. **Download**
   - Go to [Releases](https://github.com/yourusername/YouTube-Downloader/releases)
   - Download `YouTubeDownloader-Windows.zip`

2. **Extract**
   - Right-click the ZIP file
   - Select "Extract All..."
   - Choose a location

3. **Run**
   - Open the extracted folder
   - Double-click `YouTubeDownloader.exe`
   - If Windows SmartScreen appears, click "More info" then "Run anyway"

4. **First Use**
   - Paste a YouTube URL
   - Click "Download"
   - Done! 🎉

### Linux (Ubuntu/Debian)

```bash
# Download the .deb file from releases, then:
sudo dpkg -i youtube-downloader_4.0.0_amd64.deb
sudo apt-get install -f  # Install dependencies if needed

# Run from applications menu or:
youtube-downloader
```

## For Developers (Build from Source)

### Windows (Quick Build)

```cmd
REM Prerequisites: Qt 6, CMake, yt-dlp, ffmpeg

cd "C:\Users\ysary\Documents\Github Projects\Youtube Downloader"

REM Create bin folder and add yt-dlp.exe and ffmpeg.exe
mkdir bin
REM (Copy yt-dlp.exe and ffmpeg.exe to bin folder)

REM Build
mkdir build && cd build
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/Qt/6.5.3/mingw_64 ..
cmake --build . --config Release

REM Deploy
cd Release
C:\Qt\6.5.3\mingw_64\bin\windeployqt.exe YouTubeDownloader.exe

REM Run
YouTubeDownloader.exe
```

### Linux (Quick Build)

```bash
# Install dependencies
sudo apt install qt6-base-dev cmake build-essential yt-dlp ffmpeg

# Build
cd ~/Documents/GitHub-Projects/Youtube-Downloader
mkdir build && cd build
cmake ..
make -j$(nproc)

# Run
./YouTubeDownloader
```

## First Download

1. **Copy a YouTube URL**
   - Example: `https://www.youtube.com/watch?v=dQw4w9WgXcQ`

2. **Paste in the URL field**

3. **Choose settings:**
   - Mode: Single Video or Whole Playlist
   - Format: Video (MP4) or Audio (MP3)
   - Quality: Best, 1080p, 720p, 480p, etc.

4. **Select save location:**
   - Click "Choose" button
   - Pick a folder

5. **Click "Download"**
   - Watch the progress bar
   - Wait for "Download completed successfully!"

6. **Find your file:**
   - Check the folder you selected
   - Videos are organized by title

## Common Tasks

### Download a Playlist

1. Copy playlist URL (must contain `list=`)
2. Select "Whole Playlist" mode
3. Click Download
4. All videos will be saved in a playlist folder

### Download Audio Only

1. Paste video URL
2. Select "Audio (mp3)" option
3. Choose quality (320k recommended)
4. Click Download
5. MP3 file will be extracted

### Update yt-dlp

1. Click "Update yt-dlp" button
2. Wait for update to complete
3. See "✓ yt-dlp updated successfully!"

**Note**: On Windows, you may need to run as Administrator:
- Right-click `YouTubeDownloader.exe`
- Select "Run as administrator"
- Then click Update

### Copy Command for Manual Use

1. Enter URL and settings
2. Click "Copy Command"
3. Open terminal/cmd
4. Paste and run the command

## Troubleshooting Quick Fixes

### "yt-dlp not found"
**Fix**: Ensure `yt-dlp.exe` is in the same folder as the application

### "403 Forbidden" error
**Fix**: Click "Update yt-dlp" button

### Download not starting
**Fix**: Check your internet connection and URL validity

### Windows blocks the .exe
**Fix**: Click "More info" → "Run anyway"

### Update fails on Windows
**Fix**: Run as Administrator (right-click → Run as administrator)

## Tips & Tricks

- ⚡ **Keyboard shortcut**: Paste URL and press Enter to start
- 📁 **Path memory**: The app remembers your last save location
- 🔄 **Update regularly**: Click Update button weekly for best compatibility
- 📋 **Batch downloads**: Download playlists instead of videos one-by-one
- 🎵 **Audio quality**: 320k is CD quality, 192k is good enough for most uses
- 📝 **Subtitles**: Enable them before downloading, can't add later

## Getting Help

1. Check the [README](README.md) for detailed information
2. Review [BUILD_INSTRUCTIONS](BUILD_INSTRUCTIONS.md) for build help
3. Search [existing issues](https://github.com/yourusername/YouTube-Downloader/issues)
4. Create a [new issue](https://github.com/yourusername/YouTube-Downloader/issues/new) with details

## Next Steps

- Star ⭐ the project on GitHub
- Share with friends who need a YouTube downloader
- Report bugs or suggest features
- Contribute to the project!

---

**Legal Notice**: This software is for personal use. Respect copyright laws and YouTube's Terms of Service.
