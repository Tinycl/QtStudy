#include "piewidget.h"
#include "ui_piewidget.h"

PieWidget::PieWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PieWidget)
{
    ui->setupUi(this);

    QVector<SectorInfo> result;

    SectorInfo info;
    info.description = "已经出售";
    info.percent = 0.3*100;
    result.push_back(info);

    info.description = "剩余";
    info.percent = (1 - 0.3)*100;
    result.push_back(info);

    ui->widget->setData(result);
}

PieWidget::~PieWidget()
{
    delete ui;
}
