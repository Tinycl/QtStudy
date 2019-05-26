#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //绘图设备， 400*300
    QPixmap pixmap(400, 300);

    QPainter p(&pixmap);
    //填充白色背景色
    //p.fillRect(0, 0, 400, 300, QBrush(Qt::white));

    pixmap.fill(Qt::white);

    p.drawPixmap(0, 0, 80, 80, QPixmap("../Image/face.png"));

    //保存图片
    pixmap.save("../pixmap.jpg");



}

Widget::~Widget()
{
    delete ui;
}
