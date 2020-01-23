#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    /* 保存路径*/
    QString runPath;
    QString hglpName;
    QString hglpPath;


private slots:
    void choosePicture();
    void saveToOtherPath();
    void save();

};

#endif // MAINWINDOW_H
