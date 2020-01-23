#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QFileDialog>
#include <QDebug>
#include <QActionGroup>
#include <QCamera>
#include <QMediaRecorder>
#include <QVariant>
#include <QtWidgets>
#include <QMediaRecorder>
#include <QHBoxLayout>

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
    /* 摄像头设备 */
    QCamera *camera;
    /* 截图部件 */
    QCameraImageCapture *imageCapture;
    /* 摄像头取景器部件 */
    QCameraViewfinder *viewfinder;

private slots:

    void setCamera(const QCameraInfo &cameraInfo);
    void changeCameraDevice(QAction *action);
};

#endif // MAINWINDOW_H

