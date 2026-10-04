# YouTube Downloader - Dependency Download Script
# Downloads yt-dlp.exe and ffmpeg.exe into the bin folder
# Run from the project root:
#   powershell -ExecutionPolicy Bypass -File download_dependencies.ps1

$ErrorActionPreference = "Stop"

$binDir = Join-Path $PSScriptRoot "bin"
New-Item -ItemType Directory -Force -Path $binDir | Out-Null

# --- yt-dlp ---
$ytdlpPath = Join-Path $binDir "yt-dlp.exe"
if (Test-Path $ytdlpPath) {
    Write-Host "yt-dlp.exe already exists - skipping download" -ForegroundColor Yellow
} else {
    Write-Host "Downloading yt-dlp..." -ForegroundColor Green
    $ytdlpUrl = "https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp.exe"
    Invoke-WebRequest -Uri $ytdlpUrl -OutFile $ytdlpPath
    Write-Host "[OK] yt-dlp downloaded" -ForegroundColor Green
}

# --- ffmpeg ---
$ffmpegPath = Join-Path $binDir "ffmpeg.exe"
if (Test-Path $ffmpegPath) {
    Write-Host "ffmpeg.exe already exists - skipping download" -ForegroundColor Yellow
} else {
    Write-Host "Downloading ffmpeg (this is a large file, please wait)..." -ForegroundColor Green
    $ffmpegUrl = "https://github.com/BtbN/FFmpeg-Builds/releases/download/latest/ffmpeg-master-latest-win64-gpl.zip"
    $ffmpegZip = Join-Path $binDir "ffmpeg.zip"
    Invoke-WebRequest -Uri $ffmpegUrl -OutFile $ffmpegZip

    Write-Host "Extracting ffmpeg..." -ForegroundColor Green
    $tempDir = Join-Path $binDir "temp"
    Expand-Archive -Path $ffmpegZip -DestinationPath $tempDir -Force

    $ffmpegExe = Get-ChildItem -Path $tempDir -Recurse -Filter "ffmpeg.exe" | Select-Object -First 1
    if ($ffmpegExe) {
        Copy-Item $ffmpegExe.FullName -Destination $ffmpegPath -Force
        Write-Host "[OK] ffmpeg extracted" -ForegroundColor Green
    } else {
        Write-Host "[ERROR] Could not find ffmpeg.exe in the archive" -ForegroundColor Red
        exit 1
    }

    Remove-Item $ffmpegZip -Force
    Remove-Item $tempDir -Recurse -Force
}

# --- Verify ---
Write-Host ""
Write-Host "Verification:" -ForegroundColor Cyan
& $ytdlpPath --version
& $ffmpegPath -version | Select-Object -First 1

Write-Host ""
Write-Host "[OK] All dependencies ready. You can now build the project." -ForegroundColor Green
