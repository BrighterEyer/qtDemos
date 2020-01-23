#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMessageHandler>
#include <QDateTime>
#include <QMutex>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QProgressBar>
#include <QProgressDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void myMessageOutput(QtMsgType, const QMessageLogContext&, const QString&);
};

#endif // MAINWINDOW_H
