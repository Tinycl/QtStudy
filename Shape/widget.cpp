#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //去窗口表框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    //把窗口背景设置为透明
    setAttribute(Qt::WA_TranslucentBackground);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0, 0, QPixmap("../Image/sunny.png"));
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        //如果是右键
        close();
    }
    else if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
       move(e->globalPos() - p);
    }
}
