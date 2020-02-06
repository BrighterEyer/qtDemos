#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
//要包含下面的两个文件，必须在.pro文件中添加  QT += multimedia  multimediawidgets
#include <QMediaPlayer>
#include <QVideoWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QMediaPlaylist *medialist;

public slots:
    void startVideo();
    void pauseVideo();
    void closeVideo();
};

#endif // MAINWINDOW_H

