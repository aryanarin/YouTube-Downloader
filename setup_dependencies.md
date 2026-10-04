# Setup Dependencies

This guide helps you download and set up yt-dlp and ffmpeg for building the project.

## Automatic Setup (Recommended)

### For Windows Users

Create a file called `download_dependencies.ps1` and run it:

```powershell
# PowerShell script to download yt-dlp and ffmpeg
# Run this from the project root directory

# Create bin directory if it doesn't exist
New-Item -ItemType Directory -Force -Path .\bin | Out-Null

Write-Host "Downloading yt-dlp..." -ForegroundColor Green
$ytdlpUrl = "https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp.exe"
Invoke-WebRequest -Uri $ytdlpUrl -OutFile ".\bin\yt-dlp.exe"
Write-Host "✓ yt-dlp downloaded successfully" -ForegroundColor Green

Write-Host "Downloading ffmpeg..." -ForegroundColor Green
$ffmpegUrl = "https://github.com/BtbN/FFmpeg-Builds/releases/download/latest/ffmpeg-master-latest-win64-gpl.zip"
$ffmpegZip = ".\bin\ffmpeg.zip"
Invoke-WebRequest -Uri $ffmpegUrl -OutFile $ffmpegZip

Write-Host "Extracting ffmpeg..." -ForegroundColor Green
Expand-Archive -Path $ffmpegZip -DestinationPath ".\bin\temp" -Force

# Find and copy ffmpeg.exe from the extracted folder
$ffmpegExe = Get-ChildItem -Path ".\bin\temp" -Recurse -Filter "ffmpeg.exe" | Select-Object -First 1
if ($ffmpegExe) {
    Copy-Item $ffmpegExe.FullName -Destination ".\bin\ffmpeg.exe" -Force
    Write-Host "✓ ffmpeg extracted successfully" -ForegroundColor Green
} else {
    Write-Host "✗ Could not find ffmpeg.exe in the archive" -ForegroundColor Red
}

# Cleanup
Remove-Item ".\bin\ffmpeg.zip" -Force
Remove-Item ".\bin\temp" -Recurse -Force

Write-Host "`n✓ All dependencies downloaded!" -ForegroundColor Green
Write-Host "You can now build the project." -ForegroundColor Cyan
```

**To run:**
```powershell
Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process
.\download_dependencies.ps1
```

### For Linux Users

Just install via package manager:

```bash
sudo apt update
sudo apt install yt-dlp ffmpeg
```

## Manual Setup

### Windows Manual Download

#### 1. Download yt-dlp

1. Go to: https://github.com/yt-dlp/yt-dlp/releases/latest
2. Download `yt-dlp.exe`
3. Save it to: `Youtube Downloader\bin\yt-dlp.exe`

#### 2. Download FFmpeg

1. Go to: https://github.com/BtbN/FFmpeg-Builds/releases
2. Download `ffmpeg-master-latest-win64-gpl.zip` (latest release)
3. Extract the ZIP file
4. Navigate to: `ffmpeg-master-latest-win64-gpl\bin\`
5. Copy `ffmpeg.exe` to: `Youtube Downloader\bin\ffmpeg.exe`

### Verify Installation

#### Windows

```cmd
cd "C:\Users\ysary\Documents\Github Projects\Youtube Downloader\bin"
dir
```

You should see:
- `yt-dlp.exe` (around 10-20 MB)
- `ffmpeg.exe` (around 100+ MB)

Test them:
```cmd
yt-dlp.exe --version
ffmpeg.exe -version
```

#### Linux

```bash
which yt-dlp
which ffmpeg
yt-dlp --version
ffmpeg -version
```

## Alternative: Install System-Wide

Instead of bundling binaries, you can install them system-wide:

### Windows (via Chocolatey)

```powershell
choco install yt-dlp ffmpeg
```

### Windows (via Scoop)

```powershell
scoop install yt-dlp ffmpeg
```

### Windows (Manual to PATH)

1. Download executables as above
2. Create folder: `C:\Tools\VideoTools`
3. Copy both .exe files there
4. Add to PATH:
   - Press Win + X → System
   - Advanced System Settings → Environment Variables
   - Edit "Path" under System Variables
   - Add: `C:\Tools\VideoTools`
   - Click OK

### Linux (Different Distros)

**Ubuntu/Debian:**
```bash
sudo apt install yt-dlp ffmpeg
```

**Fedora:**
```bash
sudo dnf install yt-dlp ffmpeg
```

**Arch:**
```bash
sudo pacman -S yt-dlp ffmpeg
```

**From pip (if not in repos):**
```bash
python3 -m pip install -U yt-dlp
```

## Troubleshooting

### "yt-dlp.exe is not a valid Win32 application"

- You may have downloaded the wrong version
- Download the `.exe` file, not the source code
- Make sure it's the Windows version

### "Access Denied" when copying files

- Run PowerShell or Command Prompt as Administrator
- Or copy the files manually using File Explorer

### "ffmpeg.exe not found after extraction"

- The ZIP structure may have changed
- Manually navigate the extracted folder to find `ffmpeg.exe`
- It's usually in a `bin` subfolder

### Files are too large for GitHub

- Don't commit these binaries to Git
- The `.gitignore` is configured to exclude them
- Only distribute them in releases

## File Size Reference

- `yt-dlp.exe`: ~10-20 MB
- `ffmpeg.exe`: ~100-140 MB

Total: ~110-160 MB for bin folder

## Update These Dependencies

### Check for updates regularly:

```bash
# Check current versions
yt-dlp --version
ffmpeg -version

# Update yt-dlp
yt-dlp -U

# ffmpeg needs to be downloaded again from releases
```

For release builds, always use the latest stable versions.

## Security Note

Always download from official sources:
- yt-dlp: https://github.com/yt-dlp/yt-dlp
- FFmpeg: https://github.com/BtbN/FFmpeg-Builds

Do not download from third-party sites to avoid malware.
