#include "fenetrerdv.h"
#include <QBoxLayout>
#include <QMenuBar>
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
//    this->setStyleSheet(style);
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
    auto actModifierRdv=new QAction{tr("Modifier")};
    auto actSupprimerRdv=new QAction{tr("supprimer")};
    menuRdv->addActions({actAjouterRdv,actModifierRdv,actSupprimerRdv});

    auto menuRechRdv= new QMenu{tr("Rechercher")};
    auto actRechercherRdvDate=new QAction{tr("Par date")};
    auto actRechercherRdvNom=new QAction{tr("Par Nom")};
    menuRechRdv->addActions({actRechercherRdvDate,actRechercherRdvNom});
    menuRdv->addMenu(menuRechRdv);
    connect(actAjouterRdv,&QAction::triggered,
            this,&fenetreRDV::onActionAjouterRdv);
    connect(actModifierRdv,&QAction::triggered,this,&fenetreRDV::onActionModifierRdv);
    connect(actSupprimerRdv,&QAction::triggered,this,&fenetreRDV::onActionSupprimerRdv);
    connect(actRechercherRdvDate,&QAction::triggered,this,&fenetreRDV::onActionRechercherRdvDate);
    connect(actRechercherRdvNom,&QAction::triggered,this,&fenetreRDV::onActionRechercherRdvNom);

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
        afficheTable->item(i,0)->setFlags(Qt::NoItemFlags);
        afficheTable->item(i,1)->setFlags(Qt::NoItemFlags);
        afficheTable->item(i,2)->setFlags(Qt::NoItemFlags);
        afficheTable->item(i,3)->setFlags(Qt::NoItemFlags);
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

void fenetreRDV::vueRdvAjouter()
{
    auto central = new QWidget{};

    auto mainLayout = new QGridLayout{};
    mainLayout->addWidget(new QLabel{tr("Ajouter Rendez-vous")},0,1,Qt::AlignCenter);
    //nom
    mainLayout->addWidget(new QLabel{tr("Nom*")},1,0,Qt::AlignLeft);
    d_nomTextAjtRdv = new QLineEdit{};
    mainLayout->addWidget(d_nomTextAjtRdv,2,0,Qt::AlignLeft);
    d_nomErrorAjtRdv = new QLabel{"       "};
    d_nomErrorAjtRdv->setStyleSheet("color : red");
    mainLayout->addWidget(d_nomErrorAjtRdv,3,0,Qt::AlignLeft);

    //date deb
    mainLayout->addWidget(new QLabel{tr("Date debut:")},4,0,Qt::AlignLeft);
    d_dateDebAjtRdv = new QDateTimeEdit{};
    d_dateDebAjtRdv->setDisplayFormat("dd/MM/yyyy/hh/mm");
    d_dateDebAjtRdv->setDateTime(QDateTime::currentDateTime());
    mainLayout->addWidget(d_dateDebAjtRdv,5,0,Qt::AlignLeft);



//    date fin
    mainLayout->addWidget(new QLabel{tr("Date fin:")},6,0,Qt::AlignLeft);
    d_dateFinAjtRdv = new QDateTimeEdit{};
    d_dateFinAjtRdv->setDisplayFormat("dd/MM/yyyy/hh/mm");
    d_dateFinAjtRdv->setDateTime(QDateTime::currentDateTime());
    mainLayout->addWidget(d_dateFinAjtRdv,7,0,Qt::AlignLeft);
    d_dateFinErrorAjtRdv = new QLabel{"                 "};
    d_dateFinErrorAjtRdv->setStyleSheet("color : red");
    mainLayout->addWidget(d_dateFinErrorAjtRdv,8,0);
    d_btnAjtRdv = new QPushButton{tr("Ajouter")};
    mainLayout->addWidget(d_btnAjtRdv,9,0,Qt::AlignLeft);
    connect(d_btnAjtRdv,&QPushButton::clicked,
            this,&fenetreRDV::onAjouterRdv);

    //Personnes
    mainLayout->addWidget(new QLabel{tr("Personnes:")},10,0,Qt::AlignLeft);
    d_affichePersAjtRdv = new QComboBox{};
    mainLayout->addWidget(d_affichePersAjtRdv,11,0,Qt::AlignLeft);
    connect(d_affichePersAjtRdv,&QComboBox::activated,
            this,&fenetreRDV::onAjouterPersRdv);
    d_affichePersAjtRdv->setDisabled(true);
    d_infoAjtPersRdv = new QLabel{"     "};
    mainLayout->addWidget(d_infoAjtPersRdv,12,0,Qt::AlignLeft);






    central->setLayout(mainLayout);

    setCentralWidget(central);
}

