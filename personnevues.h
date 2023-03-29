#ifndef PERSONNEVUES_H
#define PERSONNEVUES_H

#include <QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QFormLayout>
#include <QLineEdit>
#include <QTableWidget>

#include "PersonneLCH.h"
class PersonneVues : public QWidget
{
    Q_OBJECT
public:
    explicit PersonneVues(const PersonneLCH& personnes,
                          QWidget *parent = nullptr);
    QLayout* vueAjouterPers();
    QLayout* vueRechercherPers();

private:
    PersonneLCH d_personnes;

    //Vue ajouter
    QLabel  *d_nomError,
            *d_prenomError,
            *d_telError,
            *d_emailError;

    QLineEdit *d_nomText,*d_prenomText,*d_telText,*d_emailText;
    //Vue rechercher
    QLineEdit *d_rechercheLine;
    QTableWidget *d_afficheTable;

public slots:
    void onAjouter();
    void onAnnuler();

signals:

};

#endif // PERSONNEVUES_H
