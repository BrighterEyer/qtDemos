#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QAction>
#include<QMenu>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //声明动作
    QAction * buttonAction1;
    QAction * buttonAction2;

    QAction * lableAction1;
    QAction * lableAction2;
    //声明菜单
    QMenu * buttonMenu;
    QMenu * lableMenu;
};

#endif // MAINWINDOW_H
