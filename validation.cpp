#include"validation.h"
#include<regex>
#include<string>

bool validation::isEmail(const std::string& email) const
{
    const std::regex r{"(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"};
    return std::regex_match(email,r);
}

bool validation::isNom(const std::string& nom) const
{
    //il support pas les espaces entre les noms
    const std::regex r{"[a-zA-Z]{1,20}"};
    return std::regex_match(nom,r);
}

bool validation::isTel(const std::string& tel) const
{
    //exemple "+919136812895"
    const std::regex r{"^[+]{1}[0-9]{10,15}$"};
    return std::regex_match(tel,r);
}

bool validation::estRdv(const Date& date_deb,const Date& date_fin) const
{
    int difHeure{date_fin.heure()-date_deb.heure()};
    return(date_deb.jour() == date_fin.jour() && date_deb.annee() == date_fin.annee() && date_deb.mois() == date_fin.mois() && difHeure<=5 && difHeure>0);
}
