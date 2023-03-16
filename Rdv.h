#ifndef RDV_H
#define RDV_H

#include<string>
#include<vector>
#include<iostream>


#include"Date.h"
class Personne;

class Rdv
{
    friend class RdvLCH;
public:
    //On peut cree un rdv sans connaitre les personnes (&personnes={})
    Rdv(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne>& personnes=std::vector<Personne>());

    int nbr_pers() const;
    //il ne faut pas qu'une personne assiste a plusieurs rdv a la meme heure
    //list_rdv de la personne
    //parcourir la list des rdv et chercher les conflict entre les dates des fin des rdvs de la liste et la la date de debut de ce rdv et le sens contraire aussi
    void ajouter_pers(const Personne& personne,const std::vector<Rdv>& list_rdv);
    /*Pour modifier une attribut d'une classe friend il faut passe un objet de cette classe en parametre */
    void supprimer_pers(Personne*& personne);
    void supprimer_pers(std::string& nom);

    //return -1 si la pers n'existe pas et l'indice si la pers existe
    int pers_exist(std::string& nom) const;

    //geters et seeters
    std::string nom() const;
    void set_nom(const std::string &nom);
    Date date_deb() const;
    void set_date_deb(const Date& date_deb);
    Date date_fin() const;
    void set_date_fin(const Date& date_fin);
    std::vector<Personne> personnes() const;
    void set_personnes(const std::vector<Personne> &personnes);
    void set_rdv(const std::string& nom,const Date& date_deb,const Date& date_fin , const std::vector<Personne>& personnes);

    bool lire(std::istream& ist);
    void ecrire(std::ostream& ost) const;
    friend std::istream& operator>>(std::istream& ist,Rdv*& rdv);
    friend std::ostream& operator<<(std::ostream& ost,Rdv*& rdv);
private:
    //le nom est l'identifiant
    std::string d_nom;
    Date d_date_deb;
    Date d_date_fin;
    std::vector<Personne> d_personnes;

    //nombre maximum des personnes qui assite a un rdv
    //j'ai ajouter cet attribut pour des raisons de complexite afin d'avoir reserve la place pour le vecteur
    const static int MAX_PERS{30};

    //test si la personne est ajoutable dans un rdv
    bool pers_ajoutable(const std::vector<Rdv>& list_rdv) const;
};
#endif // RDV_H
