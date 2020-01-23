#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
//#include <QPoint>

class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    DrawWidget(QWidget *parent = 0);
    ~DrawWidget();

private:
    int style;
    int weight;
    QColor color;
    QPoint startPos;
    QPixmap *pix;

public:
    void setStyle (int s);
    void setWidth (int w);
    void setColor (QColor c);
    void mousePressEvent (QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);
    void clear();


};

#endif // DRAWWIDGET_H
