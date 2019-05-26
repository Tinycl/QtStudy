#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer> //定时器头文件
#include "mythread.h" //线程头文件

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void dealTimeout(); //定时器槽函数
    void dealDone(); //线程结束槽函数
    void stopThread(); //停止线程槽函数

private slots:
    void on_pushButton_clicked();

private:
    Ui::MyWidget *ui;

    QTimer *myTimer; //声明变量
    MyThread *thread; //线程对象
};

#endif // MYWIDGET_H