void fenetreRDV::afficherPersSelectionAjtRdv()
{
//    if(d_nomTextAjtRdv->text() != "")
//    {

        for(int i=0 ; i<d_personnes.taille() ; ++i)
        {
            //c'est mieux d'ajouter un iterateur pour la liste des personnes
            //et il  faut afficher que les personnes ajoutable
            d_affichePersAjtRdv->addItem(QString::fromStdString(d_personnes.get_personne(i).nom()));
        }
//    }
}
void fenetreRDV::onActionAjouterRdv()
{
    vueRdvAjouter();
    afficherPersSelectionAjtRdv();
}

void fenetreRDV::onAjouterRdv()
{

    validation v;
    bool valide{true};
    if(!v.isNom(d_nomTextAjtRdv->text().toStdString()))
    {
        d_nomErrorAjtRdv->setText(tr("Entrer un nom valide"));
        valide=false;
    }
    else
    {
        d_nomErrorAjtRdv->setText("");
    }
    if(!v.estRdv(d_dateDebAjtRdv->text().toStdString(),d_dateFinAjtRdv->text().toStdString()))
    {
        d_dateFinErrorAjtRdv->setText(tr("Entrer des dates valide"));
        valide=false;
    }
    else
    {
        d_dateFinErrorAjtRdv->setText("");
    }
    if(valide)
    {
        d_dateFinErrorAjtRdv->setStyleSheet("color : green");
        d_dateFinErrorAjtRdv->setText("Rdv ajoute");
        d_rdvs.ajouter(d_nomTextAjtRdv->text().toStdString(),d_dateDebAjtRdv->text().toStdString(),d_dateFinAjtRdv->text().toStdString());
        d_btnAjtRdv->hide();
        d_affichePersAjtRdv->setEnabled(true);
    }
}

void fenetreRDV::onAjouterPersRdv(int idx)
{
    Personne P{d_personnes.personne(d_affichePersAjtRdv->itemText(idx).toStdString())};
    if(d_rdvs.rdv(d_nomTextAjtRdv->text().toStdString()).ajouter_pers(P,d_rdvs.rdvs_personne(P)))
    {
        d_infoAjtPersRdv->setStyleSheet("color : green");
        d_infoAjtPersRdv->setText(tr("Personne ajoutee"));
        d_affichePersAjtRdv->removeItem(idx);

    }
    else
    {
        d_infoAjtPersRdv->setStyleSheet("color : red");
        d_infoAjtPersRdv->setText(tr("Personne n'est pas ajoutee"));
    }
}


