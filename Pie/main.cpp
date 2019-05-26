#include "piewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PieWidget w;
    w.show();

    return a.exec();
}
