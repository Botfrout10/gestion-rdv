#include "fenetrerdv.h"
#include <QBoxLayout>
#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <fstream>

#include "validation.h"

fenetreRDV::fenetreRDV(const PersonneLCH& pers, const RdvLCH& rdv, QWidget *parent)
    : QMainWindow{parent}, d_personnes{pers}, d_rdvs{rdv}
{
    ifstream finPers{"../gestion-rdv/stockage/Personne.txt"};
    finPers>>d_personnes;
    ifstream finRdv{"../gestion-rdv/stockage/Rdv.txt"};
    finRdv>>d_rdvs;
    creeMenu();
    QString style=QStringLiteral("* {font-family: Arial;"
                                 "background-color: #e6e6e6;"
                                 "}"
                                 "/* Set the background color */"
                                 "QMainWindow {"
                                 "    background-color: #F5F5F5;"
                                 "}"
                                 "/* Set the color of the menubar */"
                                 "QMenuBar {"
                                 "    background-color: #333;"
                                 "    color: #FFF;"
                                 "}"
                                 "/* Set the color of the menu items */"
                                 "QMenuBar::item {"
                                 "    background-color: #333;"
                                 "    color: #FFF;"
                                 " }"
                                 " /* Set the color of the selected menu item */"
                                 " QMenuBar::item:selected {"
                                 "     background-color: #555;"
                                 " }"
                                 " /* Set the color of the toolbar */"
                                 " QToolBar {"
                                 "     background-color: #EEE;"
                                 " }"
                                 " /* Set the color of the buttons in the toolbar */"
                                 "QToolButton {"
                                 "    background-color: #333;"
                                 "border: 1px solid #DDD;"
                                 "}"
                                 "/* Set the color of the button when it is pressed */"
                                 "QToolButton:pressed {"
                                 "   background-color: #DDD;"
                                 "}"
                                 "/* Set the color of the button when it is hovered */"
                                 "QToolButton:hover {"
                                 "    background-color: #DDD;"
                                 "}"
                                 "/* Set the color of the central widget */"
                                 "QStackedWidget {"
                                 "    background-color: #FFF;"
                                 "}"
                                 "/* Set the color of the labels */"
                                 "QLabel {"
                                 "    color: #333;"
                                 "}"
                                 "/* Set the color of the buttons */"
                                 "QPushButton {"
                                 "    background-color: #DDD;"
                                 "    border: 1px solid #CCC;"
                                 "}"
                                 "/* Set the color of the button when it is pressed */"
                                 "QPushButton:pressed {"
                                 "    background-color: #CCC;"
                                 "}"
                                 "/* Set the color of the button when it is hovered */"
                                 "QPushButton:hover {"
                                 "    background-color: #CCC;"
                                 "}"
                                 "QLineEdit"
                                 "{"
                                 "    background : white;"
                                 "}"
                                 "QAction"
                                 "{"
                                 "    color : #333;"
                                 "}"

//                                 "QWidget "
//                                 "{"
//                                 "    background-color: #f2f2f2;"
//                                 "    font-size: 16px;"
//                                 "   font-family: Arial, sans-serif;"
//"                                 }"

//"                                 QLineEdit {"
//"                                     background-color: #fff;"
//"                                     border: 1px solid #ccc;"
//"                                     padding: 4px;"
//"                                 }"
//"                                 QPushButton {"
//"                                     background-color: #4CAF50;"
//"                                     color: #fff;"
//"                                     border: none;"
//"                                     padding: 8px 16px;"
//"                                     border-radius: 4px;"
//"                                     cursor: pointer;"
//"                                 }"
//"                                 QPushButton:hover {"
//"                                     background-color: #3e8e41;"
//                                    "}"
//"                                 QLabel {"
//"                                     font-weight: bold;"
//"}"
                                 );
    this->setStyleSheet(style);
    vuePersAfficher();
    connect(this,&QMainWindow::destroyed,this,&fenetreRDV::onAppClose);
}


