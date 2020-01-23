#pragma once

#ifndef SLIDERDEMO_H
#define SLIDERDEMO_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class SliderDemo;
}

class SliderDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit SliderDemo(QWidget *parent = nullptr);
    ~SliderDemo();

public slots:
    void slotStart();
    void slotStop();
    void slotProcessBar();

private:
    Ui::SliderDemo *ui;
    QTimer *m_timer;
};

#endif // SLIDERDEMO_H
