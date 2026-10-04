// YouTube Downloader - Qt C++ GUI for yt-dlp
// An improved version of https://github.com/yzu1103309/YouTube-Downloader
// Licensed under the GNU General Public License v3.0
#ifndef QT_PROJECT_WINDOW_H
#define QT_PROJECT_WINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include <QButtonGroup>
#include <QProgressBar>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QProcess>
#include <string>
using namespace std;

class Window: public QWidget
{
    Q_OBJECT
public:
    Window();

private:
    QGroupBox *url_area;
    QGroupBox *mode_area;
    QGroupBox *opt_area;
    QGroupBox *path_area;
    QGroupBox *status_area;

    QLineEdit *url;
    QButtonGroup *playlist_grp;
    QRadioButton *single;
    QRadioButton *multiple;
    QButtonGroup *type_grp;
    QRadioButton *video;
    QRadioButton *audio;
    QComboBox *quality;
    QComboBox *codec;
    QCheckBox *subs;

    QLineEdit *path;
    QPushButton *choosePath;
    QProcess *downloader = new QProcess;
    QProcess *updater = new QProcess;

    QPushButton *copy;
    QPushButton *download;
    QPushButton *stop;
    QPushButton *updateBtn;

    QLabel *status;
    QProgressBar *progress;

    string command;
    char percent[4];  // fixed: 3 chars + null terminator

    // Tracks whether an update or download is running
    bool updaterRunning = false;

    string getSavedPath();

    void closeEvent(QCloseEvent *event) override;

    void initLayout();
    void initButtons();

    // Returns the path to yt-dlp executable bundled alongside the app
    QString getYtDlpPath();

    void showVidOpt()
    {
        quality->clear();
        quality->addItem("Best Video");
        quality->addItem("1080p");
        quality->addItem("720p");
        quality->addItem("480p");
        codec->setEnabled(true);
    }
    void showAudOpt()
    {
        quality->clear();
        quality->addItem("Best Audio");
        quality->addItem("320k");
        quality->addItem("256k");
        quality->addItem("192k");
        codec->setDisabled(true);
    }
    void showCodecOpt()
    {
        codec->clear();
        codec->addItem("Default Codec");
        codec->addItem("VP9");
        codec->addItem("H.264");
        codec->addItem("AV1 (if supported)");
    }
    void chooseDir()
    {
        QString dir = QFileDialog::getExistingDirectory(nullptr, QString(), path->text());
        if(!dir.isEmpty())
        {
            path->setText(dir);
        }
    }
    bool optionsOK(const QString& url_text, const QString& dir, size_t youtube_url_pos);
    QStringList writeArgs(const QString& url_text, const QString& dir, size_t youtube_url_pos, size_t youtube_share_pos);
    void startDownload();
    void stopJob();
    void copyCommand();
    void startUpdate();

    // Disable/enable action buttons during operations
    void setButtonsEnabled(bool downloading, bool updating);

private slots:
    void getOutput();
    void getError();
    void checkStatus();
    void getUpdaterOutput();
    void getUpdaterError();
    void checkUpdateStatus();
};

#endif //QT_PROJECT_WINDOW_H