void fenetreRDV::creeMenu()
{
    //creation des menus
    //creation de menu Personne
    auto menuPers=menuBar()->addMenu(tr("&Personne"));
    auto actAjouterPers=new QAction{tr("Ajouter")};
    auto actModifeirPers=new QAction{tr("Modifier")};
    auto actSupprimerPers=new QAction{tr("Supprimer")};
    auto actRechercherPers=new QAction{tr("Rechercher")};
    auto actAfficherPers=new QAction{tr("Afficher")};
    menuPers->addActions({actAjouterPers,actModifeirPers,actSupprimerPers,actRechercherPers,actAfficherPers});
    connect(actAjouterPers,&QAction::triggered,
            this,&fenetreRDV::onActionAjouterPers);
    connect(actRechercherPers,&QAction::triggered,
            this,&fenetreRDV::onActionRecherchePers);
    connect(actModifeirPers,&QAction::triggered,
            this,&fenetreRDV::onActionModifierPers);
    connect(actSupprimerPers,&QAction::triggered,
            this,&fenetreRDV::onActionSupprimerPers);
    connect(actAfficherPers,&QAction::triggered,
            this,&fenetreRDV::onActionAfficherPers);


    //creation de menu Rdv
    auto menuRdv=menuBar()->addMenu(tr("&Rdv"));
    auto actAjouterRdv=new QAction{tr("Ajouter")};
    auto actModifeirRdv=new QAction{tr("Modifier")};
    auto actSupprimerRdv=new QAction{tr("supprimer")};
    auto actRechercherRdv=new QAction{tr("Rechercher")};
    menuRdv->addActions({actAjouterRdv,actModifeirRdv,actSupprimerRdv,actRechercherRdv});
}

