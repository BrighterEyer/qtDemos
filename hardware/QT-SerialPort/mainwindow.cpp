#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_btn_find_seriaport_clicked(); // 搜索串口
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_btn_find_seriaport_clicked()
{
    const auto infos = QSerialPortInfo::availablePorts();
    ui->cbx_com_name->clear();
    for(const QSerialPortInfo &info : infos)
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->cbx_com_name->addItem(info.portName());
            serial.close();
        }
    }
}
QSerialPort::StopBits MainWindow::to_convert_stopbit(QString  bit)
{
    if(bit == tr("1"))
        return QSerialPort::OneStop;
    else if (bit == tr("1.5"))
        return QSerialPort::OneAndHalfStop;
    else if (bit == tr("2"))
        return QSerialPort::TwoStop;
    return QSerialPort::OneStop;
}

QSerialPort::DataBits MainWindow::to_convert_databit(QString  bit)
{
    if(bit == tr("8"))
        return QSerialPort::Data8;

    if(bit == tr("7"))
        return QSerialPort::Data7;

    if(bit == tr("6"))
        return QSerialPort::Data6;

    if(bit == tr("5"))
        return QSerialPort::Data5;
    return QSerialPort::Data8;

}

QSerialPort::Parity MainWindow::to_convert_paritybit(QString  bit)
{
    if(bit == tr("None"))
        return QSerialPort::NoParity;
    if(bit == tr("Odd"))
        return QSerialPort::OddParity;
    if(bit == tr("Even"))
        return QSerialPort::EvenParity;
    return QSerialPort::NoParity;

}


void MainWindow::ReadData()
{
    static int reNum = 0;
    QByteArray buf;
    buf = serialPort->readAll();

    if (!buf.isEmpty())
    {
        reNum += buf.size();
        QString myStrTemp = QString::fromLocal8Bit(buf); //支持中文显示
        QString str = ui->tex_recv_text->toPlainText();
        str +=myStrTemp;
        ui->tex_recv_text->clear();
        ui->tex_recv_text->append(str);
    }
    buf.clear();
}
void MainWindow::on_btn_open_port_clicked()
{
    if (ui->btn_open_port->text() == tr("打开串口"))
    {
        serialPort = new QSerialPort;

        serialPort->setPortName(ui->cbx_com_name->currentText());

        if(serialPort->open(QIODevice::ReadWrite))
        {

            serialPort->setBaudRate(ui->cbx_bandrate->currentText().toInt());
            serialPort->setStopBits(to_convert_stopbit(ui->cbx_stopbit->currentText()));
            serialPort->setDataBits(to_convert_databit(ui->cbx_databit->currentText()));
            serialPort->setParity(to_convert_paritybit(ui->cbx_paritybit->currentText()));
            ui->btn_open_port->setText(tr("关闭串口"));
            ui->cbx_bandrate->setEnabled(false);
            ui->cbx_stopbit->setEnabled(false);
            ui->cbx_databit->setEnabled(false);
            ui->cbx_paritybit->setEnabled(false);
            ui->cbx_com_name->setEnabled(false);
            ui->btn_find_seriaport->setEnabled(false);
            connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::ReadData);
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), serialPort->errorString());
        }
    }
    else
    {
        serialPort->clear();
        serialPort->close();
        serialPort->deleteLater();

        ui->btn_open_port->setText(tr("打开串口"));
        ui->cbx_bandrate->setEnabled(true);
        ui->cbx_stopbit->setEnabled(true);
        ui->cbx_databit->setEnabled(true);
        ui->cbx_paritybit->setEnabled(true);
        ui->cbx_com_name->setEnabled(true);
        ui->btn_find_seriaport->setEnabled(true);
    }
}


void MainWindow::on_btn_clear_recv_clicked()
{
    ui->tex_recv_text->clear();
}


void MainWindow::on_btn_send_message_clicked()
{
    serialPort->write(ui->tex_send_text->toPlainText().toLocal8Bit());
}
