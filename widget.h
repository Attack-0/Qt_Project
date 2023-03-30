#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    // 绘图事件 ：显示隐藏 resize update
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);


public slots:
    void rtTimerOutSlot();
    void luckStartSlot();
signals:
    void luckStartSignal();
private:
    Ui::Widget *ui;

private:
    // 堆区对象 画家
    QPainter rotationPainter;
    QPainter pointPainter;

    // 定时器
    QTimer rtTimer;

    // 角度: 旋转因子通过定时器设定
    qreal rtAngle;
    int randNumber;

};
#endif // WIDGET_H
