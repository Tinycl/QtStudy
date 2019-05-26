#ifndef PIEWIDGET_H
#define PIEWIDGET_H

#include <QWidget>

namespace Ui {
class PieWidget;
}

class PieWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PieWidget(QWidget *parent = 0);
    ~PieWidget();

private:
    Ui::PieWidget *ui;
};

#endif // PIEWIDGET_H
