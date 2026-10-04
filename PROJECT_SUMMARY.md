# YouTube Downloader - Project Summary

## Overview

This is an enhanced version of the YouTube Downloader desktop application. It's a Qt-based C++ GUI for yt-dlp that makes downloading videos and audio from YouTube (and 1000+ other sites) easy and user-friendly.

## What's New in Version 4.0.0

### Major Features Added

1. **Auto-Update Button** ✅
   - One-click update for yt-dlp
   - Keeps the downloader compatible with latest YouTube changes
   - Shows update progress and status
   - Handles permissions gracefully (prompts for admin on Windows)

2. **Playlist Download Fixes** ✅
   - Improved format selection for playlists
   - Better error handling
   - More reliable playlist detection
   - Enhanced retry mechanisms (10 retries)

3. **Improved User Experience** ✅
   - Better status messages
   - Progress bar improvements
   - Placeholder text in URL field
   - Button states reflect ongoing operations
   - Path persistence across sessions

### Technical Improvements

- Fixed memory buffer issue (percent array)
- Better URL validation (handles shorts, youtu.be, playlists)
- Improved format strings for compatibility
- Enhanced error handling
- Code cleanup and modernization
- Updated to C++17 standard
- CMake improvements for deployment

## Project Structure

```
YouTube Downloader/
├── Window.h                 # Main window header
├── Window.cpp               # Main window implementation
├── main.cpp                 # Application entry point
├── CMakeLists.txt          # Build configuration
├── README.md               # Main documentation
├── BUILD_INSTRUCTIONS.md   # Detailed build guide
├── QUICKSTART.md          # Quick start for users
├── CHANGELOG.md           # Version history
├── RELEASE_CHECKLIST.md   # Release preparation guide
├── LICENSE                # MIT License
├── .gitignore            # Git ignore rules
├── bin/
│   ├── README.txt        # Instructions for binaries
│   ├── yt-dlp.exe        # yt-dlp executable (download separately)
│   └── ffmpeg.exe        # FFmpeg executable (download separately)
└── build/                # Build output (generated)
```

## Key Features

- ✅ Download YouTube videos in multiple qualities (1080p, 720p, 480p, best)
- ✅ Extract audio to MP3 with quality selection
- ✅ Download entire playlists
- ✅ Subtitle download support
- ✅ Codec selection (VP9, H.264, AV1)
- ✅ Real-time progress tracking
- ✅ Custom save location with persistence
- ✅ Copy command to clipboard
- ✅ One-click yt-dlp updates
- ✅ Cross-platform (Windows & Linux)

## Building the Project

### Prerequisites

**Windows:**
- Qt 6.2+ (with MinGW or MSVC)
- CMake 3.25+
- yt-dlp.exe
- ffmpeg.exe

**Linux:**
- Qt 6 dev packages
- CMake 3.25+
- yt-dlp
- ffmpeg

### Quick Build

**Windows:**
```cmd
mkdir build && cd build
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/Qt/6.5.3/mingw_64 ..
cmake --build . --config Release
```

**Linux:**
```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

See [BUILD_INSTRUCTIONS.md](BUILD_INSTRUCTIONS.md) for detailed steps.

## Creating a Release

### Windows Release

1. Build the project
2. Run windeployqt on the executable
3. Copy yt-dlp.exe and ffmpeg.exe to output
4. Create ZIP or installer (Inno Setup)
5. Test on clean Windows machine

### Linux Release

1. Build the project
2. Create .deb package structure
3. Copy binary and create desktop entry
4. Build package with dpkg-deb
5. Test installation

See [RELEASE_CHECKLIST.md](RELEASE_CHECKLIST.md) for complete checklist.

## Code Architecture

### Main Components

1. **Window Class** (Window.h/cpp)
   - Main application window
   - UI layout and widgets
   - Download management
   - Update management
   - Signal/slot connections

2. **Downloader Process**
   - QProcess wrapper for yt-dlp
   - Output parsing
   - Progress tracking
   - Error handling

3. **Updater Process**
   - QProcess wrapper for yt-dlp update
   - Update status tracking
   - Permission handling

### Key Methods

- `startDownload()` - Initiates video/audio download
- `startUpdate()` - Updates yt-dlp to latest version
- `writeArgs()` - Constructs yt-dlp command arguments
- `getOutput()` - Parses download progress
- `optionsOK()` - Validates user input
- `setButtonsEnabled()` - Manages UI state

## Testing Strategy

Before releasing, test:

1. **Functional Tests**
   - Single video download
   - Playlist download (3+ videos)
   - Audio extraction
   - Different quality settings
   - Subtitle download
   - Update functionality

2. **URL Tests**
   - Standard YouTube URLs
   - Shorts URLs
   - youtu.be sharing links
   - Playlist URLs
   - Non-YouTube URLs

3. **Error Handling**
   - Invalid URLs
   - Network errors
   - Permission errors
   - Disk space issues

## Deployment Notes

### Windows
- Ensure all Qt DLLs are bundled (use windeployqt)
- Include yt-dlp.exe and ffmpeg.exe
- Consider code signing to avoid SmartScreen warnings
- Test on Windows 10 and 11

### Linux
- List all dependencies in .deb control file
- Create desktop entry for menu integration
- Test on Ubuntu 22.04 and 24.04
- Consider creating AppImage for wider compatibility

## Known Limitations

1. **Update Requires Admin** (Windows)
   - yt-dlp update needs admin rights on Windows
   - User is prompted to run as administrator

2. **YouTube Changes**
   - YouTube frequently changes their API
   - Regular yt-dlp updates are essential
   - Update button helps keep it current

3. **Platform-Specific**
   - Some features may work differently on Windows vs Linux
   - Path handling differs between platforms

## Future Enhancements

Potential features for future versions:

- [ ] Dark mode support
- [ ] Download queue (multiple simultaneous downloads)
- [ ] Download history
- [ ] Thumbnail preview
- [ ] Format presets
- [ ] Proxy support
- [ ] Automatic update checking on startup
- [ ] Resume interrupted downloads
- [ ] Batch URL processing from file
- [ ] Custom filename templates
- [ ] Integration with clipboard monitoring

## Contributing

Contributions are welcome!

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

See [README.md](README.md) for more details.

## Resources

- [yt-dlp Documentation](https://github.com/yt-dlp/yt-dlp)
- [Qt Documentation](https://doc.qt.io/qt-6/)
- [FFmpeg Documentation](https://ffmpeg.org/documentation.html)
- [CMake Documentation](https://cmake.org/documentation/)

## License

GNU General Public License v3.0 (GPL-3.0) - see [LICENSE](LICENSE) file. This project is an improved version of the original [yzu1103309/YouTube-Downloader](https://github.com/yzu1103309/YouTube-Downloader).

## Support

For issues, questions, or contributions:
- GitHub Issues: [Create an issue](../../issues)
- Discussions: [GitHub Discussions](../../discussions)
- Email: Check README.md for contact info

## Credits

- Original project by [yzu1103309](https://github.com/yzu1103309/YouTube-Downloader)
- Enhanced by [Your Name]
- Powered by [yt-dlp](https://github.com/yt-dlp/yt-dlp)
- Built with [Qt](https://www.qt.io/)

---

**Last Updated**: October 4, 2024
**Version**: 4.0.0
**Status**: Ready for Release
