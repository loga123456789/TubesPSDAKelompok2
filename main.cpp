#include "sirumahsakit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiRumahSakit w;
    w.show();
    return a.exec();
}
