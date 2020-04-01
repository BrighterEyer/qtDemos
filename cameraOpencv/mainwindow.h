#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QImage>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QImage  Mat2QImage(Mat cvImg);
private slots:
    void openCamara();      // 打开摄像头
    void readFarme();       // 读取当前帧信息
    void closeCamara();     // 关闭摄像头。
    void takingPictures();  // 拍照

private:
    Ui::MainWindow *ui;

    QTimer          *timer;
    QImage          imag;
    Mat             cap,cap_gray,cap_tmp; //定义一个Mat变量，用于存储每一帧的图像
    VideoCapture    capture; //声明视频读入类


    CascadeClassifier eye_Classifier;  //载入分类器
    CascadeClassifier face_cascade;    //载入分类器
    //vector 是个类模板 需要提供明确的模板实参 vector<Rect>则是个确定的类 模板的实例化  需要指点std域名才可以用：using namespace std;
    vector<Rect> eyeRect;
    vector<Rect> faceRect;
    vector<Rect> faces;

};

#endif // MAINWINDOW_H

