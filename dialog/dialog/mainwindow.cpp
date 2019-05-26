#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    QMenu *menu = mBar->addMenu("对话框");
    QAction  *p1 = menu->addAction("模态对话框");
    connect(p1,&QAction::triggered,
            [=]()
            {
                //QDialog dlg;
                dlg.exec();
                qDebug()<<"aaaaa";
            }

            );
    QAction  *p2 = menu->addAction("非模态对话框");
    connect(p2,&QAction::triggered,
            [=]()
            {
                //QDialog dlg;
                dlg.show();
                dlg.setAttribute(Qt::WA_QuitOnClose);
                qDebug()<<"aaaaa";
            }

            );

    QAction  *p3 = menu->addAction("关于对话框");
    connect(p3,&QAction::triggered,
            [=]()
            {
                QMessageBox::about(this,"about","关于qt");
            }

            );
    QAction  *p4 = menu->addAction("问题对话框");
    connect(p4,&QAction::triggered,
            [=]()
            {
                //可以添加按钮
                int ret = QMessageBox::question(this,"question","??");
                switch(ret)
                {
                case QMessageBox::Yes:
                    qDebug()<<"Yes";
                    break;
                case QMessageBox::No:
                    qDebug()<<"No";
                    break;

                }
            }

            );

    QAction  *p5 = menu->addAction("文件对话框");
    connect(p5,&QAction::triggered,
            [=]()
            {
               QString path = QFileDialog::getOpenFileName(
                           this,
                           "open",
                           "../",
                           "souce(*.cpp *.h);;Text(*.txt);;all(*.*)"
                           );
               qDebug()<<path;
            }

            );

}

MainWindow::~MainWindow()
{

}
