#include "serial_tool.h"
#include "ui_serial_tool.h"
#include  <QSerialPort>
#include  <QSerialPortInfo>
#include <QMessageBox>
#include "convert.h"
#include <QtCore>
#include <QAbstractItemView>
#include  <QSplitter>

serial_tool::serial_tool(QWidget *parent) :
    QWidget(parent),
    serialPort(new QSerialPort),
    ui(new Ui::serial_tool)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();
    Find_SerialPort();
    //this->serialPort = serialport;
    tx_timer = new QTimer();
    led_timer = new QTimer();
    connect(tx_timer,SIGNAL(timeout()),this,SLOT(tx_timer_irq()));
    connect(led_timer,SIGNAL(timeout()),this,SLOT(led_timer_irq()));
    led_timer->start(1);// 启动定时器 1ms


    QSplitter *splitter = new QSplitter(Qt::Vertical, this);   //创建上下分割的对象
    // splitter->setOpaqueResize(true);
    ui->groupBoxRecv->setParent(splitter);  //设置textEdit的父容器为QSplitter， textEdit在布局页面拖拽生成，
    ui->tab_send->setParent(splitter); //设置tabWidget的父容器为QSplitter，tabWidget在布局页面拖拽生成，
    ui->horizontalLayout_6->addWidget(splitter);
}

serial_tool::~serial_tool()
{
    delete ui;
}
void serial_tool::ReadData()
{
    static int reNum = 0;
    QByteArray buf;
    QString myStrTemp,str;
    buf = serialPort->readAll();
    ui->lab_img_recv_data->setPixmap(QPixmap(":/new/prefix1/img/green.png"));
    recv_led_timer = 200;
    if(ui->pCheckBoxTimerPick->isChecked())
    {
        QTime t=QTime::currentTime();
        myStrTemp = "\r\n["+t.toString("HH:mm:ss")+"]";
        str = ui->tex_recv_text->toPlainText();
        str +=myStrTemp;
        ui->tex_recv_text->clear();
        ui->tex_recv_text->appendPlainText(str);
    }
    if (!buf.isEmpty())
    {
        if (ui->radio_recv_hex->isChecked())
        {
            myStrTemp =  Convert::ByteArrayToHexString(buf);
        }
        else
        {
            myStrTemp=QString::fromLocal8Bit(buf); //支持中文显示
        }
        reNum += buf.size();
        str = ui->tex_recv_text->toPlainText();
        str +=myStrTemp;
        ui->tex_recv_text->clear();
        ui->tex_recv_text->appendPlainText(str);
    }
    buf.clear();
}

void serial_tool::on_btn_send_message_clicked()
{
    QByteArray buff;
    if (!serialPort->isOpen())
    {
        setstatemsg("color:red;",u8"串口未打开");
        //QMessageBox::critical(this, tr("Error"), u8"串口未打开");
        return ;
    }
    if (ui->radio_send_hex->isChecked())
    {
        buff = Convert::HexStringToByteArray(ui->tex_send_text->toPlainText());
        if (buff.isNull())
        {
            setstatemsg("color:red;",u8"输入格式错误");
            //QMessageBox::critical(this, tr("Error"), u8"输入格式有误");
            return;
        }
    }
    else {
        QString str;
        str = ui->tex_send_text->toPlainText();
        if (ui->qcheckBox_newline->isChecked())
        {
            str = str +"\r\n";
        }
        buff = str.toLocal8Bit();
    }
    QPixmap bgImage(":/new/prefix1/img/green.png");
    ui->lab_send->setPixmap(bgImage);
    tx_led_timer = 200;
    serialPort->write(buff);
}
void serial_tool::tx_timer_irq()
{
    if ((serialPort->isOpen() == false))
    {
        this->tx_timer->stop();
        ui->chb_timer_send->setCheckState(Qt::Unchecked);
        ui->btn_send_message->setEnabled(true);
        ui->sb_timer_send->setEnabled(true);
        //QMessageBox::warning(this, u8"失败", u8"串口意外中断", u8"关闭");
        return ;
    }
    QByteArray buff;
    if (ui->radio_send_hex->isChecked())
    {
        buff = Convert::HexStringToByteArray(ui->tex_send_text->toPlainText());
        if (buff.isNull())
        {
            this->tx_timer->stop();
            ui->chb_timer_send->setCheckState(Qt::Unchecked);
            setstatemsg("color:red;",u8"输入格式错误");
            //QMessageBox::critical(this, tr("Error"), u8"输入格式有误");
            return;
        }
    }
    else {
        buff = ui->tex_send_text->toPlainText().toLocal8Bit();
    }
    QPixmap bgImage(":/new/prefix1/img/green.png");
    ui->lab_send->setPixmap(bgImage);
    tx_led_timer = 300;
    serialPort->write(buff);
}
void serial_tool::led_timer_irq()
{

    if (tx_led_timer > 0)
    {
        tx_led_timer--;
        if (tx_led_timer == 0)
            ui->lab_send->setPixmap(QPixmap(":/new/prefix1/img/red.png"));
    }
    if (find_led_timer > 0)
    {
        find_led_timer--;
        if (find_led_timer == 0)
            ui->lab_img_find_serial->setPixmap(QPixmap(":/new/prefix1/img/red.png"));
    }
    if (recv_led_timer > 0)
    {
        recv_led_timer--;
        if (recv_led_timer == 0)
            ui->lab_img_recv_data->setPixmap(QPixmap(":/new/prefix1/img/red.png"));
    }


}

