#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化动作
    buttonAction1 = new QAction("btnFirstAction",this);
    buttonAction2 = new QAction("btnSecondAction",this);

    lableAction1 = new QAction("lbFirstAction",this);
    lableAction2 = new QAction("lbSecondAction",this);

    //初始化菜单
    buttonMenu = new QMenu(this);

    lableMenu = new QMenu(this);
    //动作添加到菜单
    buttonMenu->addAction(buttonAction1);
    buttonMenu->addAction(buttonAction2);

    lableMenu->addAction(lableAction1);
    lableMenu->addAction(lableAction2);

    //给动作设置信号槽
    connect( buttonAction1, &QAction::triggered, [=]()
    {
        qDebug()<<"I'm btnFirstAction";
    });
    connect( buttonAction2, &QAction::triggered, [=]()
    {
        qDebug()<<"I'm btnSecondAction";
    });
    connect( lableAction1, &QAction::triggered, [=]()
    {
        qDebug()<<"I'm lbFirstAction";
    });
    connect( lableAction2, &QAction::triggered, [=]()
    {
        qDebug()<<"I'm lbSecondAction";
    });

    //给控件设置上下文菜单策略
    ui->label->setContextMenuPolicy(Qt::CustomContextMenu);
    //鼠标右键点击控件时会发送一个void QWidget::customContextMenuRequested(const QPoint &pos)信号
    //给信号设置相应的槽函数
    connect(ui->label,&QLabel::customContextMenuRequested,[=](const QPoint &pos)
    {
        qDebug()<<pos;//参数pos用来传递右键点击时的鼠标的坐标，这个坐标一般是相对于控件左上角而言的
        lableMenu->exec(QCursor::pos());
    });

    ui->pushButton->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->pushButton,&QPushButton::customContextMenuRequested,[=](const QPoint &pos)
    {
        qDebug()<<pos;
        buttonMenu->exec(QCursor::pos());
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
