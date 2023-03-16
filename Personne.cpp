#include"Personne.h"

#include<iostream>
#include<string>
#include"string_transforme.h"

using namespace std;
using namespace string_transforme;


Personne::Personne(const string& nom, const string& prenom, const string& tel, const string& email) : d_nom{nom},
    d_prenom{prenom}, d_tel{tel} , d_email{email}
{
    //Soit a chaque fois quand modifie ou cree un nouvelle personne on le met upper
    //Ou a chaque fois quand veut comparer les noms on les mets en upper
    en_maj(d_nom);
}
string Personne::nom() const
{
    return d_nom;
}
void Personne::set_nom(const string& nom)
{
    d_nom=nom;
    en_maj(d_nom);
}
string Personne::prenom() const
{
    return d_prenom;
}
void Personne::set_prenom(const string& prenom)
{
    d_prenom=prenom;
}
string Personne::tel() const
{
    return d_tel;
}
void Personne::set_tel(const string& tel)
{
    d_tel=tel;
}
string Personne::email() const
{
    return d_email;
}
void Personne::set_email(const string& email)
{
    d_email=email;
}

void Personne::set_pers(const string& nom,const string& prenom, const string& tel,const string& email)
{
    set_nom(nom);
    set_prenom(prenom);
    set_email(email);
    set_tel(tel);

}
void Personne::set_pers(const Personne& pers)
{
    set_nom(pers.nom());
    set_prenom(pers.prenom());
    set_email(pers.email());
    set_tel(pers.tel());
}


//lire une personne d'apres un istream (nom prenom tel email)
bool Personne::lire(istream& ist)
{
    char ch;
    string nom,prenom,tel,email;
    ist>>nom>>ch>>prenom>>ch>>tel>>email;
    if(ist.good())
    {
        d_nom=nom;
        d_prenom=prenom;
        d_tel=tel;
        d_email=email;
        return true;
    }
    return false;
}
istream& operator>>(istream& ist,Personne& p)
{
    p.lire(ist);
    return ist;
}

void Personne::ecrire(ostream& ost) const
{
    ost<<d_nom<<' '<<d_prenom<<' '<<d_tel<<' '<<d_email<<' '<<endl;
}
ostream& operator<<(ostream& ost,Personne& p)
{
    p.ecrire(ost);
    return ost;
}