void serial_tool::on_btn_clear_recv_clicked()
{
    ui->tex_recv_text->clear();
}

void serial_tool::on_chb_timer_send_stateChanged(int arg1)
{

    if(ui->chb_timer_send->isChecked())
    {
        if (!serialPort->isOpen())
        {
            ui->chb_timer_send->setCheckState(Qt::Unchecked);
            setstatemsg("color:red;",u8"串口未打开");
            //QMessageBox::warning(this, u8"Error", u8"串口未打开", u8"关闭");
            return ;
        }
        ui->btn_send_message->setEnabled(false);
        ui->sb_timer_send->setEnabled(false);
        this->tx_timer->start(ui->sb_timer_send->value());
    }
    else
    {
        this->tx_timer->stop();
        ui->btn_send_message->setEnabled(true);
        ui->sb_timer_send->setEnabled(true);
    }
}

void serial_tool::on_btn_find_seriaport_clicked()
{
    Find_SerialPort();
}


QSerialPort::StopBits serial_tool::to_convert_stopbit(QString  bit)
{
    if(bit == tr("1"))
        return QSerialPort::OneStop;
    else if (bit == tr("1.5"))
        return QSerialPort::OneAndHalfStop;
    else if (bit == tr("2"))
        return QSerialPort::TwoStop;
    return QSerialPort::OneStop;
}

QSerialPort::DataBits serial_tool::to_convert_databit(QString  bit)
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

QSerialPort::Parity serial_tool::to_convert_paritybit(QString  bit)
{
    if(bit == tr("None"))
        return QSerialPort::NoParity;
    if(bit == tr("Odd"))
        return QSerialPort::OddParity;
    if(bit == tr("Even"))
        return QSerialPort::EvenParity;
    return QSerialPort::NoParity;

}

void serial_tool::on_btn_open_port_clicked()
{
    QString ComName = ui->cbx_com_name->currentText().mid(0,ui->cbx_com_name->currentText().indexOf(' '));;
    if (ui->btn_open_port->text() == QObject::tr("打开串口"))
    {
        serialPort->setPortName(ComName);

        if(serialPort->open(QIODevice::ReadWrite))
        {
            serialPort->setBaudRate(ui->cbx_bandrate->currentText().toInt());
            serialPort->setStopBits(to_convert_stopbit(ui->cbx_stopbit->currentText()));
            serialPort->setDataBits(to_convert_databit(ui->cbx_databit->currentText()));
            serialPort->setParity(to_convert_paritybit(ui->cbx_paritybit->currentText()));
            ui->btn_open_port->setText(QObject::tr("关闭串口"));
            ui->cbx_bandrate->setEnabled(false);
            ui->cbx_stopbit->setEnabled(false);
            ui->cbx_databit->setEnabled(false);
            ui->cbx_paritybit->setEnabled(false);
            ui->cbx_com_name->setEnabled(false);
            ui->btn_find_seriaport->setEnabled(false);
            ui->lab_img_openport->setPixmap(QPixmap(":/new/prefix1/img/green.png"));
            //this->ss_ui->connected_serial_port();
            connect(serialPort, &QSerialPort::readyRead, this, &serial_tool::ReadData);
            setstatemsg("color:green;",u8"打开串口:"+ComName+u8",波特率:"+ui->cbx_bandrate->currentText());
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Error"), serialPort->errorString());
        }
    }
    else
    {
        serialPort->clear();
        serialPort->close();
        // serialPort->deleteLater();
        ui->lab_img_openport->setPixmap(QPixmap(":/new/prefix1/img/red.png"));
        ui->btn_open_port->setText(QObject::tr(u8"打开串口"));
        ui->cbx_bandrate->setEnabled(true);
        ui->cbx_stopbit->setEnabled(true);
        ui->cbx_databit->setEnabled(true);
        ui->cbx_paritybit->setEnabled(true);
        ui->cbx_com_name->setEnabled(true);
        ui->btn_find_seriaport->setEnabled(true);
        setstatemsg("color:red;",u8" 串口"+ComName+u8"关闭");
    }
}
void serial_tool::Find_SerialPort()
{
    const auto infos = QSerialPortInfo::availablePorts();
    ui->lab_img_find_serial->setPixmap(QPixmap(":/new/prefix1/img/green.png"));
    ui->cbx_com_name->clear();
    QTimer *time = new QTimer ();
    time->start(500);
    for(const QSerialPortInfo &info : infos)
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->cbx_com_name->addItem(info.portName()+"              "+info.description());
            serial.close();
        }
    }
    find_led_timer = 200;
    int max_len=0;
    for(int idx=0;idx < ui->cbx_com_name->count();idx++)
    {
        if(max_len < ui->cbx_com_name->itemText(idx).length())
            max_len = ui->cbx_com_name->itemText(idx).length();
    }
    int pt_val = this->font().pointSize();//获取字体的磅值
    const_cast<QAbstractItemView*>(ui->cbx_com_name->view())->setMinimumWidth(max_len*pt_val*0.75);
}
