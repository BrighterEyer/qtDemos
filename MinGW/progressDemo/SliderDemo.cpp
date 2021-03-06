﻿#include "SliderDemo.h"
#include "ui_sliderdemo.h"

SliderDemo::SliderDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SliderDemo)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);

    ui->progressBar->setRange(0, 99);
    ui->progressBar->setValue(0);

    connect(ui->btn_Start, SIGNAL(clicked()), this, SLOT(slotStart()));
    connect(ui->btn_Stop, SIGNAL(clicked()), this, SLOT(slotStop()));

    //接收到timeout信号，定时器工作
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotProcessBar()));
}

SliderDemo::~SliderDemo()
{
    delete ui;
}

//控制进度条
void SliderDemo::slotProcessBar()
{
    static int pos = 0;
    if (pos == 100)
    {
        m_timer->stop();
        return;
    }

    ui->progressBar->setValue(pos++);
}

//开启定时器
void SliderDemo::slotStart()
{
    m_timer->start(100);
}

//关闭定时器
void SliderDemo::slotStop()
{
    m_timer->stop();
}
