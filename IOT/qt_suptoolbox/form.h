#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "serial_tool.h"
#include "ui_ymodem.h"
#include "net_tool/net_tool.h"
#include "gprs_nb_tool/gprs_nb_tool.h"
#include "Tool/Check/check.h"
#include "Tool/ascii.h"
#include "mqtt/ui_mqtt.h"
#include "Tool/format.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void CheckAction(void);
    void CalcAction(void);
    void AsciiAction(void);
    void HelpAction(void);
    void AboutAction(void);
    void UpdateAction(void);
    void FormatAction(void);

    void set_state_msg(QString color,QString str);

private:
    Ui::Form *ui;
    serial_tool *ss_ui;
    ui_ymodem * ymodme_ui;
    net_tool * net_ui;
    gprs_nb_tool * gprs_ui;
    check * check_ui;
    ascii * ascii_ui;
    ui_mqtt * mqtt_ui;
    format * format_ui;

};

#endif // FORM_H
