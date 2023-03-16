#ifndef PERSONNE_H
#define PERSONNE_H
#include<string>

/**
 * @class
 * @pre le nom est l'identifient de la classe
 */
class Personne
{
public:
    //tout les noms de la liste son majiscule ou miniscule
    Personne(const std::string& nom, const std::string& prenom, const std::string& tel, const std::string& email);
    //ces fonctions c'est juste pour permetre d'ajouter et supprimer des rdvs d'apres une personne
//    void ajouter_rdv(Rdv& rdv);
//    void supprimer_rdv(Rdv& rdv);

    bool lire(std::istream& ist);
    void ecrire(std::ostream& ost) const;
    friend std::istream& operator>>(std::istream& ist,Personne& p);
    friend std::ostream& operator<<(std::ostream& ost,Personne& p);

    //les seters et geters
    std::string nom() const;
    void set_nom(const std::string& nom);
    std::string prenom() const;
    void set_prenom(const std::string& prenom);
    std::string tel() const;
    void set_tel(const std::string& tel);
    std::string email() const;
    void set_email(const std::string& email);

    //modifier les proprietes de la personne crt existe dans la liste ;mais on peut modifier juste les proprietes que l'on veut => set_pers(nom_du_param = valeur de param) ex: set_pers(crt,"mehdi",email="email@em.c");
    void set_pers(const std::string& nom,const std::string& prenom, const std::string& tel,const std::string& email);
    void set_pers(const Personne& pers);



private:
    std::string d_nom;
    std::string d_prenom;
    std::string d_tel;
    std::string d_email;


    //j'ai choisi d'ajouter un tableau des rdv pour chaque personne car cela va diminuer la complexite de plusiers fonctions
    //l'ajout de tableau engendre le probleme de couplage entre la classe rdv et la classe personne
//    vector<Rdv> d_rdv;
};



#endif // PERSONNE_H
