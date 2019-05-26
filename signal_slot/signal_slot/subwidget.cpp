#include "subwidget.h"

subwidget::subwidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("子窗口");
    m_b1.setParent(this);
    m_b1.setText("切换到父窗口");

    //向主窗口发送信号
    connect(&m_b1,&QPushButton::released,this,&subwidget::sendMySignalSlot);
}

 //向主窗口发送信号
void subwidget::sendMySignalSlot()
{
    emit mySignal();
    emit mySignal(250,"我是子窗口");
}
