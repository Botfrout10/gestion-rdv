#include "fenetrerdv.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FenetreRDV w;
    w.show();
    return a.exec();
}
