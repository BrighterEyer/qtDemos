#include "ui_mqtt.h"
#include "ui_ui_mqtt.h"

ui_mqtt::ui_mqtt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_mqtt)
{
    ui->setupUi(this);
  //  m_client             =  new QMqttClient(this);
}

ui_mqtt::~ui_mqtt()
{
    delete ui;
}

void ui_mqtt::on_btn_mqtt_connect_clicked()
{
    //f (m_client->state() == QMqttClient::Disconnected) {
    //      ui->btn_mqtt_connect->setText(tr("Disconnect"));
    //      m_client->setHostname("192.168.3.102");
    //      m_client->setPort(1883);
    //     // qleHostName->setEnabled(false);
    //    //  qleHostPort->setEnabled(false);
    //      m_client->connectToHost();
    //  } else {//断开连接
    //      ui->btn_mqtt_connect->setText(tr("Connect"));
    //     // qleHostName->setEnabled(true);
    //     // qleHostPort->setEnabled(true);
    //      m_client->disconnectFromHost();
    //  }
}