void fenetreRDV::vueRdvModifier()
{
    auto central = new QWidget{};

    auto mainLayout = new QGridLayout{};
    mainLayout->addWidget(new QLabel{tr("Modifier un Rdv")},0,1, Qt::AlignCenter);

    //Bar de recherche
    mainLayout->addWidget(new QLabel{tr("Entrer le nom : ")},1,0,Qt::AlignLeft);
    //Line Edit
    d_nomRechModifierRdv=new QLineEdit{};
    mainLayout->addWidget(d_nomRechModifierRdv,1,1,Qt::AlignLeft);
    auto btnRechModifierRdv = new QPushButton{tr("Rechercher")};
    mainLayout->addWidget(btnRechModifierRdv,1,2,Qt::AlignLeft);
    connect(btnRechModifierRdv,&QPushButton::clicked,
            this,&fenetreRDV::onRechModifierRdv);
    //ecrire l'erreure
    d_nomErrRechModifierRdv = new QLabel{"     "};
    d_nomErrRechModifierRdv->setStyleSheet("color : red");
    mainLayout->addWidget(d_nomErrRechModifierRdv,2,0,Qt::AlignLeft);

    //nom
    mainLayout->addWidget(new QLabel{tr("Nom*")},3,0,Qt::AlignLeft);
    d_nomModifierRdv = new QLineEdit{};
    mainLayout->addWidget(d_nomModifierRdv,4,0,Qt::AlignJustify);
    d_nomErrModifierRdv = new QLabel{"                 "};
    d_nomErrModifierRdv->setStyleSheet("color : red");
    mainLayout->addWidget(d_nomErrModifierRdv,5,0);

    //date Deb
    mainLayout->addWidget(new QLabel{tr("Date Debut:")},6,0,Qt::AlignLeft);
    d_dateDebModifierRdv = new QDateTimeEdit{};
    d_dateDebModifierRdv->setDisplayFormat("dd/MM/yyyy/hh/mm");
    d_dateDebModifierRdv->setDateTime(QDateTime::currentDateTime());
    mainLayout->addWidget(d_dateDebModifierRdv,7,0,Qt::AlignLeft);

    //Date fin
    mainLayout->addWidget(new QLabel{tr("Date Fin:")},8,0,Qt::AlignLeft);
    d_dateFinModifierRdv = new QDateTimeEdit{};
    d_dateFinModifierRdv->setDisplayFormat("dd/MM/yyyy/hh/mm");
    d_dateFinModifierRdv->setDateTime(QDateTime::currentDateTime());
    mainLayout->addWidget(d_dateFinModifierRdv,9,0,Qt::AlignLeft);
    //error dates
    d_dateFinErrModifierRdv = new QLabel{"       "};
    d_dateFinErrModifierRdv->setStyleSheet("color  : red");
    mainLayout->addWidget(d_dateFinErrModifierRdv,10,0,Qt::AlignLeft);
    auto btnModifRdv = new QPushButton{tr("Modifier")};
    mainLayout->addWidget(btnModifRdv,11,0,Qt::AlignLeft);
    connect(btnModifRdv,&QPushButton::clicked,
            this,&fenetreRDV::onModiferRdv);

    //Supprimer Pers
    mainLayout->addWidget(new QLabel{tr("Supprimer Personnes:")},12,0,Qt::AlignLeft);
    d_afficheSuppPersModifierRdv = new QComboBox{};
    d_afficheSuppPersModifierRdv->setDisabled(true);
    mainLayout->addWidget(d_afficheSuppPersModifierRdv,13,0,Qt::AlignLeft);
    connect(d_afficheSuppPersModifierRdv,&QComboBox::activated,
            this,&fenetreRDV::onSuppPersModifRdv);
    d_ErrSuppPersModifierRdv = new QLabel{"    "};
    d_ErrSuppPersModifierRdv->setStyleSheet("color : red");
    mainLayout->addWidget(d_ErrSuppPersModifierRdv,14,0,Qt::AlignLeft);

    //Ajouter Pers
    mainLayout->addWidget(new QLabel{tr("Ajouter Personnes:")},15,0,Qt::AlignLeft);
    d_afficheAjtPersModifierRdv = new QComboBox{};
    d_afficheAjtPersModifierRdv->setDisabled(true);
    mainLayout->addWidget(d_afficheAjtPersModifierRdv,16,0,Qt::AlignLeft);
    connect(d_afficheAjtPersModifierRdv,&QComboBox::activated,
            this,&fenetreRDV::onAjtPersModifRdv);
    d_ErrAjtPersModifierRdv = new QLabel{"    "};
    d_ErrAjtPersModifierRdv->setStyleSheet("color : red");
    mainLayout->addWidget(d_ErrAjtPersModifierRdv,17,0,Qt::AlignLeft);





    central->setLayout(mainLayout);
    setCentralWidget(central);
    this->adjustSize();
}
void fenetreRDV::afficherPersSelectionSuppModifRdv()
{
    d_afficheSuppPersModifierRdv->clear();
    vector<Personne> pers{d_rdvs.rdv(d_nomModifierRdv->text().toStdString()).personnes()};
    for(const auto& p : pers)
        d_afficheSuppPersModifierRdv->addItem(QString::fromStdString(p.nom()));
}
void fenetreRDV::afficherPersSelectionAjtModifRdv()
{
    d_afficheAjtPersModifierRdv->clear();
    Rdv rdv{d_rdvs.rdv(d_nomModifierRdv->text().toStdString())};
    for(int i{0} ; i<d_personnes.taille() ; ++i)
    {
        Personne pers=d_personnes.get_personne(i);
//        if(rdv.pers_ajoutable(d_rdvs.rdvs_personne(pers.nom())))
            d_afficheAjtPersModifierRdv->addItem(QString::fromStdString(pers.nom()));
    }
}
void fenetreRDV::onActionModifierRdv()
{
    vueRdvModifier();
}
void fenetreRDV::onRechModifierRdv()
{
    if(-1==d_rdvs.rechercher(d_nomRechModifierRdv->text().toStdString()))
    {
        d_nomErrRechModifierRdv->setText(tr("Ce nom n'existe pas"));
    }
    else
    {
        Rdv rdv{d_rdvs.rdv(d_nomRechModifierRdv->text().toStdString())};
        d_nomErrRechModifierRdv->setText("");
        d_nomModifierRdv->setText(QString::fromStdString(rdv.nom()));
        d_dateFinModifierRdv->setDisplayFormat("dd/MM/yyyy/hh/mm");
        QDateTime date_deb{QDate{rdv.date_deb().jour(),rdv.date_deb().mois(), rdv.date_deb().annee()}, QTime{rdv.date_deb().heure(), rdv.date_deb().minute()}};
        d_dateDebModifierRdv->setDateTime(date_deb);
//        d_dateDebModifierRdv->setCalendarPopup(true);
    }
//    d_dateFinErrModifierRdv

}
void fenetreRDV::onModiferRdv()
{
    validation v;
    bool valide{true};
    if(!v.isNom(d_nomModifierRdv->text().toStdString()))
    {
        d_nomErrModifierRdv->setText(tr("Entrer un nom valide"));
        valide=false;
    }
    else
    {
        d_nomErrModifierRdv->setText("");

    }
    if(!v.estRdv(d_dateDebModifierRdv->text().toStdString(),d_dateFinModifierRdv->text().toStdString()))
    {
        d_dateFinErrModifierRdv->setText(tr("Entrer des dates valides"));
        valide=false;
    }
    else
    {
        d_dateFinErrModifierRdv->setText("");
    }
    if(valide)
    {
        if(d_rdvs.modifier(d_nomRechModifierRdv->text().toStdString(),d_nomModifierRdv->text().toStdString(),d_dateDebModifierRdv->text().toStdString(),d_dateFinModifierRdv->text().toStdString(),d_rdvs.rdv(d_nomRechModifierRdv->text().toStdString()).personnes()))
        {
            d_afficheAjtPersModifierRdv->setEnabled(true);
            d_afficheSuppPersModifierRdv->setEnabled(true);
            afficherPersSelectionSuppModifRdv();
            afficherPersSelectionAjtModifRdv();
        }
        else
        {
            d_dateFinErrModifierRdv->setText("Rdv non Modifier");
        }
    }

}
void fenetreRDV::onSuppPersModifRdv(int idx)
{
    Personne pers{d_personnes.get_personne(d_afficheSuppPersModifierRdv->itemText(idx).toStdString())};
    if(d_rdvs.rdv(d_nomModifierRdv->text().toStdString()).supprimer_pers(pers))
    {
        d_afficheSuppPersModifierRdv->removeItem(idx);
        d_ErrSuppPersModifierRdv->setText(tr("Personne Supprimer"));
        afficherPersSelectionAjtModifRdv();
    }
    else
    {
        d_ErrSuppPersModifierRdv->setText(tr(""));
    }

}
void fenetreRDV::onAjtPersModifRdv(int idx)
{
    Personne pers{d_personnes.get_personne(d_afficheAjtPersModifierRdv->itemText(idx).toStdString())};
    if(d_rdvs.rdv(d_nomModifierRdv->text().toStdString()).ajouter_pers(pers,d_rdvs.rdvs_personne(pers)))
    {
        d_afficheSuppPersModifierRdv->addItem(d_afficheAjtPersModifierRdv->itemText(idx));
        d_afficheAjtPersModifierRdv->removeItem(idx);
        d_ErrAjtPersModifierRdv->setText(tr("Personne Ajouter"));
    }
    else
    {
        d_ErrAjtPersModifierRdv->setText(tr("Personne non Ajoutable"));
    }
}



