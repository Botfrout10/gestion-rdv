#ifndef PERSONNE_H
#define PERSONNE_H
#include<string>

/**
 * @class represente une personne par son nom, prenom, tel, email
 * @pre le nom est l'identifient de la classe
 */
class Personne
{
public:
    /**
     * @brief constructeur par default
     */
    Personne();
    /**
     * @brief Constructeur par recopie
     * @param pers[in] - une peronne
     */
    Personne(const Personne& pers);

    //tout les noms de la liste son majiscule
    /**
     * @brief Constructeur qui prend le nom , prenom ,tel et email pour construit une personne
     * @param nom[in] - chaine de charachtere qui identifie chaque objet
     * @param prenom[in] - chaine de charachtere represente le prenom de l'objet
     * @param tel[in] - chaine de charachtere represente le num de telephone de l'objet
     * @param email[in] - chaine de charachtere represente l'email de l'objet
     * @post en met le nom au majiscule pour que l'on puisse le compare avec d'autre nom des autres personnes
     */
    Personne(const std::string& nom, const std::string& prenom, const std::string& tel, const std::string& email);

    /**
     * @brief lire une personne d'apres un istream la lecture sa fait : nom prenom tel email
     * @param ist[in,out] - l'istream dont on ecrit
     * @return vrai si la la lecture est bonne et faux si non
     */
    bool lire(std::istream& ist);
    /**
     * @brief ecrire une personne dans un ostream l'ecriture sa fait : nom prenom tel email
     * @param ost[in,out] - l'istream dont on lit
     */
    void ecrire(std::ostream& ost) const;
    friend std::istream& operator>>(std::istream& ist,Personne& p);
    friend std::ostream& operator<<(std::ostream& ost,const Personne& p);

    //les seeters et geters
    std::string nom() const;
    void set_nom(const std::string& nom);
    std::string prenom() const;
    void set_prenom(const std::string& prenom);
    std::string tel() const;
    void set_tel(const std::string& tel);
    std::string email() const;
    void set_email(const std::string& email);

    /**
     * @brief modifier les proprietes de la personne
     * @param nom[in] - chaine de charachtere qui identifie chaque objet
     * @param prenom[in] - chaine de charachtere represente le prenom de l'objet
     * @param tel[in] - chaine de charachtere represente le num de telephone de l'objet
     * @param email[in] - chaine de charachtere represente l'email de l'objet
     * @post en met le nom au majiscule pour que l'on puisse le compare avec d'autre nom des autres personnes
     */
    void set_pers(const std::string& nom,const std::string& prenom, const std::string& tel,const std::string& email);
    /**
     * @brief modifier les proprietes de la personne
     * @param pers[in] - une personne
     */
    void set_pers(const Personne& pers);

    /**
     * @brief renvoit un objet de la personne que l'on peut modifie
     * @return la personne courante
     */
    Personne& get_personne();



private:
    std::string d_nom;
    std::string d_prenom;
    std::string d_tel;
    std::string d_email;

};



#endif // PERSONNE_H
