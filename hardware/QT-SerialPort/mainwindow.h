#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_find_seriaport_clicked();

    void on_btn_open_port_clicked();

    void on_btn_clear_recv_clicked();


    void on_btn_send_message_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;

    QSerialPort::StopBits to_convert_stopbit(QString bit);
    QSerialPort::DataBits to_convert_databit(QString  bit);
    QSerialPort::Parity to_convert_paritybit(QString  bit);
    void ReadData();
};

#endif // MAINWINDOW_H
