#ifndef DATE_H
#define DATE_H


#include<iostream>
class Date
{
public:
//    Date();
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
    bool estconflict(const Date& date) const;

private:
    unsigned d_jour;
    unsigned d_mois;
    unsigned d_annee;
    unsigned d_heure;
    unsigned d_minute;
};

#endif // DATE_H
