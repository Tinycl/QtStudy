#include "gramwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GramWidget w;
    w.show();

    return a.exec();
}
