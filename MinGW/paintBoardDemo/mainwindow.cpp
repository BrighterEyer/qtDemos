#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
//  ,ui(new Ui::MainWindow)
{
    //    ui->setupUi(this);

    drawWidget = new DrawWidget;           //新建一个DrawWidget对象--能够响应鼠标事件进行绘图功能的窗体类
    setCentralWidget(drawWidget);         //新建的DrawWidget对象作为主窗口的中央窗体
    createToolBar();                      //实现一个工具栏
    setMinimumSize(600, 400);             //设置主窗口的最小尺寸
    ShowStyle();                          //初始化线型,设置控件中的当前值作为初始值
    drawWidget->setWidth(widthSpinBox->value());        //初始化线宽
    drawWidget->setColor(Qt::black);                     //初始化颜色
}

//工具栏创建
void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tool");          //为主窗口新建一个工具栏对象
    styleLabel = new QLabel(tr("线型风格: "));        //创建线性选择控件
    styleComboBox = new QComboBox;
    styleComboBox->addItem(tr("SolidLine"),static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem(tr("DashLine"),static_cast<int>(Qt::DashLine));
    styleComboBox->addItem(tr("DotLine"),static_cast<int>(Qt::DotLine));
    styleComboBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotLine));
    styleComboBox->addItem(tr("DashDotDotLine"),static_cast<int>(Qt::DashDotDotLine));
    connect(styleComboBox, SIGNAL(activated(int)), this, SLOT(ShowStyle()));  //关联相应的槽函数
    widthLabel = new QLabel(tr("线宽: "));            //创建线宽选择控件
    widthSpinBox = new QSpinBox;
    connect(widthSpinBox, SIGNAL(valueChanged(int)), drawWidget, SLOT(setWidth(int)));

    colorBtn = new QToolButton;                      //创建颜色选择控件
    QPixmap pixmap(20, 20);                          //颜色选择按钮控件上的图像
    pixmap.fill(Qt::black);                         //填充黑色
    colorBtn->setIcon(QIcon(pixmap));               //设置按钮图像
    connect(colorBtn, SIGNAL(clicked(bool)), this, SLOT(ShowColor()));

    clearBtn = new QToolButton();                    //创建清除按钮
    clearBtn->setText(tr("清除"));
    connect(clearBtn, SIGNAL(clicked(bool)), drawWidget, SLOT(clear()));

    toolBar->addWidget(styleLabel);
    toolBar->addWidget(styleComboBox);
    toolBar->addWidget(widthLabel);
    toolBar->addWidget(widthSpinBox);
    toolBar->addWidget(colorBtn);
    toolBar->addWidget(clearBtn);
}

//ShowStyle(),通过调用DrawWidget类的setStyle()函数将当前线型选择控件中的线型参数传给绘制区;
void MainWindow::ShowStyle()
{
    drawWidget->setStyle(styleComboBox->itemData(styleComboBox->currentIndex(),Qt::UserRole).toInt());
}

//ShowColor(),通过DrawWidget类的setColor()函数将用户在标准颜色对话框中选择的颜色值传给绘制区
void MainWindow::ShowColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black));   //默认为黑(static_cast<int>转换成int节省内存
    //使用标准颜色对话框QColorDialog获得一个颜色值
    if(color.isValid())
    {
        //先将新选择的颜色传给绘制区,用于改变画笔的颜色值
        drawWidget->setColor(color);
        //改变按钮图案
        QPixmap p(20, 20);                           //设置图像大小
        p.fill(color);                              //填充颜色
        colorBtn->setIcon(QIcon(p));                //设置颜色按钮图案
    }
}

MainWindow::~MainWindow()
{
//    delete ui;
}