//vue Supprimer rdv
void fenetreRDV::vueSupprimerRdv()
{
    auto central = new QWidget{};

    auto mainLayout = new QGridLayout{central};

    mainLayout->addWidget(new QLabel{tr("Supprimer Rendez-vous")},0,1,Qt::AlignLeft);
    mainLayout->addWidget(new QLabel{tr("Nom")},1,0,Qt::AlignLeft);
    d_nomSuppRdv = new QLineEdit{};
    mainLayout->addWidget(d_nomSuppRdv,1,1,Qt::AlignLeft);
    auto btnSupp = new QPushButton{tr("Supprimer")};
    mainLayout->addWidget(btnSupp,1,3,Qt::AlignLeft);
    connect(btnSupp,&QPushButton::clicked,
            this,&fenetreRDV::onSupprimerRdv);

    d_nomErrSuppRdv = new QLabel{"     "};
    mainLayout->addWidget(d_nomErrSuppRdv,2,1,Qt::AlignLeft);


    setCentralWidget(central);
}

void fenetreRDV::onSupprimerRdv()
{
    if(d_rdvs.supprimer(d_nomSuppRdv->text().toStdString()))
    {
        d_nomErrSuppRdv->setStyleSheet("color : green");
        d_nomErrSuppRdv->setText(tr("Rendez-vous Supprimer"));
    }
    else
    {
        d_nomErrSuppRdv->setStyleSheet("color : red");
        d_nomErrSuppRdv->setText(tr("Ce nom n'existe pas"));
    }
}
void fenetreRDV::onActionSupprimerRdv()
{
    vueSupprimerRdv();
}
void fenetreRDV::onActionRechercherRdvDate()
{
    vueRechercherRdvDate();
    afficheRdv();
}
void fenetreRDV::vueRechercherRdvDate()
{
    auto central = new QWidget{};

    auto mainLayout = new QGridLayout{central};
    mainLayout->addWidget(new QLabel{tr("Recherche rendez-vous")},0,0,Qt::AlignCenter);

    d_calendar = new QCalendarWidget{};
    d_calendar->setMinimumSize(400,500);
    connect(d_calendar,&QCalendarWidget::clicked,
            this,&fenetreRDV::onDayCalendarClick);
    mainLayout->addWidget(d_calendar,1,0,Qt::AlignCenter);


    setCentralWidget(central);
}
void fenetreRDV::afficheRdv()
{
    QTextCharFormat textf =QTextCharFormat();
//    QGradient color = QGradient();
    QColor color = QColor("green");
    textf.setBackground(QBrush(color));
    for(int i=0 ; i<d_rdvs.taille() ; ++i)
    {
        Date date_deb=d_rdvs.rdv(i).date_deb();

        d_calendar->setDateTextFormat({ date_deb.annee(),date_deb.mois(),date_deb.jour()},textf);
    }
}
void fenetreRDV::vueRechercherRdvNom()
{
    auto central = new QWidget{};

    auto mainLayout = new QGridLayout{central};
    mainLayout->addWidget(new QLabel{tr("Recherche rendez-vous")},0,1,Qt::AlignLeft);

    auto rechLayout = new QVBoxLayout{};
    rechLayout->addWidget(new QLabel{tr("Nom:")});
    auto linRech = new QHBoxLayout{};
    d_nomRechRdvNom = new QLineEdit{};
    linRech->addWidget(d_nomRechRdvNom);
    auto btnRech = new QPushButton{tr("Rechercher")};
    linRech->addWidget(btnRech);
    connect(btnRech,&QPushButton::clicked,
            this,&fenetreRDV::onRechercherRdvNom);
    rechLayout->addLayout(linRech);
    d_infoRechRdvNom = new QLabel{"       "};
    rechLayout->addWidget(d_infoRechRdvNom);
    rechLayout->addStretch(1);

    mainLayout->addLayout(rechLayout,1,0);
    d_calendar = new QCalendarWidget{};
    d_calendar->setMinimumSize(400,500);
    mainLayout->addWidget(d_calendar,1,1,Qt::AlignCenter);


    setCentralWidget(central);
}
void fenetreRDV::onActionRechercherRdvNom()
{
    vueRechercherRdvNom();
}

