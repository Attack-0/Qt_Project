#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,rtAngle(0.0)
{
    ui->setupUi(this);

    connect(this,SIGNAL(luckStartSignal()),this,
            SLOT(luckStartSlot()));

    connect(&rtTimer,SIGNAL(timeout()),this,SLOT(rtTimerOutSlot()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    // 先准备一个画笔
    rotationPainter.begin(this);
    // 移动坐标
    rotationPainter.translate(200,200);
    // 旋转
    rotationPainter.rotate(rtAngle);
    // 设置反锯齿
    rotationPainter.setRenderHints(QPainter::SmoothPixmapTransform);
    // 0,0 为POS
    rotationPainter.drawPixmap(-200,-200,400,400,QPixmap(":/img/1.jpg")); // pos
    rotationPainter.end();

    // 绘制指针
    pointPainter.begin(this);
    pointPainter.translate(200,200);// 原点移动
    static const QPoint point[4] = {QPoint(0,18),QPoint(20,0),
                                    QPoint(0,-100),QPoint(-20,0)};
    // 设置画笔
    pointPainter.setBrush(QColor(Qt::darkBlue));
    // 添加反锯齿（走样） 设置抗锯齿需要再绘图之前添加
    pointPainter.setRenderHints(QPainter::Antialiasing);
    // 描点画出多边形
    pointPainter.drawPolygon(point, 4);

    // 多边形
    QRect recatanle(-7,-7,14,18);
    pointPainter.setBrush(QColor(Qt::yellow));
    pointPainter.drawEllipse(recatanle);
    pointPainter.end();
}

void Widget::rtTimerOutSlot()
{
    rtAngle++; //旋转因子

    if((rtAngle - randNumber) == 90)
    {
        rtTimer.setInterval(10);
    }
    else if((rtAngle - randNumber) == 180)

    {
        rtTimer.setInterval(15);
    }
    else if((rtAngle - randNumber) == 270)
    {
        rtTimer.setInterval(20);
    }
    else if((rtAngle - randNumber) == 360)
    {
        rtAngle--; //停下来
    }
    update(); // 更新视图
}

void Widget::luckStartSlot()
{
    rtAngle = 1;
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    randNumber = rand()%360 +180;// 180 -> 360之间
    rtTimer.start(5);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(event->pos().x() >180 && event->pos().x()<220
                && event->pos().y()<216 && event->pos().y()>130)
        {
            emit luckStartSignal();
        }
    }

}
