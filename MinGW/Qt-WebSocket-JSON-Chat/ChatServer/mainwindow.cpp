#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Server");

    userList = new QListWidget(this);
    userList->setGeometry(10,10, 500, 400);

    server = new Server(this);
    connect(server, SIGNAL(userConnected(QString)), this, SLOT(onUserConnected(QString)));
    connect(server, SIGNAL(userDisconnected(QString)), this, SLOT(onUserDisconnected(QString)));
    connect(server, SIGNAL(errorOccured(QString)), this, SLOT(onErrorOccured(QString)));

    server->Start();
}

MainWindow::~MainWindow()
{
    delete server;
    delete ui;
}

/**
 * 用户共享槽
 * 添加新用户的名字生成
 */
void MainWindow::onUserConnected(QString username)
{
    userList->addItem(username);
}

/**
 * 用户隔离槽
 * 从列表中删除断开用户的名字
 */
void MainWindow::onUserDisconnected(QString username)
{
    QList<QListWidgetItem *> items = userList->findItems(username, Qt::MatchExactly);
    if (items.size() > 0) {
        foreach(QListWidgetItem* item, items) {
            delete item;
        }
    }
}

/**
 * 误差处理槽
 * 显示错误信息
 */
void MainWindow::onErrorOccured(QString errorMessage)
{
    QMessageBox::information(this, "Error occured", errorMessage);
}

