#include "main/mainwindow.h"
#include "ui_mainwindow.h"
#include  <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QtCore>
#include <QSettings>
#include <QTextCodec>
#include "convert/convert.h"
#include "serial_tool/serial_tool.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") );

    serialPort = new QSerialPort(this);
    this->ss_ui = new serial_tool(this);
    this->ymodme_ui = new ui_ymodem(this);
    ui->tabWidget->addTab(ss_ui,QIcon(":/new/prefix1/img/debug.png"),"串口日志");
    ui->tabWidget->addTab(ymodme_ui,QIcon(":/new/prefix1/img/update.png"),"固件升级");
   // connect(ymodme_ui, SIGNAL(ymodem_signel(ui_ymodem::Status)), this, SLOT(ymodem_event(ui_ymodem::Status)));
     //QSettings能记录一些程序中的信息，下次再打开时可以读取出来


}
MainWindow::~MainWindow()
{
    delete ui;
}

