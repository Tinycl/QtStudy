#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QEvent>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    timerId = this->startTimer(1000); //毫秒为单位 每隔1s触发一次定时器
    this->timeId2 = this->startTimer(500);


    connect(ui->pushButton, &MyButton::clicked,
            [=]()
            {
                qDebug() << "按钮被按下";
            }

            );

    //安装过滤器
    ui->label_2->installEventFilter(this);
    ui->label_2->setMouseTracking(true);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::keyPressEvent(QKeyEvent *e)
{
    qDebug() << (char)e->key();

    if(e->key() == Qt::Key_A)
    {
        qDebug() << "Qt::Key_A";
    }
}

void MyWidget::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == this->timerId)
    {
        static int sec = 0;
        ui->label->setText(
             QString("<center><h1>timer out: %1</h1></center>").arg(sec++)

                    );

        if(5 == sec)
        {
            //停止定时器
            this->killTimer(this->timerId);
        }
    }
    else if(e->timerId() == this->timeId2)
    {
        static int sec = 0;
        ui->label_2->setText(
             QString("<center><h1>timer out: %1</h1></center>").arg(sec++)

                    );
    }
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "+++++++++++++++++++++++";
}

void MyWidget::closeEvent(QCloseEvent *e)
{
    int ret = QMessageBox::question(this, "question", "是否需要关闭窗口");
    if(ret == QMessageBox::Yes)
    {
        //关闭窗口
        //处理关闭窗口事件，接收事件，事件就不会再往下传递
        e->accept();
    }
    else
    {
        //不关闭窗口
        //忽略事件，事件继续给父组件传递
        e->ignore();
    }

}

bool MyWidget::event(QEvent *e)
{
//    //事件分发
//    switch( e->type() )
//    {
//        case QEvent::Close:
//            closeEvent(e);
//        break;
//    case QEvent::MouseMove:
//        mouseMoveEvent(e);
//        break;
//        /*
//         *  ……
//        */
//    }

    if(e->type() == QEvent::Timer)
    {
        //干掉定时器
        //如果返回true，事件停止传播
        //QTimerEvent *env = static_cast<QTimerEvent *>(e);
        //timerEvent(env);
        return true;
    }
    else if(e->type() == QEvent::KeyPress)
    {
        //类型转换
        QKeyEvent *env = static_cast<QKeyEvent *>(e);
        if(env->key() == Qt::Key_B)
        {
            return QWidget::event(e);
        }
        return true;

    }
    else
    {
        return QWidget::event(e);
        //return false;
    }

}

bool MyWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->label_2)
    {
        QMouseEvent *env = static_cast<QMouseEvent *>(e);
        //判断事件
        if(e->type() == QEvent::MouseMove)
        {
            ui->label_2->setText(QString("Mouse move:(%1, %2)").arg(env->x()).arg(env->y()));
            return true;
        }
        if(e->type() == QEvent::MouseButtonPress)
        {
            ui->label_2->setText(QString("Mouse press:(%1, %2)").arg(env->x()).arg(env->y()));
            return true;
        }
        if(e->type() == QEvent::MouseButtonRelease)
        {
            ui->label_2->setText(QString("Mouse release:(%1, %2)").arg(env->x()).arg(env->y()));
            return true;
        }
        else
        {
            return QWidget::eventFilter(obj, e);
        }
    }
    else
    {
        return QWidget::eventFilter(obj, e);
    }
    
//    if(obj == ui->pushButton)
//    {
        
//    }
}











