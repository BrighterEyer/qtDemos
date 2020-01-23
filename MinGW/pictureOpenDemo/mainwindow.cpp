#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>

#include "QFileDialog"
#include "QMessageBox"
#include "QGuiApplication"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获取exe路径
    runPath = QCoreApplication::applicationDirPath();
    hglpName = "photo";
    hglpPath = QString("%1/%2").arg(runPath).arg(hglpName);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::choosePicture()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg)"));
    if(filename.isEmpty())
        return;
    else
    {
        QImage img;
        if(!(img.load(filename))) //加载图像
        {
            QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
            return;
        }
        ui->label->setPixmap(QPixmap::fromImage(img.scaled(ui->label->size())));
    }
}

void MainWindow::saveToOtherPath()
{
    QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(ui->label->winId()).save(filename1);
}

void MainWindow::save()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(ui->label->winId()).save(QString("%1/34.jpg").arg(hglpPath));
}
