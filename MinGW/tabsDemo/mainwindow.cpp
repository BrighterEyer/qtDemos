#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPlainTextEdit>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(OnbtnAdd()));
    connect(ui->btnDelete,SIGNAL(clicked()),this,SLOT(OnbtnDelete()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::OnbtnAdd()
{

    QPlainTextEdit* page = new QPlainTextEdit();
    ui->tabWidget->addTab(page,"标签");

    return 0;
}
int MainWindow::OnbtnDelete()
{
    int index = ui->tabWidget->currentIndex();
    ui->tabWidget->removeTab(index);
    return 0;
}
