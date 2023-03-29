#ifndef FENETRERDV_H
#define FENETRERDV_H

#include <QMainWindow>
#include <QWidget>
#include "PersonneLCH.h"
#include "RdvLCH.h"
#include "personnevues.h"
#include <QLineEdit>
#include <QTableWidget>

class fenetreRdv : public QMainWindow
{
    Q_OBJECT
public:
    explicit fenetreRdv(const PersonneLCH& personnes,
                        const RdvLCH& rdvs,
                        QWidget *parent = nullptr);
private:
    PersonneLCH d_personnes;
    RdvLCH d_rdvs;
    QWidget *d_central;

    PersonneVues* d_affichePersonne;

    void creeVue();
    void creeBar();
public slots :
    void onPersAjouter();
    void onPersRechercher();
};

#endif // FENETRERDV_H
