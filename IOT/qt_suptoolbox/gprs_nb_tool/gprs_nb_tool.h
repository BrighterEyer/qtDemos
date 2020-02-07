#ifndef GPRS_NB_TOOL_H
#define GPRS_NB_TOOL_H

#include <QWidget>

namespace Ui {
class gprs_nb_tool;
}

class gprs_nb_tool : public QWidget
{
    Q_OBJECT

public:
    explicit gprs_nb_tool(QWidget *parent = nullptr);
    ~gprs_nb_tool();

private:
    Ui::gprs_nb_tool *ui;
};

#endif // GPRS_NB_TOOL_H
