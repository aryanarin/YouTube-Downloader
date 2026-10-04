# Changelog

All notable changes to this project will be documented in this file.

## [4.0.0] - 2026-10-04

### Added
- **License change**: Project relicensed from MIT (original) to GNU GPL v3.0
- **Attribution**: This project is an improved version of yzu1103309/YouTube-Downloader
- **Update Button**: Added "Update yt-dlp" button for easy one-click updates
- Auto-update functionality for yt-dlp backend
- Better progress indication during updates
- Administrator privilege detection for Windows updates
- Placeholder text in URL field for better UX

### Fixed
- **Playlist Download Issues**: Improved playlist handling and reliability
- Better format selection for various video sources
- More robust error handling for edge cases
- Fixed percentage parsing in progress bar
- Improved URL validation (now handles shorts, youtu.be links better)
- Fixed memory issues with percentage buffer

### Changed
- Updated format selection arguments for better compatibility
- Improved error messages and user feedback
- Enhanced codec selection logic
- Better fallback format options
- Increased window height to accommodate new button (600px)
- Updated CMake minimum version to 3.25
- Changed C++ standard to C++17

### Improved
- Download reliability with retry mechanisms (10 retries)
- Fragment retry handling for network issues
- Status messages are more informative
- Button states now properly reflect ongoing operations
- Update process provides clearer feedback

## [3.0.0] - 2024-03-01

### Added
- Codec selection menu (VP9, AV1, H.264)
- Enhanced usage flexibility with command generation
- Download path persistence

### Changed
- yt-dlp installed to '/usr/local/bin' on Ubuntu (instead of '/usr/bin')
- Updated yt-dlp version to 2023.12.30

### Fixed
- YouTube sharing link 'youtu.be' now works correctly

### Removed
- Support for Ubuntu 20.04 Focal

## [2.0.0] - Previous Version

### Added
- GUI interface with Qt
- Single video and playlist download modes
- Quality selection
- Subtitle download option
- Progress tracking
- Custom save location

## [1.0.0] - Initial Release

### Added
- Basic yt-dlp wrapper
- Simple command-line interface
