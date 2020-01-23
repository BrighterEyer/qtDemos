#include "drawwidget.h"
#include <QtGui>
#include <QPen>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);             //对窗体背景色的设置
    setPalette(QPalette(Qt::white));         //背景色为白
    pix = new QPixmap(size());                //此QPixmap对象用来准备随时接受绘制的内容
    pix->fill(Qt::white);                    //填充背景色为白色
    setMinimumSize(600, 400);                //设置绘制区窗体的最小尺寸
}

//接受主窗体传来的线型风格参数
void DrawWidget::setStyle(int s)
{
    style = s;
}

//setWidth()接受主窗体传来的线宽参数值
void DrawWidget::setWidth(int w)
{
    weight = w;
}

//接受主窗体传来的画笔颜色值
void DrawWidget::setColor(QColor c)
{
    color = c;
}

//重定义鼠标按下事件--按下鼠标时,记录当前鼠标位置值startPos
void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    startPos = e->pos();
}

//重定义鼠标移动事件--默认情况下,在鼠标按下的同时拖曳鼠标时被触发.
//mouseTracking事件,可以通过设置setMouseTracking(bool enable)为true,
//则无论是否有鼠标键按下,只要鼠标移动,就会触发mouseMoveEvent()
//在此函数中,完成向QPixmap对象中绘图的工作.
void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPainter *painter = new QPainter;            //新建一个QPainter对象
    QPen pen;                                    //新建一个QPen对象
    //设置画笔的线型,style表示当前选择的线型是Qt::PenStyle枚举数据中的第几个元素
    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight);                       //设置画笔的线宽值
    pen.setColor(color);                        //设置画笔的颜色
    /***
     * 以QPixmap对象为QPaintDevice参数绘制,构造一个QPainter对象,
     * 就立即开始对绘画设备进行绘制,此构造QPainter对象是短期的
     * 由于当一个QPainter对象的初始化失败时构造函数不能提供反馈信息,
     * 所以在绘制 外部设备时 应使用begin()和end()(Ps:如打印机外部设备)
     */
    painter->begin(pix);
    painter->setPen(pen);                       //将QPen对象应用到绘制对象当中
    //绘制从startPos到鼠标当前位置的直线
    painter->drawLine(startPos, e->pos());
    painter->end();                             //绘制成功返回true
    startPos = e->pos();                        //更新鼠标的当前位置,为下次绘制做准备
    update();                                   //重绘绘制区窗体
}

/***
 * 重画函数paintEvent()完成绘制区窗体的更新工作,只需要调用drawPixmap()函数将用于接收图形绘制的
 * 的QPixmap对象绘制在绘制区窗体控件上即可.
 */
void DrawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0), *pix);
}

/***
 * 调整绘制区大小函数resizeEvent():
 * 当窗体大小改变是，实际能够绘制的区域仍然没有改变,因为绘图的大小没有改变
 * 所以窗体尺寸变化时，应及时调整用于绘制的QPixmap对象的尺寸大小
 */
void DrawWidget::resizeEvent(QResizeEvent *event)
{
    //判断改变后的窗体长或宽是否大于原窗体的长和宽;
    //若大于则进行相应调整;
    if(height() > pix->height() || width() > pix->width())
    {
        QPixmap *newPix = new QPixmap(size());         //创建一个新的QPixmap对象
        newPix->fill(Qt::white);                      //填充新QPixmap对象newPix的颜色为白色背景色
        QPainter p(newPix);
        p.drawPixmap(QPoint(0, 0), *pix);             //在newPix中绘制原pix中内容
        pix = newPix;                                  //将newPix赋值给Pix作为新的绘制图形接收对象
    }
    //否则直接调用QWidget的resizeEvent()函数返回
    QWidget::resizeEvent(event);                      //完成其余工作

}

/***
 * clear()函数完成绘制区的清除工作,只需要一个新的，干净的QPixmap对象代替pix,并调用update()重绘即可
 */
void DrawWidget::clear()
{
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    pix = clearPix;
    update();
}

DrawWidget::~DrawWidget(){

}
