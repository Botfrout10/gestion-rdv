#ifndef PERSONNELCH_H
#define PERSONNELCH_H

#include"Personne.h"
#include<string>
#include<vector>

class Rdv;

using namespace std;

/**
 * @class Personne represente les chainnons de la liste
 * @pre le nom est l'identifient de la classe
 */
class PersonneCH
{
public:
    PersonneCH(const Personne& personne);
    PersonneCH(const string& nom, const string& prenom, const string& tel, const string& email);

    Personne d_personne;
    PersonneCH *d_suiv;
    PersonneCH *d_prec;
};

/**
 * @class PersonneLCH represente une liste doublement chainnee des personnes
 * @pre pour chaque nouveau chainnon en suppose que le nom n'existe pas dans la liste
 */
class PersonneLCH
{

public:
        PersonneLCH();
        PersonneLCH(const PersonneLCH& p_list);

        /**
        * @brief Ajouter une personne a une liste doublement chainnee
        * @param[in] nom - le nom de la nouvelle personne
        * ...
        * @pre nom != tous les noms dans la liste
        */
        void ajouter(PersonneCH*& pers);
        bool ajouter(const string& nom, const string& prenom, const string& tel,const string& email);
        /**
         * @brief Supprimer une personne par son nom
         * @param[in] nom - Le nom de la personne a supprimer
         * @param[in] list_rdv - tableau des rdvs de la personne a supprimer
         * @pre la peronne ne doit pas avoir des rdvs
         */
        void supprimer(const string& nom , const vector<Rdv>& list_rdv);
        /**
         * @brief modifier les propriete d'une personne par son nom
         * @param[in] nom_p - le nom de la personne a modifier
         * @param[in] nom - le nouveau nom de la personne a modifier
        */
        void modifier(const string& nom_p,const string& nom,const string& prenom, const string& tel,const string& email);

        /**
         * @brief recherche une personne par le nom
         * @param nom - nom de la personne a rechercher
         * @return vrai si la personne existe et faux dans le cas contraire
         */
        bool recherche(const string& nom) const;

        int pers_existe(PersonneCH*& pers) const;
        int pers_existe(const string& nom)const;

        //ces 2 methodes throw a run time error il faut ajouter un handler
        Personne& get_personne(const string& nom) const;
        Personne& get_personne(int idx) const;



        int taille() const;
        bool vide() const;


        //lire plusieurs Personnes a partir d'un istream
        void lire(istream& ist);
        //ecrire toutes les Personnes dans un ostream
        void ecrire(ostream& ost) const;

        friend ostream& operator<<(ostream& ost,const PersonneLCH& p);
        friend istream& operator>>(istream& ist,PersonneLCH& p);


        //fonction qui suprime une personne
        void supprimer(const string& nom);

    private:
        PersonneCH *d_tete;
        PersonneCH *d_fin;
        int d_taille;

    //  Sous programme pour la methode ajouter
        void ajout_vide(const string& nom, const string& prenom, const string& tel,const string& email);
        void ajout_entete(const string& nom, const string& prenom, const string& tel,const string& email);
        void ajout_milieu(PersonneCH*& crt,const string& nom, const string& prenom, const string& tel,const string& email);
        void ajout_fin(const string& nom, const string& prenom, const string& tel,const string& email);

        void ajout_vide(PersonneCH*& pers);
        void ajout_entete(PersonneCH*& pers);
        void ajout_milieu(PersonneCH*& crt,PersonneCH*& pers);
        void ajout_fin(PersonneCH*& pers);

    //  Sous programme pour la methode supprimer
        void supprimer_entete();
        void supprimer_milieu(PersonneCH*& crt);
        void supprimer_fin();
};

#endif // PERSONNELCH_H
