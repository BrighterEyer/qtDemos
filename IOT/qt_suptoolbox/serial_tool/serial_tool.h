#ifndef SERIAL_TOOL_H
#define SERIAL_TOOL_H
#include  <QSerialPort>
#include <QtCore>
#include <QWidget>

namespace Ui {
class serial_tool;
}

class serial_tool : public QWidget
{
    Q_OBJECT
public:

    explicit serial_tool(QWidget *parent = nullptr);
    ~serial_tool();

    void connected_serial_port(void);
    void disconnected_serial_port(void);

signals:
    void setstatemsg(QString color,QString str);

private slots:
    void on_btn_send_message_clicked();
    void tx_timer_irq();
    void led_timer_irq();
    void ReadData();

    void on_btn_clear_recv_clicked();

    void on_chb_timer_send_stateChanged(int arg1);

    void on_btn_find_seriaport_clicked();

    void on_btn_open_port_clicked();

private:
    QSerialPort *serialPort;
    Ui::serial_tool *ui;
    QTimer *tx_timer;
    QTimer *led_timer;

    int tx_led_timer = 0;
    int find_led_timer = 0;
    int recv_led_timer = 0;

    void Find_SerialPort();
    QSerialPort::StopBits to_convert_stopbit(QString bit);
    QSerialPort::DataBits to_convert_databit(QString  bit);
    QSerialPort::Parity to_convert_paritybit(QString  bit);





};

#endif // SERIAL_TOOL_H
