#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h" //子窗口头文件
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public:
    void mySlot(); //声明槽函数
    void changeWid();
    void dealSubWidSignal();
    void dealSlot(int,QString);
public:
    QPushButton m_b1;
    QPushButton *m_pb2;
    QPushButton m_b3;

    subwidget m_subwidget; //子窗口作为父窗口成员变量
};

#endif // WIDGET_H
