#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>
#include "YmodemFileTransmit.h"
#include "YmodemFileReceive.h"
#include "serial_tool.h"
#include "ui_ymodem.h"

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


private:
    Ui::MainWindow *ui;
    serial_tool *ss_ui;
    ui_ymodem * ymodme_ui;
    QSerialPort *serialPort;


    QSettings * setting  = new QSettings("./Setting.ini",QSettings::IniFormat);




    void OpenSerialPort();
};

#endif // MAINWINDOW_H
