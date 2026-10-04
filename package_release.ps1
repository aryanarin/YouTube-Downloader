# Package the built YouTubeDownloader into a distributable ZIP
$ErrorActionPreference = "Stop"
$root = $PSScriptRoot
$build = Join-Path $root "build"
$stage = Join-Path $env:TEMP "YouTubeDownloader-Package"

if (Test-Path $stage) { Remove-Item $stage -Recurse -Force }
New-Item -ItemType Directory -Force -Path $stage | Out-Null

# Core executables
Copy-Item (Join-Path $build "YouTubeDownloader.exe") $stage
Copy-Item (Join-Path $build "yt-dlp.exe") $stage
Copy-Item (Join-Path $build "ffmpeg.exe") $stage

# Qt DLLs
Get-ChildItem -Path $build -Filter "*.dll" | ForEach-Object {
    Copy-Item $_.FullName $stage
}

# Plugin folders
foreach ($d in @("platforms","styles","imageformats","iconengines","generic","networkinformation","tls")) {
    $src = Join-Path $build $d
    if (Test-Path $src) { Copy-Item $src (Join-Path $stage $d) -Recurse -Force }
}

# Create ZIP in project root
$zip = Join-Path $root "YouTubeDownloader-v4.0.0-Windows-x64.zip"
if (Test-Path $zip) { Remove-Item $zip -Force }
Compress-Archive -Path (Join-Path $stage "*") -DestinationPath $zip -Force

Remove-Item $stage -Recurse -Force

$item = Get-Item $zip
Write-Host ("Created: " + $item.FullName)
Write-Host ("Size: " + [math]::Round($item.Length / 1MB, 1) + " MB")
