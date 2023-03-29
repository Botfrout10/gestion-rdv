#include "personnevues.h"
#include "PersonneLCH.h"
#include<QBoxLayout>
#include<QFormLayout>
#include<QLineEdit>
#include <QPushButton>
#include <QString>
#include <QMessageBox>


PersonneVues::PersonneVues(const PersonneLCH& personnes,QWidget *parent)
    : QWidget{parent} , d_personnes{personnes}
{}

QLayout* PersonneVues::vueAjouterPers()
{
    auto mainLayout=new QVBoxLayout{};
    mainLayout->addWidget(new QLabel{tr("Ajouter Personne")},0,Qt::AlignCenter);

    mainLayout->addWidget(new QLabel{tr("Nom:")});
    d_nomText=new QLineEdit{};
    mainLayout->addWidget(d_nomText);
    d_nomError=new QLabel{"           "};
//    d_nomError->setStyle();
    mainLayout->addWidget(d_nomError);


    mainLayout->addWidget(new QLabel{tr("Prenom:")});
    d_prenomText=new QLineEdit{};
    mainLayout->addWidget(d_prenomText);
    d_prenomError=new QLabel{"           "};
    d_prenomError->setStyleSheet("{color : red;}");
    mainLayout->addWidget(d_prenomError);

    mainLayout->addWidget(new QLabel{tr("Tel:")});
    d_telText=new QLineEdit{};
    mainLayout->addWidget(d_telText);
    d_telError=new QLabel{"           "};
//    d_telText->setStyle();
    mainLayout->addWidget(d_telError);

    mainLayout->addWidget(new QLabel{tr("Email:")});
    d_emailText=new QLineEdit{};
    mainLayout->addWidget(d_emailText);
    d_emailError=new QLabel{"           "};
//    d_emailError->setStyle();
    mainLayout->addWidget(d_emailError);

    auto btnLayout=new QHBoxLayout{};
    auto btnValider=new QPushButton{tr("Valider")};
    btnLayout->addWidget(btnValider,0,Qt::AlignRight);
    auto btnAnnuler=new QPushButton{tr("Annuler")};
    btnLayout->addWidget(btnAnnuler,0,Qt::AlignLeft);
    mainLayout->addLayout(btnLayout);
    mainLayout->addStretch(1);

    connect(btnValider, &QPushButton::clicked, this, &PersonneVues::onAjouter);
    connect(btnAnnuler, &QPushButton::clicked, this, &PersonneVues::onAnnuler);
    return mainLayout;
//        nameEdit->setStyleSheet("
//                                * {
//                                    font-family: Roboto, sans-serif;
//                                    font-size: 12pt;
//                                });

//                                QLabel {
//                                    font-size: 10pt;
//                                }

//                                QLineEdit, QCheckBox {
//                                    height: 30px;
//                                }


//                                QPushButton {
//                                    height: 40px;
//                                    padding: 5px 10px;
//                                }
//                                QPushButton {
//                                    background-color: #2C3E50;
//                                    color: white;
//                                }


//                                QPushButton:hover {
//                                    background-color: #34495E;
//                                }


//                                QPushButton:pressed {
//                                    background-color: #2C3E50;
//                                }
//                                QCheckBox {
//                                    background-color: transparent;
//                                }
//                                QFormLayout {
//                                    padding: 20px;
//                                }
//                                QFormLayout QAbstractButton {
//                                    margin-top: 10px;
//                                }


//                                QMessageBox {
//                                    font-size: 10pt;
//                                    background-color: #F5F5F5;
//                                }

//                                QMessageBox::warning {
//                                    background-color: #E74C3C;
//                                    color: white;
//                                }

//                                QMessageBox::information {
//                                    background-color: #2ECC71;
//                                    color: white;
//                                }");


}

QLayout* PersonneVues::vueRechercherPers()
{
    auto widg=new QWidget{};
    widg->addWidget(new QLabel{"fez"});
    auto mainLayout=new QVBoxLayout{};

       mainLayout->addWidget(new QLabel{tr("Afficher Personnes")},0,Qt::AlignCenter);

        auto rechercheLayout=new QHBoxLayout{};
        rechercheLayout->addWidget(new QLabel{tr("Rechercher :")},0,Qt::AlignLeft);
        d_rechercheLine=new QLineEdit{};
        rechercheLayout->addWidget(d_rechercheLine,0,Qt::AlignLeft);
        rechercheLayout->addWidget(new QPushButton{tr("Valider")},0,Qt::AlignRight);
        rechercheLayout->addStretch(1);
        mainLayout->addLayout(rechercheLayout);


        d_afficheTable=new QTableWidget{d_personnes.taille(),5};

        d_afficheTable->setHorizontalHeaderItem(0,new QTableWidgetItem{"NOM"});
        d_afficheTable->setHorizontalHeaderItem(1,new QTableWidgetItem{"PRENOM"});
        d_afficheTable->setHorizontalHeaderItem(2,new QTableWidgetItem{"TEL"});
        d_afficheTable->setHorizontalHeaderItem(3,new QTableWidgetItem{"EMAIL"});

        for(int i=0 ; i<d_personnes.taille(); ++i)
        {
            d_afficheTable->setItem(i,0,new QTableWidgetItem{QString::fromStdString(d_personnes.get_personne(i).nom())});
            d_afficheTable->setItem(i,1,new QTableWidgetItem{QString::fromStdString(d_personnes.get_personne(i).prenom())});
            d_afficheTable->setItem(i,2,new QTableWidgetItem{QString::fromStdString(d_personnes.get_personne(i).tel())});
            d_afficheTable->setItem(i,3,new QTableWidgetItem{QString::fromStdString(d_personnes.get_personne(i).email())});
//            auto btnCol=d_afficheTable->cellWidget(i,4);
//            btnCol->addWidget(new QPushButton{tr("modi")});

        }
        mainLayout->addWidget(d_afficheTable);
        return mainLayout;
}

void PersonneVues::onAjouter()
{
    bool test = d_personnes.ajouter(d_nomText->text().toStdString(), d_prenomText->text().toStdString(), d_telText->text().toStdString(), d_emailText->text().toStdString());
    if (test)
    {
        QMessageBox msgBox{QMessageBox::Information,
        tr("Information"), tr("Votre personne est ajoutée")};
        msgBox.exec();
    } else
    {
        QMessageBox msgBox{QMessageBox::Information,
        tr("Information"), tr("Votre personne existe déjà")};
        msgBox.exec();
    }

}

void PersonneVues::onAnnuler()
{
    d_nomText->setText("");
    d_prenomText->setText("");
    d_telText->setText("");
    d_emailText->setText("");
}







