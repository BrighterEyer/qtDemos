#include "ascii.h"
#include "ui_ascii.h"

ascii::ascii(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ascii)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
}

ascii::~ascii()
{
    delete ui;
}
