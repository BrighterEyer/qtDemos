#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer   = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
    connect(ui->open, SIGNAL(clicked()), this, SLOT(openCamara()));
    connect(ui->take, SIGNAL(clicked()), this, SLOT(takingPictures()));
    connect(ui->close, SIGNAL(clicked()), this, SLOT(closeCamara()));
}


//打开摄像头
void MainWindow::openCamara()
{
    capture.open(0);    //从摄像头读入视频如果设备只有一个摄像头就传入参数0
    qDebug("open");
    if (!capture.isOpened()) //先判断是否打开摄像头
    {
        qDebug("err");
    }
    timer->start(20);              // 开始计时，20ms获取一帧
}

//读取摄像头信息
//void MainWindow::readFarme()
//{
//    capture>>cap; //读取当前帧
//    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
//    {
//        imag = Mat2QImage(cap);
//        imag = imag.scaled(ui->camera->width(), ui->camera->height(),
//                           Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致
//        //imshow(name, cap); //若当前帧捕捉成功，显示
//        ui->camera->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
//    }
//    else
//        qDebug("can not ");
//}

void MainWindow::readFarme()
{
    capture>>cap; //读取当前帧
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        cvtColor(cap, cap_gray, CV_BGR2GRAY);//转为灰度图
        equalizeHist(cap_gray, cap_gray);//直方图均衡化，增加对比度方便处理


        if (!eye_Classifier.load("/home/machine/work/opencv/opencv-3.4.3/data/haarcascades/haarcascade_eye.xml"))  //需要将xml文档放在自己指定的路径下
        {
            qDebug("Load haarcascade_eye.xml failed!");
            return;
        }
        if (!face_cascade.load("/home/machine/work/opencv/opencv-3.4.3/data/haarcascades/haarcascade_frontalface_alt.xml"))
        {
            qDebug("Load haarcascade_frontalface_alt failed!");
            return;
        }

        //检测关于眼睛部位位置
        eye_Classifier.detectMultiScale(cap_gray, eyeRect, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));//检测
        for (size_t eyeIdx = 0; eyeIdx < eyeRect.size(); eyeIdx++)
        {
            rectangle(cap, eyeRect[eyeIdx], Scalar(0, 0, 255));   //用红色矩形画出检测到的位置
        }
        //检测关于脸部位置
        face_cascade.detectMultiScale(cap_gray, faceRect, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));//检测
        for (size_t i = 0; i < faceRect.size(); i++)
        {
            rectangle(cap, faceRect[i], Scalar(0, 255, 0));      //用绿色矩形画出检测到的位置
        }
        imag = Mat2QImage(cap);     // 将Mat转换成QImage对象来显示
        imag = imag.scaled(ui->camera->width(),
                           ui->camera->height(),
                           Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);//设置图片大小和label的长宽一致
        //imshow(name, cap); //若当前帧捕捉成功，显示
        ui->camera->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
    }
    else
        qDebug("can not ");
}


// 拍照
void MainWindow::takingPictures()
{
    capture>>cap; //读取当前帧
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        imag = Mat2QImage(cap);
        imag = imag.scaled(ui->photo->width(),
                           ui->photo->height(),
                           Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);//设置图片大小和label的长宽一致

        //imshow(name, cap); //若当前帧捕捉成功，显示
        ui->photo->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
    }
    else
        qDebug("can not ");
}


//关闭摄像头，释放资源，必须释放***
void MainWindow::closeCamara()
{
    timer->stop();         // 停止读取数据。
}


// 图片转换（网上抄的）
QImage  MainWindow::Mat2QImage(Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)     //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                     cvImg.cols, cvImg.rows,
                     cvImg.cols*cvImg.channels(),
                     QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                     cvImg.cols,cvImg.rows,
                     cvImg.cols*cvImg.channels(),
                     QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                     cvImg.cols,cvImg.rows,
                     cvImg.cols*cvImg.channels(),
                     QImage::Format_RGB888);
    }
    return qImg;
}

MainWindow::~MainWindow()
{
    delete ui;
}

