#ifndef ASCII_H
#define ASCII_H

#include <QWidget>

namespace Ui {
class ascii;
}

class ascii : public QWidget
{
    Q_OBJECT

public:
    explicit ascii(QWidget *parent = nullptr);
    ~ascii();

private:
    Ui::ascii *ui;
};

#endif // ASCII_H