void fenetreRDV::onRechercherRdvNom()
{
    if(d_personnes.recherche(d_nomRechRdvNom->text().toStdString())<0)
    {
        d_infoRechRdvNom->setText(tr("Cette personne n'existe pas"));
    }
    else
    {
        vector<Rdv> list_rdvs{d_rdvs.rdvs_personne(d_nomRechRdvNom->text().toStdString())};
        if(list_rdvs.size()==0)
        {
            d_infoRechRdvNom->setText(tr("Cette personne n'a pas de rdvs"));
        }
        else
        {
            afficheRdvPers(list_rdvs);
            d_infoRechRdvNom->setText(tr(""));
//            connect(d_calendar,&QCalendarWidget::clicked,
//                    this,&fenetreRDV::onDayCalendarClick);
        }
    }
}
void fenetreRDV::afficheRdvPers(const vector<Rdv>& list_rdvs)
{
    QTextCharFormat textf =QTextCharFormat();
//    QGradient color = QGradient();
    QColor color = QColor("Blue");
    textf.setBackground(QBrush(color));
    for(int i=0 ; i<list_rdvs.size() ; ++i)
    {
        Date date_deb=list_rdvs[i].date_deb();

        d_calendar->setDateTextFormat({ date_deb.annee(),date_deb.mois(),date_deb.jour()},textf);
    }
}

