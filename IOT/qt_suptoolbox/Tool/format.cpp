#include "format.h"
#include "ui_format.h"

format::format(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::format)
{
    ui->setupUi(this);
}

format::~format()
{
    delete ui;
}
