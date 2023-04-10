#include"Rdv.h"
#include"Personne.h"
#include"Date.h"
#include"string_transforme.h"
using namespace string_transforme;

Rdv::Rdv() : d_nom{"N/A"} , d_date_deb{} , d_date_fin{} , d_personnes{}
{}
Rdv::Rdv(const Rdv& rdv) : d_nom{rdv.nom()} , d_date_deb{rdv.date_deb()} , d_date_fin{rdv.date_fin()} , d_personnes{rdv.personnes()}
{
    en_maj(d_nom);
}
Rdv::Rdv(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne>& personnes)
:d_nom{nom} , d_date_deb{date_deb} , d_date_fin{date_fin} , d_personnes{personnes}
{
    d_personnes.reserve(MAX_PERS);
    en_maj(d_nom);
}

int Rdv::nbr_pers() const
{
    return d_personnes.size();
}

//list_rdv d'une personne
bool Rdv::pers_ajoutable(const std::vector<Rdv>& list_rdv) const
{
    //verifier si le nombre maximum des personnes dans un rdv est atteint
    if(d_personnes.size()==MAX_PERS)
        return false;
    //si la personne a aucun rdv donc il est disponible
    //sinon il faut comparer tous les date de fin de ces rdvs avec la date de debut de ce rdv "(this)"
    if(list_rdv.size()==0)
        return true;
    //(il faut parcourir tous les rdv de la personne) => ajouter une variable d_rdv[] =>couplage entre les deux classes rdv et personne
    // (ou parcourir tous les rdvs et chercher dans qu'ils lui sont dedans) =>complexite
    //et les comparer avec (this)
    //si il y aura des conflict return false
    unsigned i{0};
//    cout<<d_date_deb<<list_rdv[i].date_fin();
    while(i<list_rdv.size() && !conflict(list_rdv[i]) && d_nom != list_rdv[i].nom())
    {
        //date de deb de nouveau rdv => d_date_deb
        //date de fin des rdvs de la pers => rdv.d_date_fin
        ++i;
    }
    return (i==list_rdv.size());
}

//list_rdv d'une personne
bool Rdv::ajouter_pers(const Personne& personne,const vector<Rdv>& list_rdv)
{
    std::string nom_pers{personne.nom()};
    if(pers_exist(nom_pers)==-1 &&
       pers_ajoutable(list_rdv))
    {
        //ajouter la personne dans la table des personnes qui assitent a ce rdv
        d_personnes.push_back(personne);
        return true;
    }
    return false;
}

bool Rdv::supprimer_pers(const Personne& personne)
{
    if(d_personnes.size()==0)
        return false;
    int i{pers_exist(personne.nom())};
    if(i>=0)
    {
        //j'ai utilise cela "d_personnes.begin()" car la fonction prend en parametre un iterator
        //supprimer la personne du rdv
        d_personnes.erase(d_personnes.begin()+i);
        return true;
    }
}
bool Rdv::supprimer_pers(const std::string& nom)
{
    std::string nom_modif{nom};
    en_maj(nom_modif);
    if(d_personnes.size()==0)
        return false;
    int i{pers_exist(nom_modif)};
    if(i>=0)
    {
        //j'ai utilise cela "d_personnes.begin()" car la fonction prend en parametre un iterator
        //supprimer la personne du rdv
        d_personnes.erase(d_personnes.begin()+i);
        return true;
    }
}


int Rdv::pers_exist(const std::string& nom) const
{
    std::string nom_modif{nom};
    en_maj(nom_modif);
    unsigned i{0};
    while(i<d_personnes.size() && d_personnes[i].nom()!=nom_modif)
        ++i;
    if(i==d_personnes.size())
        return -1;
    return i;
}
bool Rdv::conflict(const Rdv& rdv) const
{
    //         d_deb        d_fin
    //          |-------------|
    //cas1:
    //|-------------|
    //cas2:
    //                  |-------------|
    //cas3:
    //            |--------|
//    return ((rdv.date_deb()<d_date_deb && rdv.date_fin()>d_date_deb) ||
//            (rdv.date_deb()<d_date_fin && rdv.date_fin()>d_date_fin) ||
//            (rdv.date_deb()>d_date_deb && rdv.date_fin()<d_date_fin));
    if (d_date_deb.annee() == rdv.date_fin().annee() && d_date_deb.mois() == rdv.date_fin().mois() && d_date_deb.jour() == rdv.date_fin().jour()) {
           if (d_date_fin.heure() < rdv.date_deb().heure() || rdv.date_fin().heure() < d_date_deb.heure()) {
               return false;
           }
           if (d_date_fin.heure() == rdv.date_deb().heure() && d_date_fin.minute() <= rdv.date_deb().minute()) {
               return false;
           }
           if (d_date_deb.heure() == rdv.date_fin().heure() && d_date_deb.minute() >= rdv.date_fin().minute()) {
               return false;
           }
           return true;
       }
       return false;
}

//nom_rdv date_deb date_fin nbr_pers() [ pers1 ] [ pers2 ]...
bool Rdv::lire(std::istream& ist)
{
    std::string nom;
    Date d_d,d_f;
    char ch;
    int i=0,nb;
    ist>>nom>>d_d>>d_f>>nb;

    if(ist.good())
    {
        std::vector<Personne> personnes;
        personnes.reserve(nb);
        Personne p{};
        while( i<nb && ist>>ch>>p>>ch)
        {
            personnes.push_back(p);
            ++i;
        }
        d_nom=nom;
        d_date_deb=d_d;
        d_date_fin=d_f;
        d_personnes=personnes;
        return true;
    }
    return false;
}
//nom date_deb date_fin nbr_pers() [ personnes[0] ] [ personnes[1] ]...
void Rdv::ecrire(ostream& ost) const
{
    ost<<d_nom<<' '<<d_date_deb<<d_date_fin<<' '<<nbr_pers()<<' ';
    if(nbr_pers()>0)
    {
        for(unsigned i{0} ; i<d_personnes.size() ; ++i)
        {
            ost<<"[ "<<d_personnes[i]<<" ] ";
        }

    }
}

std::istream& operator>>(std::istream& ist,Rdv& rdv)
{
    rdv.lire(ist);
    return ist;
}
std::ostream& operator<<(std::ostream& ost,const Rdv& rdv)
{
    rdv.ecrire(ost);
    return ost;
}
std::string Rdv::nom() const
{
    return d_nom;
}
void Rdv::set_nom(const std::string &nom)
{
    d_nom=nom;
    en_maj(d_nom);
}
Date Rdv::date_deb() const
{
    return d_date_deb;
}
void Rdv::set_date_deb(const Date& date_deb)
{
    d_date_deb=date_deb;
}
Date Rdv::date_fin() const
{
    return d_date_fin;
}
void Rdv::set_date_fin(const Date& date_fin)
{
    d_date_fin=date_fin;
}
std::vector<Personne> Rdv::personnes() const
{
    return d_personnes;
}
void Rdv::set_personnes(const std::vector<Personne> &personnes)
{
    d_personnes=personnes;
}

void Rdv::set_rdv(const std::string& nom,const Date& date_deb,const Date& date_fin , const std::vector<Personne>& personnes)
{
    set_nom(nom);
    set_date_deb(date_deb);
    set_date_fin(date_fin);
    set_personnes(personnes);
}
