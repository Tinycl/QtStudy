#include "mainwindow.h"
#include <QMenuBar> //菜单栏
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //菜单栏
    QMenuBar *mBar = menuBar();

    //添加菜单
    QMenu *pFile = mBar->addMenu("文件");

    //添加菜单项，添加动作，信号
     QAction *pNew = pFile->addAction("新建");
    connect(pNew, &QAction::triggered,
            [=]()
            {
                qDebug()<<"new";
             }
            );
    pFile->addSeparator(); //添加分割线，美观
    QAction *pOpen = pFile->addAction("打开");
    connect(pOpen, &QAction::triggered,
           [=]()
           {
               qDebug()<<"open";
            }
           );

    //工具栏，存放菜单项的快捷方式
    QToolBar *toolBar = addToolBar("toolBar");
    //工具栏添加快捷键
    toolBar->addAction(pNew);
    //工具栏添加小控件
    QPushButton *b = new QPushButton(this);
    b->setText("button");
    toolBar->addWidget(b);
    connect(b,&QPushButton::released,
            [=]()
            {
                b->setText("123");
                qDebug()<<"button";
            }
            );
    //状态栏
    QStatusBar *sBar = statusBar();
    QLabel *label = new QLabel(this);
    label->setText("Normal text file");
    sBar->addWidget(label);
    //addWidget从左往右添加
    sBar->addWidget(new QLabel("2",this));
    //addPermanentWidget从右向左添加
    sBar->addPermanentWidget(new QLabel("3",this));

    //核心控件
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    //浮动窗口
    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    //浮动窗口添加控件
    QTextEdit *textEdit1 = new QTextEdit(this);
    dock->setWidget(textEdit1);
}

MainWindow::~MainWindow()
{

}
