# Build Instructions for YouTube Downloader

Detailed step-by-step instructions for building the YouTube Downloader on Windows and Linux.

## Windows Build Guide

### Step 1: Install Qt 6

1. Download Qt from: https://www.qt.io/download-open-source
2. Run the Qt Online Installer
3. Select these components:
   - Qt 6.5.x (or latest)
   - MinGW 11.2.0 64-bit (or MSVC 2019 64-bit)
   - Qt Creator (optional, but recommended)
4. Note the installation path (e.g., `C:\Qt\6.5.3`)

### Step 2: Install CMake

1. Download from: https://cmake.org/download/
2. Choose "Windows x64 Installer"
3. During installation, select "Add CMake to system PATH"
4. Verify installation:
   ```cmd
   cmake --version
   ```

### Step 3: Download yt-dlp and ffmpeg

1. **Download yt-dlp:**
   - Go to: https://github.com/yt-dlp/yt-dlp/releases
   - Download `yt-dlp.exe` (latest release)

2. **Download ffmpeg:**
   - Go to: https://github.com/BtbN/FFmpeg-Builds/releases
   - Download `ffmpeg-master-latest-win64-gpl.zip`
   - Extract the archive
   - Find `ffmpeg.exe` in the `bin` folder

3. **Create bin folder in project:**
   ```cmd
   cd "C:\Users\ysary\Documents\Github Projects\Youtube Downloader"
   mkdir bin
   ```

4. **Copy executables:**
   - Copy `yt-dlp.exe` to `bin\yt-dlp.exe`
   - Copy `ffmpeg.exe` to `bin\ffmpeg.exe`

### Step 4: Build the Project

#### Using CMake Command Line

```cmd
cd "C:\Users\ysary\Documents\Github Projects\Youtube Downloader"
mkdir build
cd build

REM For MinGW:
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/Qt/6.5.3/mingw_64 ..
cmake --build . --config Release

REM For MSVC:
REM cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:/Qt/6.5.3/msvc2019_64 ..
REM cmake --build . --config Release
```

#### Using Qt Creator (Alternative)

1. Open Qt Creator
2. File → Open File or Project
3. Select `CMakeLists.txt`
4. Configure the project with your Qt kit
5. Click the green "Run" button

### Step 5: Deploy the Application

```cmd
cd build\Release

REM Deploy Qt dependencies
C:\Qt\6.5.3\mingw_64\bin\windeployqt.exe YouTubeDownloader.exe

REM Copy yt-dlp and ffmpeg (they should already be there from CMake)
REM Verify they exist:
dir yt-dlp.exe
dir ffmpeg.exe
```

### Step 6: Create Release Package

```cmd
cd ..
REM Create a ZIP file with everything
powershell Compress-Archive -Path Release\* -DestinationPath YouTubeDownloader-Windows.zip
```

## Linux Build Guide (Ubuntu/Debian)

### Step 1: Install Dependencies

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-base-dev-tools \
    libqt6core6 \
    libqt6gui6 \
    libqt6widgets6 \
    yt-dlp \
    ffmpeg
```

### Step 2: Build the Project

```bash
cd ~/Documents
git clone <your-repo-url> YouTube-Downloader
cd YouTube-Downloader

mkdir build
cd build

cmake ..
make -j$(nproc)
```

### Step 3: Run the Application

```bash
./YouTubeDownloader
```

### Step 4: Create .deb Package

```bash
# Create package structure
mkdir -p youtube-downloader-4.0.0/DEBIAN
mkdir -p youtube-downloader-4.0.0/usr/local/bin
mkdir -p youtube-downloader-4.0.0/usr/share/applications
mkdir -p youtube-downloader-4.0.0/usr/share/icons/hicolor/256x256/apps

# Copy binary
cp build/YouTubeDownloader youtube-downloader-4.0.0/usr/local/bin/

# Create control file
cat > youtube-downloader-4.0.0/DEBIAN/control << EOF
Package: youtube-downloader
Version: 4.0.0
Section: video
Priority: optional
Architecture: amd64
Depends: libqt6core6, libqt6gui6, libqt6widgets6, yt-dlp, ffmpeg
Maintainer: Your Name <your.email@example.com>
Description: YouTube video and audio downloader
 GUI application for downloading videos and audio from YouTube and 1000+ sites.
 Powered by yt-dlp with automatic update support.
