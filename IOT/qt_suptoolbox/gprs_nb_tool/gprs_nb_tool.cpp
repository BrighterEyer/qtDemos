#include "gprs_nb_tool.h"
#include "ui_gprs_nb_tool.h"

gprs_nb_tool::gprs_nb_tool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gprs_nb_tool)
{
    ui->setupUi(this);
}

gprs_nb_tool::~gprs_nb_tool()
{
    delete ui;
}
