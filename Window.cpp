#include <QLayout>
#include <QFormLayout>
#include <QScreen>
#include <QClipboard>
#include <QApplication>
#include <QMessageBox>
#include <QDir>
#include <QStandardPaths>
#include <fstream>
#include "Window.h"

int fixedW = 1000;
int fixedH = 600;  // Increased height to accommodate update button

string Window::getSavedPath()
{
    fstream ioFile("./path.dat", ios::binary | ios::in);
    // Default to user's Downloads folder
    string dir = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation).toStdString() + "/YouTube Downloader";
    if(ioFile)
    {
        getline(ioFile, dir);
    }
    return dir;
}

void Window::closeEvent(QCloseEvent *event)
{
    fstream ioFile("./path.dat", ios::binary | ios::out);
    if(ioFile)
    {
        ioFile << path->text().toStdString();
    }

    if(downloader->state() == QProcess::NotRunning && updater->state() == QProcess::NotRunning)
    {
        event->accept();
    }
    else
    {
        QMessageBox msg;
        msg.setText("Operation in progress. Stop and exit?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        int rtn = msg.exec();
        if(rtn == QMessageBox::Yes)
        {
            if(downloader->state() == QProcess::Running)
                downloader->kill();
            if(updater->state() == QProcess::Running)
                updater->kill();
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
}

QString Window::getYtDlpPath()
{
    // Look for yt-dlp in the application directory first
    QString appDir = QCoreApplication::applicationDirPath();
    QString ytdlpPath = appDir + "/yt-dlp.exe";
    
    if(QFile::exists(ytdlpPath))
    {
        return ytdlpPath;
    }
    
    // Fall back to system PATH
    return "yt-dlp";
}

Window::Window()
{
    setWindowTitle("YouTube Downloader");
    setWindowIcon(QIcon("./youtube.png"));
    setFixedWidth(fixedW);
    setFixedHeight(fixedH);
    move(screen()->geometry().center() - frameGeometry().center());
    initLayout();

    copy = new QPushButton("Copy Command");
    copy->setFixedWidth(150);
    copy->setFixedHeight(40);
    connect(copy, &QPushButton::clicked, this, &Window::copyCommand);

    download = new QPushButton("Download");
    download->setFixedWidth(150);
    download->setFixedHeight(40);
    connect(download, &QPushButton::clicked, this, &Window::startDownload);

    stop = new QPushButton("Stop");
    stop->setFixedWidth(150);
    stop->setFixedHeight(40);
    connect(stop, &QPushButton::clicked, this, &Window::stopJob);

    updateBtn = new QPushButton("Update yt-dlp");
    updateBtn->setFixedWidth(150);
    updateBtn->setFixedHeight(40);
    updateBtn->setToolTip("Update yt-dlp and ffmpeg to the latest versions");
    connect(updateBtn, &QPushButton::clicked, this, &Window::startUpdate);

    QHBoxLayout *action_area = new QHBoxLayout();
    action_area->addStretch();
    action_area->addWidget(download, 0, Qt::AlignCenter);
    action_area->addSpacerItem(new QSpacerItem(20, 0));
    action_area->addWidget(copy, 0, Qt::AlignCenter);
    action_area->addSpacerItem(new QSpacerItem(20, 0));
    action_area->addWidget(stop, 0, Qt::AlignCenter);
    action_area->addSpacerItem(new QSpacerItem(20, 0));
    action_area->addWidget(updateBtn, 0, Qt::AlignCenter);
    action_area->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(url_area);
    mainLayout->addWidget(mode_area);
    mainLayout->addWidget(opt_area);
    mainLayout->addWidget(path_area);
    mainLayout->addSpacerItem(new QSpacerItem(0,25));
    mainLayout->addLayout(action_area);
    mainLayout->addSpacerItem(new QSpacerItem(0,25));
    mainLayout->addWidget(status_area);
}

void Window::initLayout()
{
    url_area = new QGroupBox;
    url = new QLineEdit;
    url->setPlaceholderText("Enter YouTube URL (video or playlist)");
    QFormLayout *layout1 = new QFormLayout;
    layout1->addRow(new QLabel("URL: "), url);
    url_area->setLayout(layout1);
    url_area->setFixedHeight(50);

    mode_area = new QGroupBox;
    QHBoxLayout *modeLayout = new QHBoxLayout;
    playlist_grp = new QButtonGroup;
    single = new QRadioButton("Single Video");
    multiple = new QRadioButton("Whole Playlist");
    playlist_grp->addButton(single);
    playlist_grp->addButton(multiple);
    modeLayout->addWidget(new QLabel("Mode Selection: "), 0, Qt::AlignCenter);
    modeLayout->addWidget(single, 0, Qt::AlignCenter);
    modeLayout->addWidget(multiple, 0, Qt::AlignCenter);
    single->setChecked(true);
    mode_area->setLayout(modeLayout);

    opt_area = new QGroupBox;
    quality = new QComboBox;
    codec = new QComboBox;
    Window::showCodecOpt();
    initButtons();
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(new QLabel("Options: "));
    layout2->addWidget(video);
    layout2->addWidget(audio);
    layout2->addWidget(quality);
    layout2->addSpacerItem(new QSpacerItem(25, 0));
    layout2->addWidget(codec);
    layout2->addWidget(subs, 0,Qt::AlignRight);
    opt_area->setLayout(layout2);

    path_area = new QGroupBox;
    path = new QLineEdit;
    path->setReadOnly(true);
    string dir = getSavedPath();
    path->setText(dir.c_str());
    choosePath = new QPushButton("Choose");
    choosePath->setIcon(QIcon::fromTheme("folder"));
    connect(choosePath, &QPushButton::clicked, this, &Window::chooseDir);
    QGridLayout *layout3 = new QGridLayout;
    layout3->addWidget(new QLabel("Path: "), 0,0);
    layout3->addWidget(path, 0, 1);
    layout3->addWidget(choosePath, 0, 2);
    path_area->setLayout(layout3);

    status_area = new QGroupBox;
    status = new QLabel("Ready");
    status->setFixedHeight(80);
    status->setAlignment(Qt::AlignCenter);
    status->setWordWrap(true);
    progress = new QProgressBar;
    progress->setValue(0);
    QGridLayout *layout4 = new QGridLayout;
    layout4->addWidget(status, 1,0);
    layout4->addWidget(progress, 2,0);
    status_area->setLayout(layout4);
}

void Window::initButtons()
{
    type_grp = new QButtonGroup;
    video = new QRadioButton("Video (mp4)");
    audio = new QRadioButton("Audio (mp3)");
    subs = new QCheckBox("Subtitles (all)");

    connect(video, &QRadioButton::clicked, this, &Window::showVidOpt);
    connect(audio, &QRadioButton::clicked, this, &Window::showAudOpt);

    video->setChecked(true);
    showVidOpt();

    type_grp->addButton(video);
    type_grp->addButton(audio);
}

bool Window::optionsOK(const QString& url_text, const QString& dir, size_t youtube_url_pos)
{
    if(url_text.isEmpty())
    {
        status->setText("[ERROR] URL Required");
        return false;
    }
    if(dir.isEmpty())
    {
        status->setText("[ERROR] Choose a directory to store the file");
        return false;
    }
    
    // More lenient checking - allow both modes to work with various URLs
    if(single->isChecked() && youtube_url_pos != string::npos)
    {
        size_t watch_found = url_text.toStdString().find("watch");
        size_t short_found = url_text.toStdString().find("shorts");
        size_t short_found2 = url_text.toStdString().find("short");
        size_t share_found = url_text.toStdString().find("youtu.be");
        size_t list_found = url_text.toStdString().find("list=");
        
        // If it's clearly a playlist URL and user selected single mode, warn them
        if(list_found != string::npos && watch_found == string::npos && 
           short_found == string::npos && short_found2 == string::npos && share_found == string::npos)
        {
            status->setText("[WARNING] This appears to be a playlist URL.\nSwitch to 'Whole Playlist' mode to download all videos.");
            // Don't return false - let yt-dlp handle it with --no-playlist
        }
    }
    
    return true;
}

QStringList Window::writeArgs(const QString& url_text, const QString& dir, size_t youtube_url_pos, size_t youtube_share_pos)
{
    QStringList args = (
            QStringList() << url_text.toStdString().c_str()
                          << "--paths" << dir.toStdString().c_str() 
                          << "--no-color"
                          << "--no-mtime"  // Don't set file modification time
                          << "--ignore-errors"  // Continue on download errors
    );
    
    string kbps;
    args << "--format";
    
    if(video->isChecked())
    {
        // Improved format selection for better compatibility
        if(youtube_url_pos != string::npos || youtube_share_pos != string::npos)
        {
            switch (quality->currentIndex()) {
                case 0: // best video
                    args << "bestvideo[ext=mp4]+bestaudio[ext=m4a]/best[ext=mp4]/best";
                    break;
                case 1:
                    args << "bestvideo[height<=1080][ext=mp4]+bestaudio[ext=m4a]/best[height<=1080]/best";
                    break;
                case 2:
                    args << "bestvideo[height<=720][ext=mp4]+bestaudio[ext=m4a]/best[height<=720]/best";
                    break;
                case 3:
                    args << "bestvideo[height<=480][ext=mp4]+bestaudio[ext=m4a]/best[height<=480]/best";
            }
        }
        else
        {
            args << "bestvideo+bestaudio/best";
        }
        
        // Codec preference
        switch (codec->currentIndex()) {
            case 1:
                args << "-S" << "vcodec:vp9";
                break;
            case 2:
                args << "-S" << "vcodec:h264";
                break;
            case 3:
                args << "-S" << "vcodec:av01";
        }
    }
    else
    {
        if(youtube_url_pos != string::npos || youtube_share_pos != string::npos)
        {
            args << "bestaudio[ext=m4a]/bestaudio" << "-x" << "--audio-format" << "mp3" << "--audio-quality";
        }
        else
        {
            args << "bestaudio" << "-x" << "--audio-format" << "mp3" << "--audio-quality";
        }
        
        switch (quality->currentIndex()) {
            case 0: // best audio
                kbps = "0";  // 0 means best quality
                break;
            case 1:
                kbps = "320k";
                break;
            case 2:
                kbps = "256k";
                break;
            case 3:
                kbps = "192k";
        }
        args << kbps.c_str();
    }

    if(video->isChecked() && subs->isChecked())
        args << "--write-subs" << "--sub-langs" << "all" << "--convert-subs" << "srt" << "--embed-subs";

    if(single->isChecked())
        args << "--no-playlist";
    else
        args << "--yes-playlist";

    string o_template;
    if(multiple->isChecked())
    {
        if(video->isChecked())
            o_template = "[Playlist] %(playlist)s/%(playlist_index)03d - %(title)s.%(ext)s";
        else
            o_template = "[Playlist] %(playlist)s/%(playlist_index)03d - %(title)s.%(ext)s";
    }
    else
    {
        if(video->isChecked())
            o_template = "%(title)s.%(ext)s";
        else
            o_template = "%(title)s.%(ext)s";
    }
    args << "-o" << o_template.c_str();

    // Add retries for reliability
    args << "--retries" << "10";
    args << "--fragment-retries" << "10";

    return args;
}

void Window::copyCommand()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString url_text = url->text();
    QString dir = path->text();
    size_t youtube_url = url_text.toStdString().find("youtube");
    size_t youtube_share_url = url_text.toStdString().find("youtu.be");

    if(!optionsOK(url_text, dir, youtube_url)) return;

    QStringList args = writeArgs(url_text, dir, youtube_url, youtube_share_url);

    QString args_str = "yt-dlp";
    for (int t = 0; t < args.size(); ++t)
    {
        args_str += " ";
        // Quote arguments containing spaces
        if(args[t].contains(' '))
            args_str += "\"" + args[t] + "\"";
        else
            args_str += args[t];
    }
    clipboard->setText(args_str);
    status->setText("[Message] Command copied to clipboard!\nOpen command line and paste.");
}

void Window::setButtonsEnabled(bool downloading, bool updating)
{
    download->setEnabled(!downloading && !updating);
    copy->setEnabled(!downloading && !updating);
    stop->setEnabled(downloading);
    updateBtn->setEnabled(!downloading && !updating);
    url->setEnabled(!downloading && !updating);
    choosePath->setEnabled(!downloading && !updating);
}

void Window::startDownload()
{
    if(downloader->state() == QProcess::NotRunning && !updaterRunning)
    {
        memset(percent, 0, sizeof(percent));
        progress->setValue(0);

        QString url_text = url->text();
        QString dir = path->text();
        size_t youtube_url = url_text.toStdString().find("youtube");
        size_t youtube_share_url = url_text.toStdString().find("youtu.be");

        if(!optionsOK(url_text, dir, youtube_url)) return;

        QStringList args = writeArgs(url_text, dir, youtube_url, youtube_share_url);

        status->setText("Starting download...");
        setButtonsEnabled(true, false);
        repaint();

        delete downloader;
        downloader = new QProcess;
        
        QString ytdlpPath = getYtDlpPath();
        downloader->start(ytdlpPath, args);

        connect(downloader, SIGNAL(readyReadStandardOutput()),this, SLOT(getOutput()));
        connect(downloader, SIGNAL(readyReadStandardError()),this, SLOT(getError()));
        connect(downloader, SIGNAL(finished(int,QProcess::ExitStatus)),this, SLOT(checkStatus()));
    }
}

void Window::getOutput()
{
    QString output = QString::fromLocal8Bit(downloader->readAllStandardOutput());
    string tmp = output.toStdString();
    size_t found = tmp.find("[download]");
    if(found != string::npos)
    {
        tmp.erase(0, found+11);
    }
    status->setText(tmp.c_str());

    // Parse percentage more carefully
    size_t percent_pos = tmp.find("%");
    if(percent_pos != string::npos && percent_pos >= 1)
    {
        // Find the start of the percentage number
        size_t start = percent_pos;
        while(start > 0 && (isdigit(tmp[start-1]) || tmp[start-1] == '.'))
        {
            start--;
        }
        
        string percent_str = tmp.substr(start, percent_pos - start);
        try {
            double percent_val = std::stod(percent_str);
            progress->setValue(static_cast<int>(percent_val));
        } catch(...) {
            // Ignore parse errors
        }
    }
}

void Window::getError()
{
    QString output = downloader->readAllStandardError();
    // Don't show warnings, only real errors
    if(output.contains("ERROR", Qt::CaseInsensitive))
    {
        status->setText("Error: " + output);
    }
}

void Window::checkStatus()
{
    if(downloader->exitStatus() == QProcess::NormalExit)
    {
        if(downloader->exitCode() == 0)
        {
            status->setText("Download completed successfully!");
            progress->setValue(100);
        }
        else
        {
            status->setText("Download finished with errors. Check the output directory.");
        }
    }
    else
    {
        status->setText("Download was interrupted.");
    }
    setButtonsEnabled(false, false);
}

void Window::stopJob()
{
    if(downloader->state() == QProcess::Running)
    {
        downloader->kill();
        status->setText("Download canceled by user.");
        progress->setValue(0);
        setButtonsEnabled(false, false);
    }
}

void Window::startUpdate()
{
    if(updater->state() == QProcess::NotRunning && downloader->state() == QProcess::NotRunning)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Update yt-dlp", 
            "This will update yt-dlp to the latest version.\n\nNote: On Windows, you may need to run this application as Administrator for the update to work.\n\nContinue?",
            QMessageBox::Yes|QMessageBox::No);
        
        if (reply == QMessageBox::No)
            return;

        status->setText("Updating yt-dlp...");
        progress->setValue(0);
        updaterRunning = true;
        setButtonsEnabled(false, true);
        repaint();

        delete updater;
        updater = new QProcess;
        
        QString ytdlpPath = getYtDlpPath();
        QStringList args;
        args << "-U";  // Update flag

        updater->start(ytdlpPath, args);

        connect(updater, SIGNAL(readyReadStandardOutput()),this, SLOT(getUpdaterOutput()));
        connect(updater, SIGNAL(readyReadStandardError()),this, SLOT(getUpdaterError()));
        connect(updater, SIGNAL(finished(int,QProcess::ExitStatus)),this, SLOT(checkUpdateStatus()));
    }
}

void Window::getUpdaterOutput()
{
    QString output = QString::fromLocal8Bit(updater->readAllStandardOutput());
    status->setText("Update: " + output.trimmed());
}

void Window::getUpdaterError()
{
    QString output = updater->readAllStandardError();
    status->setText("Update: " + output.trimmed());
}

void Window::checkUpdateStatus()
{
    updaterRunning = false;
    
    if(updater->exitStatus() == QProcess::NormalExit)
    {
        if(updater->exitCode() == 0)
        {
            status->setText("✓ yt-dlp updated successfully!\nYou're using the latest version.");
            progress->setValue(100);
        }
        else
        {
            QString output = QString::fromLocal8Bit(updater->readAllStandardOutput());
            if(output.contains("up to date", Qt::CaseInsensitive) || 
               output.contains("already", Qt::CaseInsensitive))
            {
                status->setText("✓ yt-dlp is already up to date!");
                progress->setValue(100);
            }
            else
            {
                status->setText("Update failed. Try running as Administrator\nor manually update with: yt-dlp -U");
            }
        }
    }
    else
    {
        status->setText("Update was interrupted.");
    }
    
    setButtonsEnabled(false, false);
}
