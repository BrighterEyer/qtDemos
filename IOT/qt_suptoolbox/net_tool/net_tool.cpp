#include "net_tool.h"
#include "ui_net_tool.h"

net_tool::net_tool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::net_tool)
{
    ui->setupUi(this);
}

net_tool::~net_tool()
{
    delete ui;
}

void net_tool::on_cbx_select_net_func_currentIndexChanged(const QString &arg1)
{
    if (ui->cbx_select_net_func->currentText() == tr("TCP服务器"))
    {
        ui->stw_select_net_func->setCurrentWidget(ui->page_tcp_server);
    }
    if (ui->cbx_select_net_func->currentText() == tr("TCP客户端"))
    {
        ui->stw_select_net_func->setCurrentWidget(ui->page_tcp_client);
    }
    if (ui->cbx_select_net_func->currentText() == tr("UDP服务器"))
    {

    }
    if (ui->cbx_select_net_func->currentText() == tr("UDP客户端"))
    {

    }
}
