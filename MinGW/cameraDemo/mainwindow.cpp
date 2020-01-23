#include "mainwindow.h"
#include "ui_mainwindow.h"


Q_DECLARE_METATYPE(QCameraInfo)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    QList<QCameraInfo>cameras =  QCameraInfo::availableCameras();
    if(cameras.count() > 0)
    {
        foreach (const QCameraInfo &cameraInfo,cameras)
        {
            qDebug()<<cameraInfo.description();
            QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
            videoDeviceAction->setCheckable(true);
            videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
            if (cameraInfo == QCameraInfo::defaultCamera())
                videoDeviceAction->setChecked(true);
            /* 添加动作*/
            ui->DeviceMenu->addAction(videoDeviceAction);
        }
    }
    /* 这三个声明必须有 */
    camera = new QCamera(QCameraInfo::defaultCamera());
    viewfinder = new QCameraViewfinder(this);
    imageCapture = new QCameraImageCapture(camera);
    connect(videoDevicesGroup, SIGNAL(triggered(QAction*)), SLOT(changeCameraDevice(QAction *action)));
    setCamera(QCameraInfo::defaultCamera());
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setCamera(const QCameraInfo &cameraInfo)
{
    delete imageCapture;
    delete viewfinder;
    delete camera;
    camera = new QCamera(cameraInfo);
    viewfinder = new QCameraViewfinder(this);
    imageCapture = new QCameraImageCapture(camera);
    ui->horizontalLayout->addWidget(viewfinder);
    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(viewfinder);
    camera->start();//启动摄像头
}
void MainWindow::changeCameraDevice(QAction *action)
{
    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}
