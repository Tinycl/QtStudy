#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void dealSignal();
    void dealClose();

signals:
    void startThread(); //启动子线程的信号

private slots:
    void on_buttonStart_clicked();

    void on_buttonStop_clicked();

private:
    Ui::MyWidget *ui;
    MyThread *myT;
    QThread *thread;

};

#endif // MYWIDGET_H
