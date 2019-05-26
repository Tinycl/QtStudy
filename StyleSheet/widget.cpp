#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setStyleSheet("QLabel{color:rgb(0, 255, 255);"
                        "background-color:red;"
                        "}");

    ui->label->setStyleSheet("QLabel{color:rgb(0, 255, 255);"
                             "background-color:blue;"
                             "border-image:url(:/new/prefix1/image/Sunny.jpg);"
                             "}");

    ui->pushButton->setStyleSheet("QPushButton{"
                                  "border-image:url(:/new/prefix1/image/Sunny.jpg);"
                                  "}"
                                  "QPushButton:hover{"
                                  "border-image:url(:/new/prefix1/image/up.png);"
                                  "}"

                                  "QPushButton:pressed{"
                                  "border-image:url(:/new/prefix1/image/Luffy.png);"
                                  "}"

                                  );


}

Widget::~Widget()
{
    delete ui;
}
