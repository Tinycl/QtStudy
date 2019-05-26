#ifndef GRAMWIDGET_H
#define GRAMWIDGET_H

#include <QWidget>

namespace Ui {
class GramWidget;
}

class GramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GramWidget(QWidget *parent = 0);
    ~GramWidget();

private:
    Ui::GramWidget *ui;
};

#endif // GRAMWIDGET_H