EOF

# Create desktop entry
cat > youtube-downloader-4.0.0/usr/share/applications/youtube-downloader.desktop << EOF
[Desktop Entry]
Name=YouTube Downloader
Comment=Download videos and audio from YouTube
Exec=/usr/local/bin/YouTubeDownloader
Icon=youtube-downloader
Terminal=false
Type=Application
Categories=AudioVideo;Video;
EOF

# Build package
dpkg-deb --build youtube-downloader-4.0.0
mv youtube-downloader-4.0.0.deb youtube-downloader_4.0.0_amd64.deb
```

## Creating an Installer (Windows)

### Using Inno Setup

1. Download and install [Inno Setup](https://jrsoftware.org/isinfo.php)

2. Create `installer.iss` in project root:

```iss
[Setup]
AppName=YouTube Downloader
AppVersion=4.0.0
DefaultDirName={pf}\YouTube Downloader
DefaultGroupName=YouTube Downloader
OutputDir=.
OutputBaseFilename=YouTubeDownloader-Setup
Compression=lzma2
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64

[Files]
Source: "build\Release\YouTubeDownloader.exe"; DestDir: "{app}"
Source: "build\Release\*.dll"; DestDir: "{app}"
Source: "build\Release\yt-dlp.exe"; DestDir: "{app}"
Source: "build\Release\ffmpeg.exe"; DestDir: "{app}"
Source: "build\Release\platforms\*"; DestDir: "{app}\platforms"
Source: "build\Release\styles\*"; DestDir: "{app}\styles"; Flags: recursesubdirs

[Icons]
Name: "{group}\YouTube Downloader"; Filename: "{app}\YouTubeDownloader.exe"
Name: "{commondesktop}\YouTube Downloader"; Filename: "{app}\YouTubeDownloader.exe"

[Run]
Filename: "{app}\YouTubeDownloader.exe"; Description: "Launch YouTube Downloader"; Flags: postinstall nowait skipifsilent
```

3. Compile the installer:
   - Right-click `installer.iss`
   - Select "Compile" (or open in Inno Setup and press F9)

## Troubleshooting Build Issues

### Windows

**CMake can't find Qt:**
```cmd
# Make sure CMAKE_PREFIX_PATH points to your Qt installation
cmake -DCMAKE_PREFIX_PATH=C:/Qt/6.5.3/mingw_64 ..
```

**MinGW not found:**
```cmd
# Add MinGW to PATH
set PATH=C:\Qt\6.5.3\mingw_64\bin;%PATH%
```

**Missing DLLs when running:**
```cmd
# Run windeployqt again
cd build\Release
C:\Qt\6.5.3\mingw_64\bin\windeployqt.exe YouTubeDownloader.exe
```

### Linux

**Qt6 not found:**
```bash
# Install Qt6 development packages
sudo apt install qt6-base-dev qt6-base-dev-tools
```

**Build fails with Qt errors:**
```bash
# Clear build directory and try again
rm -rf build
mkdir build && cd build
cmake ..
make
```

## Testing the Build

Before creating a release, test these scenarios:

1. **Single video download** - Download a YouTube video
2. **Playlist download** - Download a playlist with 3+ videos
3. **Audio extraction** - Download audio only
4. **Update function** - Click "Update yt-dlp" button
5. **Path persistence** - Close and reopen, check if path is remembered
6. **Copy command** - Verify command is copied to clipboard
7. **Error handling** - Try an invalid URL

## Publishing to GitHub

```bash
# Tag the release
git tag -a v4.0.0 -m "Version 4.0.0 - Added update button and fixed playlists"
git push origin v4.0.0

# Go to GitHub → Releases → Draft a new release
# Upload:
# - YouTubeDownloader-Windows.zip (or .exe installer)
# - youtube-downloader_4.0.0_amd64.deb
```

## Version Numbering

Follow [Semantic Versioning](https://semver.org/):
- MAJOR.MINOR.PATCH (e.g., 4.0.0)
- Update MAJOR for breaking changes
- Update MINOR for new features
- Update PATCH for bug fixes
