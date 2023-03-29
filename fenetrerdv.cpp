#include "fenetrerdv.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QLineEdit>
#include <QPushButton>


fenetreRdv::fenetreRdv(const PersonneLCH& personnes,
                       const RdvLCH& rdvs,
                       QWidget *parent)
    : QMainWindow{parent} , d_personnes{personnes},d_rdvs{rdvs}
{
    creeBar();
    creeVue();
}

void fenetreRdv::creeBar()
{
    auto menuPersonne=menuBar()->addMenu("&Personne");
    auto actAjouter=new QAction{tr("Ajouter")};
    menuPersonne->addAction(actAjouter);
    menuPersonne->addAction("Modifier");
    menuPersonne->addAction("Supprimer");
    auto actRecher=new QAction{tr("Rechercher")};
    menuPersonne->addAction(actRecher);
    connect(actRecher,&QAction::triggered, this , &fenetreRdv::onPersRechercher);



    auto menuRdv=menuBar()->addMenu("&Rendez-vous");
    menuRdv->addAction("Ajouter");
    menuRdv->addAction("Modifier");
    menuRdv->addAction("Supprimer");
    menuRdv->addAction("Rechercher");


}


void fenetreRdv::creeVue()
{
    d_central=new QWidget{};

    //
    d_affichePersonne=new PersonneVues{d_personnes};
    d_central->setLayout(d_affichePersonne->vueAjouterPers());
    //
    setCentralWidget(d_central);
}

void fenetreRdv::onPersAjouter()
{
    d_affichePersonne=new PersonneVues{d_personnes};
    d_central->setLayout(d_affichePersonne->vueAjouterPers());
    setCentralWidget(d_central);
}

void fenetreRdv::onPersRechercher()
{
    d_affichePersonne=new PersonneVues{d_personnes};
    d_central->setLayout(d_affichePersonne->vueRechercherPers());
    setCentralWidget(d_central);
}





