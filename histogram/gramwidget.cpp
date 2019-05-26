#include "gramwidget.h"
#include "ui_gramwidget.h"

GramWidget::GramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GramWidget)
{
    ui->setupUi(this);

    ui->widget->SetMaxValue(100);
    ui->widget->AddItem("大众", 7);

    ui->widget->AddItem("奔驰", 8);

    ui->widget->AddItem("奥迪", 18);
}

GramWidget::~GramWidget()
{
    delete ui;
}
