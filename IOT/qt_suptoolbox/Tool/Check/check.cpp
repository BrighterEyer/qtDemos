#include "check.h"
#include "ui_check.h"
#include <convert.h>

check::check(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::check)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
}

check::~check()
{
    delete ui;
}

void check::on_btn_calc_clicked()
{
    QByteArray buff;
    unsigned int result = 0;
    buff = Convert::HexStringToByteArray(ui->PtextBoxSrcdata->toPlainText());
    result = (unsigned int)CalcCheckSum(buff);
    ui->PlineBoxObjdata->setText(QString::number(result,16).toUpper());
}

unsigned char check::CalcCheckSum(QByteArray buff)
{
    unsigned char sum = 0;
    for(int i =0;i < buff.length();i++)
    {
        sum = sum +buff[i];
    }
    return sum;
}
