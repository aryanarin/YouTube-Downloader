# Release Checklist for YouTube Downloader

Use this checklist when preparing a new release.

## Pre-Release Testing

### Functional Testing
- [ ] Single video download works
- [ ] Playlist download works (test with 3+ videos)
- [ ] Audio-only download works
- [ ] Different quality settings work
- [ ] Codec selection works (VP9, H.264, AV1)
- [ ] Subtitle download works
- [ ] Custom save path works
- [ ] Path persistence works (close/reopen app)
- [ ] "Copy Command" button works
- [ ] "Update yt-dlp" button works
- [ ] Stop button cancels downloads properly
- [ ] Progress bar updates correctly
- [ ] Error messages display properly

### URL Testing
- [ ] Standard YouTube video URL
- [ ] YouTube shorts URL
- [ ] youtu.be sharing links
- [ ] Playlist URLs
- [ ] Channel URLs (if supported)
- [ ] Non-YouTube URLs (Vimeo, etc.)

### Edge Cases
- [ ] Invalid URL handling
- [ ] Empty URL field
- [ ] No save path selected
- [ ] Network interruption handling
- [ ] Disk space full scenario
- [ ] Permission denied errors

### Windows-Specific
- [ ] Application runs without console window
- [ ] All DLLs are bundled correctly
- [ ] yt-dlp.exe and ffmpeg.exe are included
- [ ] Icon displays correctly
- [ ] Runs on Windows 10
- [ ] Runs on Windows 11
- [ ] Update function works (with Admin rights)

### Linux-Specific
- [ ] .deb package installs correctly
- [ ] Desktop entry appears in menu
- [ ] Application launches from menu
- [ ] Dependencies resolve correctly
- [ ] Update function works

## Build Process

### Windows Build
- [ ] Clean build directory
- [ ] CMake configures without errors
- [ ] Project builds without warnings
- [ ] Run windeployqt successfully
- [ ] Copy yt-dlp.exe and ffmpeg.exe
- [ ] Test the built executable
- [ ] Create ZIP package
- [ ] (Optional) Create installer with Inno Setup
- [ ] Test installer on clean Windows machine

### Linux Build
- [ ] Clean build directory
- [ ] CMake configures without errors
- [ ] Project builds without warnings
- [ ] Test the built executable
- [ ] Create .deb package
- [ ] Test .deb installation
- [ ] (Optional) Create AppImage

## Documentation

- [ ] Update version number in:
  - [ ] CMakeLists.txt
  - [ ] README.md
  - [ ] CHANGELOG.md
  - [ ] Window title (if shown)
- [ ] Update CHANGELOG.md with all changes
- [ ] Update README.md if needed
- [ ] Update screenshots if UI changed
- [ ] Review BUILD_INSTRUCTIONS.md for accuracy

## Version Control

- [ ] Commit all changes
- [ ] Create version tag (e.g., `v4.0.0`)
- [ ] Push to GitHub
- [ ] Verify GitHub Actions (if configured)

## GitHub Release

- [ ] Go to GitHub → Releases → Draft a new release
- [ ] Create release tag (e.g., `v4.0.0`)
- [ ] Write release title (e.g., "Version 4.0.0 - Update Button & Playlist Fixes")
- [ ] Copy relevant CHANGELOG entries to release notes
- [ ] Upload release assets:
  - [ ] Windows ZIP or installer
  - [ ] Linux .deb package
  - [ ] (Optional) AppImage
  - [ ] (Optional) Source code archives
- [ ] Mark as pre-release if beta
- [ ] Publish release

## Post-Release

- [ ] Test download links from release page
- [ ] Verify release appears in repository
- [ ] Update any external documentation
- [ ] Announce release (if applicable):
  - [ ] Project README
  - [ ] Social media
  - [ ] Related forums/communities
- [ ] Monitor for bug reports
- [ ] Respond to issues promptly

## Release Assets Naming Convention

- Windows: `YouTubeDownloader-v4.0.0-Windows.zip`
- Windows Installer: `YouTubeDownloader-v4.0.0-Setup.exe`
- Linux deb: `youtube-downloader_4.0.0_amd64.deb`
- Linux AppImage: `YouTubeDownloader-v4.0.0-x86_64.AppImage`
- Source: Let GitHub auto-generate

## Version Numbering Guide

Semantic Versioning: MAJOR.MINOR.PATCH

- **MAJOR**: Breaking changes or major new features
- **MINOR**: New features, backward compatible
- **PATCH**: Bug fixes, minor improvements

Examples:
- 4.0.0 → 4.0.1: Bug fix
- 4.0.1 → 4.1.0: New feature (e.g., download queue)
- 4.1.0 → 5.0.0: Major rewrite or breaking change

## Rollback Plan

If critical issues are found after release:

1. Mark release as "Pre-release" on GitHub
2. Add warning to release notes
3. Pin previous stable release
4. Fix issues quickly
5. Release hotfix version (e.g., 4.0.1)
6. Test thoroughly before re-releasing

## Success Criteria

- [ ] No critical bugs reported within 48 hours
- [ ] All release assets downloadable
- [ ] Installation works on target platforms
- [ ] Core features work as expected
- [ ] Positive or neutral community feedback
