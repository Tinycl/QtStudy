#include "mywidget.h"
#include "ui_mywidget.h"
#include <QThread>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    //只要定时器启动，自动触发timeout()
    connect(myTimer, &QTimer::timeout, this, &MyWidget::dealTimeout);

    //分配空间
    thread = new MyThread(this);


    connect(thread, &MyThread::isDone, this, &MyWidget::dealDone);

    //当按窗口右上角x时，窗口触发destroyed()
    connect(this, &MyWidget::destroyed, this, &MyWidget::stopThread);

}

void MyWidget::stopThread()
{
    //停止线程
    thread->quit();
    //等待线程处理完手头动作
    thread->wait();
}

void MyWidget::dealDone()
{
    qDebug() << "it is over";
    myTimer->stop(); //关闭定时器
}

void MyWidget::dealTimeout()
{
    static int i = 0;
    i++;
    //设置lcd的值
    ui->lcdNumber->display(i);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    //如果定时器没有工作
    if(myTimer->isActive() == false)
    {
        myTimer->start(100);
    }

    //启动线程，处理数据
    thread->start();

}





