#include "form.h"
#include "ui_form.h"
#include "serial_tool.h"
#include "Ymodem/ui_ymodem.h"
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QStyle>
#include <QDebug>
#include "qprocess.h"
#include <QDesktopServices>


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    this->setWindowTitle("成竹调试工具合集");
    this->ss_ui = new serial_tool(this);
    this->ymodme_ui = new ui_ymodem(this);
    this->net_ui = new net_tool(this);
    this->gprs_ui = new gprs_nb_tool(this);
    this->check_ui = new check();
    this->ascii_ui = new ascii();
    this->format_ui = new format();
    //this->mqtt_ui = new ui_mqtt(this);

    this->check_ui->setWindowFlags(this->check_ui->windowFlags() &~ Qt::WindowMaximizeButtonHint); //设置禁止最大化
    this->check_ui->setWindowTitle("校验位计算小工具");

    this->ascii_ui->setWindowFlags(this->ascii_ui->windowFlags() &~ Qt::WindowMaximizeButtonHint); //设置禁止最大化
    this->ascii_ui->setWindowTitle("ASCII 码表");

    this->format_ui->setWindowFlags(this->format_ui->windowFlags() &~ Qt::WindowMaximizeButtonHint); //设置禁止最大化
    this->format_ui->setWindowTitle("HEX格式化");

    ui->frameMenu->resize(this->geometry().width(), ui->frameMenu->height());
    //ui->frameMenu->setFrameStyle();
    QMenuBar *pMenuBar = new QMenuBar(ui->frameMenu);
    QMenu *pMenuBarFile= new QMenu(QStringLiteral("文件"),this);


    QAction *pActionOpen = new QAction(QStringLiteral("打开"), this);
    pActionOpen->setIcon(QIcon(":/new/prefix1/img/open.png"));
    pActionOpen->setShortcut(Qt::CTRL | Qt::Key_O);


    QAction *pActionSave = new QAction(QStringLiteral("保存"), this);
    pActionSave->setIcon(QIcon(":/new/prefix1/img/save.png"));
    pActionSave->setShortcut(Qt::CTRL | Qt::Key_S);
    pMenuBarFile->addAction(pActionOpen);
    pMenuBarFile->addAction(pActionSave);
    pMenuBar->addMenu(pMenuBarFile);

    // 工具菜单

    QMenu *pMenuBarTool= new QMenu(QStringLiteral("工具"),this);
     pMenuBar->addMenu(pMenuBarTool);
    //校验小工具
    QAction *pActionCheck = new QAction(QStringLiteral("校验"), this);
    pActionCheck->setIcon(QIcon(":/new/prefix1/img/check.png"));
    connect(pActionCheck, &QAction::triggered, this, &Form::CheckAction);
    pMenuBarTool->addAction(pActionCheck);

    //计算器工具
    //QMenu *pMenuBarTool= new QMenu(QStringLiteral("工具"),this);
    QAction *pActionCalc = new QAction(QStringLiteral("计算器"), this);
    pActionCalc->setIcon(QIcon(":/new/prefix1/img/calc.png"));
    connect(pActionCalc, &QAction::triggered, this, &Form::CalcAction);
    pMenuBarTool->addAction(pActionCalc);


    //ascii
    QAction *pActionAscii = new QAction(QStringLiteral("ASCII码表"), this);
    pActionAscii->setIcon(QIcon(":/new/prefix1/img/ascii.png"));
    connect(pActionAscii, &QAction::triggered, this, &Form::AsciiAction);
    pMenuBarTool->addAction(pActionAscii);

    QAction *pActionFomat = new QAction(QStringLiteral("HEX格式化"), this);
    pActionFomat->setIcon(QIcon(":/new/prefix1/img/ascii.png"));
    connect(pActionFomat, &QAction::triggered, this, &Form::FormatAction);
    pMenuBarTool->addAction(pActionFomat);



    // 帮助菜单
    QMenu *pMenuBarHelp= new QMenu(QStringLiteral("帮助"),this);
    pMenuBar->addMenu(pMenuBarHelp);

    //帮助文档
    QAction *pActionHelp = new QAction(QStringLiteral("帮助文档"), this);
    pActionHelp->setIcon(QIcon(":/new/prefix1/img/help.png"));
    connect(pActionHelp, &QAction::triggered, this, &Form::HelpAction);
    pMenuBarHelp->addAction(pActionHelp);

    //检查更新
    QAction *pActionUpdate = new QAction(QStringLiteral("检查更新"), this);
    pActionUpdate->setIcon(QIcon(":/new/prefix1/img/updatess.png"));
    connect(pActionUpdate, &QAction::triggered, this, &Form::UpdateAction);
    pMenuBarHelp->addAction(pActionUpdate);

    //关于软件
    QAction *pActionAbout = new QAction(QStringLiteral("关于软件"), this);
    pActionAbout->setIcon(QIcon(":/new/prefix1/img/about.png"));
    connect(pActionAbout, &QAction::triggered, this, &Form::AboutAction);
    pMenuBarHelp->addAction(pActionAbout);


    pMenuBar->setFixedSize(ui->frameMenu->width(), ui->frameMenu->height());
    pMenuBar->setStyleSheet("background-color: rgb(240, 240, 240);");



  //  ui->tabWidget
    ui->tabWidget->addTab(ss_ui,QIcon(":/new/prefix1/img/serialport.png"),"串口日志");
    ui->tabWidget->addTab(ymodme_ui,QIcon(":/new/prefix1/img/update.png"),"固件升级");
    ui->tabWidget->addTab(net_ui,QIcon(":/new/prefix1/img/net.png"),"网络调试");
    ui->tabWidget->addTab(gprs_ui,QIcon(":/new/prefix1/img/gprs.png"),"GPRS-NB");
    ui->tabWidget->addTab(gprs_ui,QIcon(":/new/prefix1/img/MQTT.png"),"MQTT调试");
    connect(ss_ui,SIGNAL(setstatemsg(QString,QString)),this,SLOT(set_state_msg(QString,QString)));


}

Form::~Form()
{
    delete ui;
    delete ss_ui;
    delete ymodme_ui;
    delete net_ui;
    delete gprs_ui;
    delete check_ui;

}

void Form::CheckAction(void)
{
    qDebug()<< "CheckAction";
    check_ui->setVisible(true);
}

void Form:: CalcAction(void)
{
    QProcess::startDetached("calc\n");
}

void Form:: AsciiAction(void)
{
    ascii_ui->setVisible(true);
}

void Form:: HelpAction(void)
{

    QDesktopServices::openUrl(QUrl("https://www.memory6181.com/archives/53/"));
}

void Form:: AboutAction(void)
{
    QDesktopServices::openUrl(QUrl("https://www.memory6181.com/archives/53/"));
}
void Form:: UpdateAction(void)
{
    QDesktopServices::openUrl(QUrl("https://www.memory6181.com/archives/53/"));
}

void Form:: FormatAction(void)
{
    format_ui->setVisible(true);
}

void Form::set_state_msg(QString color,QString str)
{
    // QColor(Qt::red)
    //QPalette palette = ui->state_lable->palette(); // 获取调色板
    //palette.setColor(QPalette::WindowText,color); // 设置字体颜色
    ui->state_lable->setStyleSheet("font: 12pt \"Microsoft JhengHei UI\";"+color);
  //  ui->state_lable->setPalette(palette);         // 设置调色板
    ui->state_lable->setText(str);
}
