#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class subwidget : public QWidget
{
    Q_OBJECT
public:
    explicit subwidget(QWidget *parent = nullptr);

signals:
    void mySignal(); //定义信号，信号函数只需要声明，不需要定义
    void mySignal(int,QString);//定义带参数信号
public slots:
    void sendMySignalSlot();
public:
    QPushButton m_b1;
};

#endif // SUBWIDGET_H
