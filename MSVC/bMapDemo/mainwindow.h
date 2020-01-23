#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onTimeOut();

    void on_btnAddLight_clicked();

    void on_btnLightOn_clicked();

    void on_btnLightOff_clicked();

private:
    Ui::MainWindow *ui;
    QTimer m_timer;
    void InitForm();

    QWebEngineView *webView;
};

#endif // MAINWINDOW_H