//Ajouter Personne
void fenetreRDV::vuePersAjouter()
{
    auto central = new QWidget{};

    auto mainLayout = new QGridLayout{};
    mainLayout->addWidget(new QLabel{tr("Ajouter une Personne")},0,0,Qt::AlignJustify);
    //nom
    mainLayout->addWidget(new QLabel{tr("Nom*")},1,0,Qt::AlignLeft);
    d_nomTextAjtPers = new QLineEdit{};
    mainLayout->addWidget(d_nomTextAjtPers,2,0,Qt::AlignJustify);
    d_nomErrorAjtPers = new QLabel{"                 "};
    d_nomErrorAjtPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_nomErrorAjtPers,3,0);
    //prenom
    mainLayout->addWidget(new QLabel{tr("Prenom")},4,0,Qt::AlignLeft);
    d_prenomTextAjtPers = new QLineEdit{};
    mainLayout->addWidget(d_prenomTextAjtPers,5,0,Qt::AlignJustify);
    d_prenomErrorAjtPers = new QLabel{"                 "};
    d_prenomErrorAjtPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_prenomErrorAjtPers);
    //tel
    mainLayout->addWidget(new QLabel{tr("Tel")},7,0,Qt::AlignLeft);
    d_telTextAjtPers = new QLineEdit{};
    mainLayout->addWidget(d_telTextAjtPers,8,0,Qt::AlignJustify);
    d_telErrorAjtPers = new QLabel{"                 "};
    d_telErrorAjtPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_telErrorAjtPers);
    //email
    mainLayout->addWidget(new QLabel{tr("Email")},10,0,Qt::AlignLeft);
    d_emailTextAjtPers = new QLineEdit{};
    mainLayout->addWidget(d_emailTextAjtPers,11,0,Qt::AlignJustify);
    d_emailErrorAjtPers = new QLabel{"                 "};
    d_emailErrorAjtPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_emailErrorAjtPers);

    //bouttons
    auto btnValider = new QPushButton{tr("Valider")};
    mainLayout->addWidget(btnValider,12,2,Qt::AlignCenter);
    connect(btnValider,&QPushButton::clicked,
            this,&fenetreRDV::onAjouterPers);


    central->setLayout(mainLayout);




    setCentralWidget(central);
    this->adjustSize();


}
void fenetreRDV::onActionAjouterPers()
{
    vuePersAjouter();
}
void fenetreRDV::onAjouterPers()
{
    validation v{};
    bool valide=true;
    if(!v.isNom(d_nomTextAjtPers->text().toStdString()))
    {
        d_nomErrorAjtPers->setText(tr("Entrer un nom valide"));
        valide=false;
    }
    else
    {
        d_nomErrorAjtPers->setText(tr(""));
    }
    if(!v.isNom(d_prenomTextAjtPers->text().toStdString()))
    {
        d_prenomErrorAjtPers->setText(tr("Entrer un prenom valide"));
        valide=false;
    }
    else
    {
        d_prenomErrorAjtPers->setText(tr(""));
    }
    if(!v.isTel(d_telTextAjtPers->text().toStdString()))
    {
        d_telErrorAjtPers->setText(tr("Entrer un Tel valide ex: +0687465768"));
        valide=false;
    }
    else
    {
        d_telErrorAjtPers->setText(tr(""));
    }
    if(!v.isEmail(d_emailTextAjtPers->text().toStdString()))
    {
        d_emailErrorAjtPers->setText(tr("Entrer un email valide"));
        valide=false;
    }
    else
    {
        d_emailErrorAjtPers->setText(tr(""));
    }
    if(valide)
    {
        bool test=d_personnes.ajouter(d_nomTextAjtPers->text().toStdString(),
        d_prenomTextAjtPers->text().toStdString(),
        d_telTextAjtPers->text().toStdString(),
        d_emailTextAjtPers->text().toStdString());
        if(test)
        {
            QMessageBox msgBox{QMessageBox::Information,
            tr("Information"), tr("Personne Ajouter")};
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox{QMessageBox::Warning,
            tr("Critical"), tr("Ce nom Existe")};
            msgBox.exec();
        }
    }

}
//Rechercher Personne
void fenetreRDV::vuePersRechercher()
{
    auto central = new QWidget{};

    auto mainLayout = new QGridLayout{};
    central->setLayout(mainLayout);
    mainLayout->addWidget(new QLabel{tr("Rechercher une Personne")},0,0,Qt::AlignCenter);

    //Recherche bar
    mainLayout->addWidget(new QLabel{tr("Entrer le nom : ")},1,0,Qt::AlignLeft);
    //Line Edit
    d_nomTextRechPers=new QLineEdit{};
    mainLayout->addWidget(d_nomTextRechPers,1,1,Qt::AlignLeft);
    //boutton Rechercher
    auto btnRecherche = new QPushButton{tr("Rechercher")};
    mainLayout->addWidget(btnRecherche,1,2,Qt::AlignCenter);
    connect(btnRecherche,&QPushButton::clicked,
            this, &fenetreRDV::onRechercherPers);

    //les infos de la personne
    d_nomRechPers=new QLabel{};
    d_prenomRechPers=new QLabel{};
    d_telRechPers=new QLabel{};
    d_emailRechPers=new QLabel{};
    mainLayout->addWidget(d_nomRechPers,2,0);
    mainLayout->addWidget(d_prenomRechPers,3,0);
    mainLayout->addWidget(d_telRechPers,4,0);
    mainLayout->addWidget(d_emailRechPers,5,0);


    setCentralWidget(central);
    this->adjustSize();

}
void fenetreRDV::onRechercherPers()
{
    Personne p=d_personnes.personne(d_nomTextRechPers->text().toStdString());
    if(p.nom()!="N/A")
    {
        d_nomRechPers->setText("Nom :"+QString::fromStdString(p.nom()));
        d_prenomRechPers->setText("Prenom :"+QString::fromStdString(p.prenom()));
        d_telRechPers->setText("Tel :"+QString::fromStdString(p.tel()));
        d_emailRechPers->setText("Email :"+QString::fromStdString(p.email()));
    }
    else
    {
        d_nomRechPers->setText(tr("La Personne n'existe pas"));
        d_prenomRechPers->setText("");
        d_telRechPers->setText("");
        d_emailRechPers->setText("");
    }
}
void fenetreRDV::onActionRecherchePers()
{
    vuePersRechercher();
}
//Modifier Personne
void fenetreRDV::vuePersModifier()
{
    auto central = new QWidget{};

    auto mainLayout = new QGridLayout{};
    mainLayout->addWidget(new QLabel{tr("Modifier une Personne")},0,1, Qt::AlignCenter);

    //Bar de recherche
    mainLayout->addWidget(new QLabel{tr("Entrer le nom : ")},1,0,Qt::AlignLeft);
    //Line Edit
    d_rechNomTextModifPers=new QLineEdit{};
    mainLayout->addWidget(d_rechNomTextModifPers,1,1,Qt::AlignLeft);
    //ecrire l'erreure
    d_rechNomErrModifPers= new QLabel{"     "};
    d_rechNomErrModifPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_rechNomErrModifPers,2,0,Qt::AlignLeft);

    //nom
    mainLayout->addWidget(new QLabel{tr("Nom*")},3,0,Qt::AlignLeft);
    d_nomTextModiPers = new QLineEdit{};
    mainLayout->addWidget(d_nomTextModiPers,4,0,Qt::AlignJustify);
    d_nomErrModiPers = new QLabel{"                 "};
    d_nomErrModiPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_nomErrModiPers,5,0);
    //prenom
    mainLayout->addWidget(new QLabel{tr("Prenom")},6,0,Qt::AlignLeft);
    d_prenomTextModiPers = new QLineEdit{};
    mainLayout->addWidget(d_prenomTextModiPers,7,0,Qt::AlignJustify);
    d_prenomErrModiPers = new QLabel{"                 "};
    d_prenomErrModiPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_prenomErrModiPers,8,0,Qt::AlignLeft);
    //tel
    mainLayout->addWidget(new QLabel{tr("Tel")},9,0,Qt::AlignLeft);
    d_telTextModiPers = new QLineEdit{};
    mainLayout->addWidget(d_telTextModiPers,10,0,Qt::AlignJustify);
    d_telErrModiPers = new QLabel{"                 "};
    d_telErrModiPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_telErrModiPers,11,0,Qt::AlignLeft);
    //email
    mainLayout->addWidget(new QLabel{tr("Email")},12,0,Qt::AlignLeft);
    d_emailTextModiPers = new QLineEdit{};
    mainLayout->addWidget(d_emailTextModiPers,13,0,Qt::AlignJustify);
    d_emailErrModiPers = new QLabel{"                 "};
    d_emailErrModiPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_emailErrModiPers,14,0,Qt::AlignLeft);

    //bouttons
    auto btnValider = new QPushButton{tr("Valider")};
    mainLayout->addWidget(btnValider,15,2,Qt::AlignCenter);
    connect(btnValider,&QPushButton::clicked,
            this,&fenetreRDV::onModifierPers);

    central->setLayout(mainLayout);
    setCentralWidget(central);
    this->adjustSize();
}
void fenetreRDV::onActionModifierPers()
{
    vuePersModifier();
}
void fenetreRDV::onModifierPers()
{
    validation v{};
    bool valide=true;
    if(!d_personnes.recherche(d_rechNomTextModifPers->text().toStdString()))
    {
        d_rechNomErrModifPers->setText(tr("Ce nom n'existe pas"));
        valide=false;
    }
    else
    {
        d_rechNomErrModifPers->setText("");
    }
    if(!v.isNom(d_nomTextModiPers->text().toStdString()))
    {
        d_nomErrModiPers->setText(tr("Entrer un nom valide"));
        valide=false;
    }
    else
    {
        d_nomErrModiPers->setText(tr(""));
    }
    if(!v.isNom(d_prenomTextModiPers->text().toStdString()))
    {
        d_prenomErrModiPers->setText(tr("Entrer un prenom valide"));
        valide=false;
    }
    else
    {
        d_prenomErrModiPers->setText(tr(""));
    }
    if(!v.isTel(d_telTextModiPers->text().toStdString()))
    {
        d_telErrModiPers->setText(tr("Entrer un Tel valide ex: +0687465768"));
        valide=false;
    }
    else
    {
        d_telErrModiPers->setText(tr(""));
    }
    if(!v.isEmail(d_emailTextModiPers->text().toStdString()))
    {
        d_emailErrModiPers->setText(tr("Entrer un email valide"));
        valide=false;
    }
    else
    {
        d_emailErrModiPers->setText(tr(""));
    }
    if(valide)
    {
        bool test=d_personnes.modifier(d_rechNomTextModifPers->text().toStdString(),
                                      d_nomTextModiPers->text().toStdString(),
                                      d_prenomTextModiPers->text().toStdString(),
                                      d_telTextModiPers->text().toStdString(),
                                      d_emailTextModiPers->text().toStdString());
        if(test)
        {
            QMessageBox msgBox{QMessageBox::Information,
            tr("Information"), tr("Personne Modifier")};
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox{QMessageBox::Warning,
            tr("Warning"), tr("le nouveau nom existe deja,choisir un autre nom")};
            msgBox.exec();
        }
    }
}
//Supprimer Personne
void fenetreRDV::vuePersSupprimer()
{
//    this->setMaximumSize(QSize{200,150});
    auto central = new QWidget{};

    auto mainLayout = new QGridLayout{};
    mainLayout->addWidget(new QLabel{tr("Supprimer un Personne")},0,1,Qt::AlignJustify);
    mainLayout->addWidget(new QLabel{tr("Nom")},1,0,Qt::AlignLeft);
    d_nomTextSuppPers = new QLineEdit{};
    mainLayout->addWidget(d_nomTextSuppPers,1,1,Qt::AlignLeft);
    auto btnSupp = new QPushButton{tr("Supprimer")};
    btnSupp->setStyleSheet("QPushButton:hover"
                           "{   background-color: red;"
                           "}");
    mainLayout->addWidget(btnSupp,1,3,Qt::AlignLeft);
    connect(btnSupp,&QPushButton::clicked,
            this,&fenetreRDV::onSupprimerPers);

    d_nomErrSuppPers = new QLabel{"     "};
    d_nomErrSuppPers->setStyleSheet("color : red");
    mainLayout->addWidget(d_nomErrSuppPers,2,1,Qt::AlignLeft);
    central->setLayout(mainLayout);
    setCentralWidget(central);
    this->adjustSize();

}
void fenetreRDV::onActionSupprimerPers()
{
    vuePersSupprimer();
}
void fenetreRDV::onSupprimerPers()
{
    bool valide=true;
    if(!d_personnes.recherche(d_nomTextSuppPers->text().toStdString()))
    {
        d_nomErrSuppPers->setText(tr("Ce nom n'existe pas"));
        valide=false;
    }
    else
    {
        d_nomErrSuppPers->setText("");
    }
    if(valide)
    {
        bool test = d_personnes.supprimer(d_nomTextSuppPers->text().toStdString(),d_rdvs.rdvs_personne(d_nomTextSuppPers->text().toStdString()));
        if(test)
        {
            QMessageBox msgBox{QMessageBox::Information,
            tr("Information"), tr("Personne Supprimer")};
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox{QMessageBox::Warning,
            tr("Warning"), tr("la personne a des rendez-vous")};
            msgBox.exec();
        }
    }

}
//afficher Personne
void fenetreRDV::vuePersAfficher()
{
    this->setMinimumWidth(450);

    auto central = new QWidget{};

    auto mainLayout = new QVBoxLayout{};
    auto afficheTable = new QTableWidget{d_personnes.taille(),4};
    afficheTable->setHorizontalHeaderItem(0,new QTableWidgetItem{tr("Nom")});
    afficheTable->setHorizontalHeaderItem(1,new QTableWidgetItem{tr("Prenom")});
    afficheTable->setHorizontalHeaderItem(2,new QTableWidgetItem{tr("Tel")});
    afficheTable->setHorizontalHeaderItem(3,new QTableWidgetItem{tr("Email")});

    for(int i{0} ; i<d_personnes.taille() ; ++i)
    {
        afficheTable->setItem(i,0,new QTableWidgetItem{QString::fromStdString(d_personnes.get_personne(i).nom())});
        afficheTable->setItem(i,1,new QTableWidgetItem{QString::fromStdString(d_personnes.get_personne(i).prenom())});
        afficheTable->setItem(i,2,new QTableWidgetItem{QString::fromStdString(d_personnes.get_personne(i).tel())});
        afficheTable->setItem(i,3,new QTableWidgetItem{QString::fromStdString(d_personnes.get_personne(i).email())});
    }
    mainLayout->addWidget(afficheTable);

    central->setLayout(mainLayout);
    setCentralWidget(central);
}
void fenetreRDV::onActionAfficherPers()
{
    vuePersAfficher();
}

void fenetreRDV::onAppClose()
{
    ofstream foutPers{"../gestion-rdv/stockage/Personne.txt"},
             foutRdv{"../gestion-rdv/stockage/Rdv.txt"};
    foutPers<<d_personnes;
    foutRdv<<d_rdvs;
}
