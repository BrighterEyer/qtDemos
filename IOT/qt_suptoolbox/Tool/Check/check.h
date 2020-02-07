#ifndef CHECK_H
#define CHECK_H

#include <QWidget>

namespace Ui {
class check;
}

class check : public QWidget
{
    Q_OBJECT

public:
    explicit check(QWidget *parent = nullptr);
    ~check();

private slots:
    void on_btn_calc_clicked();

private:
    Ui::check *ui;



    unsigned char CalcCheckSum(QByteArray buff);
};

#endif // CHECK_H
