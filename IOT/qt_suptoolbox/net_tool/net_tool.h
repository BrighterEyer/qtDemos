#ifndef NET_TOOL_H
#define NET_TOOL_H

#include <QWidget>

namespace Ui {
class net_tool;
}

class net_tool : public QWidget
{
    Q_OBJECT

public:
    explicit net_tool(QWidget *parent = nullptr);
    ~net_tool();

private slots:
    void on_cbx_select_net_func_currentIndexChanged(const QString &arg1);

private:
    Ui::net_tool *ui;
};

#endif // NET_TOOL_H
