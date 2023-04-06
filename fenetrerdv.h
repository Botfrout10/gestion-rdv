#ifndef FENETRERDV_H
#define FENETRERDV_H
#include "PersonneLCH.h"
#include "RdvLCH.h"
#include <QStackedLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QDateEdit>
#include <QComboBox>


#include <QMainWindow>

class fenetreRDV : public QMainWindow
{
    Q_OBJECT
public:
    fenetreRDV(const PersonneLCH& pers, const RdvLCH& rdv, QWidget *parent = nullptr);

private:
    PersonneLCH d_personnes;
    RdvLCH d_rdvs;


    //vue Personne:
    //Vue ajouter Personne
    QLabel  *d_nomErrorAjtPers,
            *d_prenomErrorAjtPers,
            *d_telErrorAjtPers,
            *d_emailErrorAjtPers;
    QLineEdit *d_nomTextAjtPers,
               *d_prenomTextAjtPers,
               *d_telTextAjtPers,
               *d_emailTextAjtPers;

    //vue Rechercher Personne
    QLineEdit *d_nomTextRechPers;
    QLabel  *d_nomRechPers,
            *d_prenomRechPers,
            *d_telRechPers,
            *d_emailRechPers;

    //vue Modifier Personne
    QLineEdit *d_rechNomTextModifPers,
              *d_nomTextModiPers,
              *d_prenomTextModiPers,
              *d_telTextModiPers,
                *d_emailTextModiPers;
    QLabel *d_rechNomErrModifPers,
            *d_nomErrModiPers,
            *d_prenomErrModiPers,
            *d_telErrModiPers,
              *d_emailErrModiPers;
    //vue Supprimer Personne
    QLineEdit *d_nomTextSuppPers;
    QLabel *d_nomErrSuppPers;
    //vue Afficher Personne
/********************************/
    //vue Rdv:
    //Vue ajouter Rdv
    QLabel  *d_nomErrorAjtRdv,
            *d_dateDebErrorAjtRdv,
            *d_dateFinErrorAjtRdv;

    QLineEdit *d_nomTextAjtRdv;
    QDateEdit *d_dateDebAjtRdv,
              *d_dateFinAjtRdv;
    QComboBox *d_affichePersAjtRdv;


    //le menuBar
    void creeMenu();

    //vue Personne
    void vuePersAjouter();
    void vuePersRechercher();
    void vuePersModifier();
    void vuePersSupprimer();
    void vuePersAfficher();
    //vue Rdv
    void vueRdvAjouter();
    void afficherPersSelectionAjtRdv();
public slots:
    //slots Personne
    void onActionAjouterPers();
    void onAjouterPers();

    void onActionRecherchePers();
    void onRechercherPers();

    void onActionModifierPers();
    void onModifierPers();

    void onActionSupprimerPers();
    void onSupprimerPers();

    void onActionAfficherPers();


    //slots Rdv
    void onActionAjouterRdv();
    void onAjouterPersRdv();


    void onAppClose();

};

#endif // FENETRERDV_H
