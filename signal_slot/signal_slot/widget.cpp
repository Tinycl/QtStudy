#include "widget.h"
#include <QDebug>

//父窗口的按钮控件发送信号，父窗口隐藏自己，并将子窗口显示
//子窗口向父窗口发送信号，父窗口显示自己，隐藏子窗口
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_b1.setParent(this);
    m_b1.setText("hello b1");
    m_pb2 = new QPushButton(this);
    m_pb2->setText("hello b2");
    m_pb2->move(400,400);
    /*
     *  m_b1 :信号发出者，按钮
     * QPushButton::pressed :发出的信号，这里是标准信号，按钮的信号
     * this :信号接收处理者， 当前窗口Widget
     * Widget::close :处理信号的槽函数，当前窗口槽函数，这里是标准槽函数
     *
    */
    connect(&m_b1,&QPushButton::pressed,this,&Widget::close);

    //自定义槽函数
    //当前窗口接收
    connect(m_pb2,&QPushButton::released,this,&Widget::mySlot);
    //另一个按钮控件接收处理
    connect(m_pb2,&QPushButton::released,&m_b1,&QPushButton::hide);

    this->setWindowTitle("父窗口");
    m_b3.setParent(this);
    m_b3.setText("切换到子窗口");
    m_b3.move(100,100);

   // m_subwidget.show(); //显示子窗口
    connect(&m_b3,&QPushButton::released,this,&Widget::changeWid);

    //接收并处理子窗口发送的信号
    //connect(&m_subwidget,&subwidget::mySignal,this,&Widget::dealSubWidSignal);
    //信号重载之后，利用函数指针解决信号的二义性
    void (subwidget::*funSignal1)() = &subwidget::mySignal;
    connect(&m_subwidget,funSignal1,this,&Widget::dealSubWidSignal);
    void (subwidget::*funSignal2)(int, QString) = &subwidget::mySignal;
    connect(&m_subwidget,funSignal2,this,&Widget::dealSlot);

    //c++ 11 Lambda表达式，匿名函数对象，用作信号和槽函数
    /* []()
     * {
     * ...
     * }
     * [name]()外部name为要传入的参数
     * [=]() 把外部所有局部变量、类成员变量以值传递传入，传入参数只读
     * [=]() mutable 以值传递方式，参数可修改
     * [this]() 把类中所有成员以值传递
     * [&]() 把外部所有局部变量，引用方式
     *
     * [](type name) name作为信号传递给槽函数的参数
     */
    QPushButton *pb4 = new QPushButton(this);
    pb4->setText("Lambda表达式");
    pb4->move(250,250);
    connect(pb4,&QPushButton::released,
            [pb4]()
             {
                pb4->setText("Lambda input para");
                qDebug()<<"Lambda\n";
             }
            );

}

Widget::~Widget()
{

}

//槽函数
void Widget::mySlot()
{
    m_pb2->setText("myslot");
}

//父窗口隐藏，切换到子窗口
void Widget::changeWid()
{
    m_subwidget.show();
    this->hide();
}
//处理子窗口发送信号的槽函数
void Widget::dealSubWidSignal()
{
    m_subwidget.hide();
    this->show();
}

void Widget::dealSlot(int a, QString str)
{
    qDebug()<<a<<str.toUtf8().data();
}