void fenetreRDV::onDayCalendarClick(QDate date)
{
    vector<Rdv> rdvs=d_rdvs.rdvsDeDate({date.day(),date.month(),date.year(),1,1});
    if(rdvs.size()==0)
    {
        QMessageBox msgBox{QMessageBox::Information,
        tr("Information"), tr("Il n'existe pas de rdv pour aujourd'hui!!")};
        msgBox.exec();
    }
    else
    {
        QDialog dialog{this};
        auto dialogLayout = new QGridLayout{};
        int i{0};

        dialogLayout->addWidget(new QLabel{tr("Rendez-vous d'aujourd'hui")},i++,0,Qt::AlignCenter);

        for(const auto& rdv : rdvs)
        {
            //Nom
            dialogLayout->addWidget(new QLabel{tr("Nom :")},i,0);
            dialogLayout->addWidget(new QLabel{QString::fromStdString(rdv.nom())},i++,1);
            //Personne
            vector<Personne> personnes=rdv.personnes();
            dialogLayout->addWidget(new QLabel{"Personnes: "+QString::number(rdv.nbr_pers())},i++,0);
            for(unsigned j{0} ; j<personnes.size() ; ++j)
            {
                dialogLayout->addWidget(new QLabel{QString::fromStdString(personnes[j].nom())},i,0);
                dialogLayout->addWidget(new QLabel{QString::fromStdString(personnes[j].prenom())},i,1);
                dialogLayout->addWidget(new QLabel{QString::fromStdString(personnes[j].tel())},i,2);
                dialogLayout->addWidget(new QLabel{QString::fromStdString(personnes[j].email())},i++,3);
            }
        }
        dialog.setLayout(dialogLayout);
        dialog.exec();
    }

}

