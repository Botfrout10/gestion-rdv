#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

#include"Date.h"
#include<string>
class validation
{
public:
    bool isNom(const std::string& nom) const;
    bool isEmail(const std::string& email) const;
    bool isTel(const std::string& tel) const;
    //un rdv ne peut pas dure plus de 5 heures
    //et les date d'un rdv doivent etre dans le meme jour
//    bool estRdv(const Rdv& rdv);
    bool estRdv(const Date& date_deb,const Date& date_fin) const;

};

#endif // VALIDATION_H_INCLUDED
