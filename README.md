# YouTube Downloader

A modern, user-friendly desktop application for downloading YouTube videos and audio. Built with Qt C++ and powered by yt-dlp.

> **Note:** This project is an **improved version** of the original [YouTube-Downloader](https://github.com/yzu1103309/YouTube-Downloader) by [yzu1103309](https://github.com/yzu1103309). This fork adds a one-click yt-dlp update button, fixes playlist download reliability, and improves error handling — while keeping the original interface and workflow intact.

![YouTube Downloader](https://img.shields.io/badge/Qt-6-green) ![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-blue) ![License](https://img.shields.io/badge/license-GPL%20v3-blue)

## ✨ Features

### Core Features
- 📹 **Download videos** in multiple qualities (1080p, 720p, 480p, or best available)
- 🎵 **Extract audio** in MP3 format with quality options (320k, 256k, 192k)
- 📋 **Playlist support** - Download entire playlists or individual videos
- 🎬 **Codec selection** - Choose VP9, H.264, or AV1 codecs
- 📝 **Subtitle download** - Download all available subtitles
- 📂 **Custom save location** - Choose where to save your downloads
- 📊 **Progress tracking** - Real-time download progress with percentage

### New in This Version
- ✅ **Auto-Update Button** - Update yt-dlp to the latest version with one click
- 🔧 **Fixed playlist downloads** - Improved reliability for playlist downloads
- 🎯 **Better error handling** - More informative error messages
- 🚀 **Enhanced compatibility** - Works with more video sources
- 💾 **Persistent settings** - Remembers your download path

### Supported Sites
While optimized for YouTube, this downloader supports 1000+ websites including:
- YouTube (videos, playlists, channels)
- Vimeo
- Dailymotion
- Facebook
- Twitter/X
- Instagram
- TikTok
- And many more!

## 📥 Installation

### Windows

#### Option 1: Download Pre-built Release (Recommended)
1. Go to the [Releases](../../releases) page
2. Download the latest `YouTubeDownloader-Windows.zip`
3. Extract the ZIP file
4. Run `YouTubeDownloader.exe`

#### Option 2: Build from Source
See [Building from Source](#building-from-source) below.

### Linux

#### Option 1: Download Pre-built Package
1. Go to the [Releases](../../releases) page
2. Download the `.deb` package (for Ubuntu/Debian) or `.AppImage`
3. Install or run the package

#### Option 2: Build from Source
See [Building from Source](#building-from-source) below.

## 🚀 Usage

1. **Enter URL**: Paste a YouTube video or playlist URL
2. **Select Mode**: Choose "Single Video" or "Whole Playlist"
3. **Choose Format**: Select Video (MP4) or Audio (MP3)
4. **Select Quality**: Pick your preferred quality
5. **Choose Codec** (for video): Select codec preference
6. **Select Path**: Choose where to save the download
7. **Click Download**: Start downloading!

### Update yt-dlp
- Click the **"Update yt-dlp"** button to update to the latest version
- **Note**: On Windows, you may need to run the application as Administrator for updates to work
- This keeps your downloader compatible with the latest YouTube changes

### Copy Command
- Use **"Copy Command"** to copy the yt-dlp command to clipboard
- Useful for manual execution or automation

## 🔧 Building from Source

### Prerequisites

#### Windows
1. **Qt 6** (6.2 or later)
   - Download from [Qt Official Site](https://www.qt.io/download)
   - Install Qt 6 with MinGW or MSVC compiler

2. **CMake** (3.25 or later)
   - Download from [CMake Official Site](https://cmake.org/download/)

3. **yt-dlp and ffmpeg**
   - Download [yt-dlp](https://github.com/yt-dlp/yt-dlp/releases) (yt-dlp.exe)
   - Download [ffmpeg](https://github.com/BtbN/FFmpeg-Builds/releases) (extract ffmpeg.exe)
   - Create a `bin` folder in the project root
   - Place both executables in the `bin` folder

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install qt6-base-dev cmake build-essential
sudo apt install yt-dlp ffmpeg
```

### Build Steps

#### Windows

1. **Clone or download this repository**
```cmd
cd "C:\Users\YourName\Documents"
git clone https://github.com/yourusername/YouTube-Downloader.git
cd YouTube-Downloader
```

2. **Create bin folder and add executables**
```cmd
mkdir bin
REM Copy yt-dlp.exe and ffmpeg.exe to the bin folder
```

3. **Configure with CMake**
```cmd
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/Qt/6.x.x/mingw_xx ..
REM Or for MSVC:
REM cmake -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH=C:/Qt/6.x.x/msvc2019_64 ..
```

4. **Build**
```cmd
cmake --build . --config Release
```

5. **Run**
```cmd
cd Release
YouTubeDownloader.exe
```

#### Linux

```bash
# Clone the repository
git clone https://github.com/yourusername/YouTube-Downloader.git
cd YouTube-Downloader

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run
./YouTubeDownloader
```

## 📦 Creating a Release

### Windows Release

1. **Build the application** (follow build steps above)

2. **Gather dependencies**
```cmd
cd build\Release
windeployqt YouTubeDownloader.exe
```

3. **Copy yt-dlp and ffmpeg**
```cmd
copy ..\..\bin\yt-dlp.exe .
copy ..\..\bin\ffmpeg.exe .
```

4. **Create installer with Inno Setup (Optional)**
   - Download [Inno Setup](https://jrsoftware.org/isinfo.php)
   - Create an installer script (see `installer.iss` example below)
   - Compile the installer

5. **Or create a ZIP package**
```cmd
cd ..
7z a YouTubeDownloader-Windows.zip Release\*
```

### Linux Release

#### Create .deb package

Create a directory structure:
```bash
mkdir -p youtube-downloader/DEBIAN
mkdir -p youtube-downloader/usr/local/bin
mkdir -p youtube-downloader/usr/share/applications
mkdir -p youtube-downloader/usr/share/icons/hicolor/256x256/apps
```

Create `youtube-downloader/DEBIAN/control`:
```
Package: youtube-downloader
Version: 4.0.0
Section: video
Priority: optional
Architecture: amd64
Depends: qt6-base-dev, yt-dlp, ffmpeg
Maintainer: Your Name <your.email@example.com>
Description: YouTube video and audio downloader
 GUI application for downloading videos and audio from YouTube and 1000+ sites.
```

Copy files and build:
```bash
cp build/YouTubeDownloader youtube-downloader/usr/local/bin/
dpkg-deb --build youtube-downloader
```

## 🛠️ Troubleshooting

### Download Errors

**403 Forbidden Error**
- This usually means yt-dlp is outdated
- Click the **"Update yt-dlp"** button
- Or manually update: `yt-dlp -U`

**Playlist Not Downloading**
- Make sure you selected "Whole Playlist" mode
- Verify the URL contains `list=` parameter
- Try updating yt-dlp

**"yt-dlp not found" Error**
- Ensure yt-dlp.exe is in the same folder as the application
- Or install yt-dlp system-wide and add it to PATH

### Windows Defender SmartScreen

If Windows blocks the .exe:
1. Click "More info"
2. Click "Run anyway"

Or run from command line:
```cmd
cd "C:\path\to\YouTubeDownloader"
YouTubeDownloader.exe
```

### Update Permission Issues (Windows)

If updates fail:
1. Right-click `YouTubeDownloader.exe`
2. Select "Run as Administrator"
3. Try updating again

## 📋 System Requirements

### Windows
- Windows 10 or later
- 4GB RAM (recommended)
- 100MB free disk space (plus space for downloads)

### Linux
- Ubuntu 22.04 or later (or equivalent)
- Qt 6 libraries
- 4GB RAM (recommended)
- 100MB free disk space (plus space for downloads)

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the **GNU General Public License v3.0 (GPL-3.0)** - see the [LICENSE](LICENSE) file for details.

This project is based on [yzu1103309/YouTube-Downloader](https://github.com/yzu1103309/YouTube-Downloader), which was originally released under the MIT License. This improved version is distributed under GPL-3.0.

## 🙏 Acknowledgments

- [yzu1103309](https://github.com/yzu1103309/YouTube-Downloader) - Creator of the original YouTube-Downloader project
- [yt-dlp](https://github.com/yt-dlp/yt-dlp) - The powerful backend downloader
- [FFmpeg](https://ffmpeg.org/) - Media processing
- [Qt](https://www.qt.io/) - Cross-platform UI framework

## 📞 Support

If you encounter any issues:
1. Check the [Troubleshooting](#troubleshooting) section
2. Search [existing issues](../../issues)
3. Create a [new issue](../../issues/new) with:
   - Your operating system
   - Application version
   - Error message or description
   - Steps to reproduce

## 🗺️ Roadmap

- [ ] Dark mode support
- [ ] Download history
- [ ] Queue multiple downloads
- [ ] Thumbnail preview
- [ ] Format presets
- [ ] Proxy support
- [ ] Automatic update checking

---

**Note**: This software is for personal use only. Please respect copyright laws and YouTube's Terms of Service.
