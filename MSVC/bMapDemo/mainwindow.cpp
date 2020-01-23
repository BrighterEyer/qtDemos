#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bridge.h"
#include <QWebChannel>
#include <QStackedLayout>
#include <QDebug>

#define bridgeins bridge::instance()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitForm();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    m_timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitForm()
{
    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject("bridge", (QObject*)bridgeins);


    webView = new QWebEngineView(this);
    webView->page()->setWebChannel(channel);
    webView->page()->load(QUrl(qApp->applicationDirPath() + "/index.html"));


    QString msg =  qApp->applicationDirPath()+"/index.html";
    qDebug() << msg;

    QStackedLayout* layout = new QStackedLayout(ui->frame);
//    ui->frame->setLayout(layout);
    layout->addWidget(webView);

    bridgeins->Init();

    const QList<Light_t>& list = bridgeins->GetLightList();
    int nCount = list.count();
    for(int i=0; i<nCount; i++)
    {
        Light_t tLight = list[i];
        ui->cbLight->addItem(tLight.strDesc, tLight.strName);
    }
    ui->cbLight->setCurrentIndex(0);


    this->showMaximized();
}


void MainWindow::on_btnAddLight_clicked()
{
    Light_t tLight = bridgeins->AddLight();
    ui->cbLight->addItem(tLight.strDesc, tLight.strName);
    ui->cbLight->setCurrentIndex(ui->cbLight->count()-1);
    bridgeins->onUpdateData();
}

void MainWindow::on_btnLightOn_clicked()
{
    QString strName = ui->cbLight->currentData().toString();
    bridgeins->onLightOn(strName);
}

void MainWindow::on_btnLightOff_clicked()
{
    QString strName = ui->cbLight->currentData().toString();
    bridgeins->onLightOff(strName);
}

void MainWindow::onTimeOut()
{
    //  bridgeins->onUpdateStatus();
}
