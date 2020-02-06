#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);

    ui->verticalLayout->addWidget(videoWidget);
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(startVideo()));
    connect(ui->pauseButton,SIGNAL(clicked()),this,SLOT(pauseVideo()));
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(closeVideo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startVideo()
{
    player->setMedia(QUrl::fromLocalFile("G:\\workspaces\\qt\\videoSources\\player.flv"));
    videoWidget->show();
    player->play();
}

void MainWindow::pauseVideo()
{
    player->pause();
}

void MainWindow::closeVideo()
{
    player->stop();
}
