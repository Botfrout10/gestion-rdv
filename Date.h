#ifndef DATE_H
#define DATE_H


#include<iostream>

/**
 * @class represente une date et elle est faite pour gerer les dates de debut et de fin des rdvs
*/
class Date
{
public:
    Date();
    /**
     * @brief constructeur d'une date qui prend les param
     * @param [in] jour  - un entier positif qui represente le jour
     * @param [in] mois  - un entier positif qui represente le mois
     * @param [in] annee  - un entier positif qui represente l'annee
    */
    Date(unsigned jour,unsigned mois, unsigned annee , unsigned heure, unsigned minute);
    //Date d{"01/02/2002 , 10:22"}
    Date(const std::string& date);
    unsigned jour() const;
    unsigned mois() const;
    unsigned annee() const;
    unsigned heure() const;
    unsigned minute() const;
    void ecrire(std::ostream& ost) const;
    bool lire(std::istream& ist);
    friend std::ostream& operator<<(std::ostream& ost,const Date& date);
    friend std::istream& operator>>(std::istream& ist,Date& date);
    //un rdv il ne peut pas commence s'il est deja un rdv en cours ?
    bool egale(const Date& date) const;
    friend bool operator ==(const Date& date1,const Date& date2);
    friend bool operator !=(const Date& date1,const Date& date2);
    friend bool operator >(const Date& date1,const Date& date2);
    friend bool operator <(const Date& date1,const Date& date2);
    friend bool operator <=(const Date& date1,const Date& date2);
    friend bool operator >=(const Date& date1,const Date& date2);



private:
    unsigned d_jour;
    unsigned d_mois;
    unsigned d_annee;
    unsigned d_heure;
    unsigned d_minute;
};

#endif // DATE_H
