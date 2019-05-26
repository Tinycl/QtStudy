#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QBitmap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //QPixmap 图片背景透明
    p.drawPixmap(0, 0, QPixmap("../Image/butterfly.png"));
    //QBitmap 图片背景透明
    p.drawPixmap(200, 0, QBitmap("../Image/butterfly.png"));

     //QPixmap 图片背景白色
    QPixmap pixmap;
    pixmap.load("../Image/butterfly1.png");
    p.drawPixmap(0, 200, pixmap);

    //QBitmap 图片背景白色
    QBitmap bitmap;
    bitmap.load("../Image/butterfly1.png");
    p.drawPixmap(200, 200, bitmap);

}
