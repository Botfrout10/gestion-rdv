#include "fenetrerdv.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PersonneLCH pers{};
    pers.ajouter("Ottmani","Mehdi","+09876543","mehdi@gmail.com");
    pers.ajouter("Salem","Mouhssin","+09876543","mehdi@gmail.com");
    pers.ajouter("Lbaldi","Jlafet","+09876543","mehdi@gmail.com");

    fenetreRdv w{pers,{}};
    w.show();
    return a.exec();
}
