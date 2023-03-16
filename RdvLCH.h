#ifndef RDVLCH_H
#define RDVLCH_H

#include<string>
#include<vector>
#include<iostream>


#include"Date.h"
class Personne;
#include"Rdv.h"


class RdvCH
{
public:
    RdvCH(const Rdv& rdv);
    RdvCH(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne>& personnes=std::vector<Personne>());

    Rdv d_rdv;
    RdvCH *d_suiv;
    RdvCH *d_prec;
};

class RdvLCH
{
public:
    RdvLCH();
    RdvLCH(const RdvLCH& RdvLCH);
    void ajouter(std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes);
    void ajouter(RdvCH*& rdv);
    void supprimer(std::string& nom);
    void modifier(std::string& nom_p,std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes);
    //return -1 si l' element n'existe pas
    int rechercher(std::string& nom) const;
    int taille() const;
    bool vide() const;

    Rdv& rdv(int idx) const;
    Rdv& rdv(std::string& nom) const;


    //lire plusieurs Rdvs a partir d'un istream
    void lire(std::istream& ist);
    //ecrire toutes les Rdvs dans un ostream
    void ecrire(std::ostream& ost) const;

    //remplir list_rdv par les rdv de la personne
    void rdvs_personne(const Personne& pers,std::vector<Rdv> list_rdvs) const;
    void rdvs_personne(std::string& nom,std::vector<Rdv> list_rdvs) const;
    std::vector<Rdv> rdvs_personne(std::string& nom) const;
    //il faut ajouter les surcharge d'operateur
    friend std::ostream& operator<<(std::ostream& ost,const RdvLCH& r);
    friend std::istream& operator>>(std::istream& ist,RdvLCH& r);
private:
    RdvCH *d_tete;
    RdvCH *d_fin;
    int d_taille;

    //  Sous programme pour la methode ajouter
    void ajout_vide(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes);
    void ajout_entete(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes);
    void ajout_milieu(RdvCH*& crt,const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes);
    void ajout_fin(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes);

    void ajout_vide(RdvCH*& rdv);
    void ajout_entete(RdvCH*& rdv);
    void ajout_milieu(RdvCH*& crt,RdvCH*& rdv);
    void ajout_fin(RdvCH*& rdv);

//  Sous programme pour la methode supprimer
    void supprimer_entete();
    void supprimer_milieu(RdvCH*& crt);
    void supprimer_fin();
};

#endif // RDVLCH_H