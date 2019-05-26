#include "carmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarManager w;
    w.show();

    return a.exec();
}
