#ifndef FENETRERDV_H
#define FENETRERDV_H
#include "PersonneLCH.h"
#include "RdvLCH.h"
#include <QStackedLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCalendarWidget>


#include <QMainWindow>

class fenetreRDV : public QMainWindow
{
    Q_OBJECT
public:
    fenetreRDV(const PersonneLCH& pers, const RdvLCH& rdv, QWidget *parent = nullptr);

private:
    PersonneLCH d_personnes;
    RdvLCH d_rdvs;
    //le menuBar
    void creeMenu();


    // partie personne anais , oussama
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


    //creation de vue Personne
    void vuePersAjouter();
    void vuePersRechercher();
    void vuePersModifier();
    void vuePersSupprimer();
    void vuePersAfficher();


/********************************/

    //partie rdv mehdi , amine
    //vue Rdv:
    //Vue ajouter Rdv
    QLabel  *d_dateFinErrorAjtRdv,
            *d_nomErrorAjtRdv,
            *d_infoAjtPersRdv;

    QLineEdit *d_nomTextAjtRdv;
    QDateTimeEdit *d_dateDebAjtRdv,
              *d_dateFinAjtRdv;
    QComboBox *d_affichePersAjtRdv;
    QPushButton *d_btnAjtRdv;

    //vue Modifier Rdv:
    QLineEdit *d_nomRechModifierRdv,
              *d_nomModifierRdv;
    QLabel *d_nomErrRechModifierRdv,
            *d_nomErrModifierRdv,
            *d_dateFinErrModifierRdv,
            *d_ErrSuppPersModifierRdv,
            *d_ErrAjtPersModifierRdv;
    QDateTimeEdit *d_dateDebModifierRdv,
                   *d_dateFinModifierRdv;
    QComboBox *d_afficheSuppPersModifierRdv,
               *d_afficheAjtPersModifierRdv;
    //vue Supprimer Rdv
    QLineEdit *d_nomSuppRdv;
    QLabel *d_nomErrSuppRdv;
    //Vue rechercher rdv par date
    QCalendarWidget *d_calendar;
    //Vue rechercher rdv par nom
    QLineEdit *d_nomRechRdvNom;
    QLabel *d_infoRechRdvNom;


    //Creation vue Rdv
    //vue Ajouter
    void vueRdvAjouter();
    void afficherPersSelectionAjtRdv();
    //vue Modifier
    void vueRdvModifier();
    void afficherPersSelectionSuppModifRdv();
    void afficherPersSelectionAjtModifRdv();
    //vue Supprimer
    void vueSupprimerRdv();
    //vues Recherche:
    //vue Recherche par date
    void vueRechercherRdvDate();
    //vue Recherche par Nom
    void vueRechercherRdvNom();

    void afficheRdv();
    void afficheRdvPers(const vector<Rdv>& list_rdvs);


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
/***********************************/


    //slots Rdv
    //ajouter rdv
    void onActionAjouterRdv();
    void onAjouterPersRdv(int idx);
    void onAjouterRdv();

    //modifier rdv
    void onActionModifierRdv();
    void onRechModifierRdv();
    void onModiferRdv();
    void onSuppPersModifRdv(int idx);
    void onAjtPersModifRdv(int idx);
    //Supprimer rdv
    void onActionSupprimerRdv();
    void onSupprimerRdv();
    //Rechercher rdv par Dare
    void onActionRechercherRdvDate();
    void onDayCalendarClick(QDate date);
    //Recherche rdv par nom
    void onActionRechercherRdvNom();
    void onRechercherRdvNom();



    //app
    void onAppClose();


};

#endif // FENETRERDV_H
