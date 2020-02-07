#ifndef FORMAT_H
#define FORMAT_H

#include <QWidget>

namespace Ui {
class format;
}

class format : public QWidget
{
    Q_OBJECT

public:
    explicit format(QWidget *parent = nullptr);
    ~format();

private:
    Ui::format *ui;
};

#endif // FORMAT_H
