// YouTube Downloader - Qt C++ GUI for yt-dlp
// An improved version of https://github.com/yzu1103309/YouTube-Downloader
// Licensed under the GNU General Public License v3.0
#include <QApplication>
#include "Window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}
