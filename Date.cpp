#include"Date.h"

//Date::Date() : d_jour{1},d_mois{1},d_annee{2023} , d_heure{1} , d_minute{0} {}
Date::Date(unsigned jour,unsigned mois, unsigned annee , unsigned heure, unsigned minute) :
    d_jour{jour} , d_mois{mois} , d_annee{annee} , d_heure{heure} , d_minute{minute}
{}


unsigned Date::jour() const
{
    return d_jour;
}
unsigned Date::mois() const
{
    return d_mois;
}
unsigned Date::annee() const
{
    return d_annee;
}
unsigned Date::heure() const
{
    return d_heure;
}
unsigned Date::minute() const
{
    return d_minute;
}
void Date::ecrire(std::ostream& ost) const
{
    ost<<d_jour<<'/'<<d_mois<<'/'<<d_annee<<','<<d_heure<<':'<<d_minute<<' ';
}
bool Date::lire(std::istream& ist)
{
    char ch;
    unsigned j,m,a,mi,h;

    ist>>j>>ch>>m>>ch>>a>>ch>>h>>ch>>mi;
    if(ist.good())
    {
        d_jour=j;
        d_mois=m;
        d_annee=a;
        d_heure=h;
        d_minute=mi;
        return true;
    }
    return false;
}
std::ostream& operator<<(std::ostream& ost,const Date& date)
{
    date.ecrire(ost);
    return ost;
}
std::istream& operator>>(std::istream& ist,Date& date)
{
    date.lire(ist);
    return ist;
}

//d_d.estconflit(d_f)
bool Date::estconflict(const Date& date) const
{
    //this est la date de debut d'un rdv
    //date est la date de fin d'un autre rdv
    if(d_jour==date.d_jour && d_mois==date.d_mois && d_annee==date.d_annee && d_heure==date.heure())
        return (this->d_minute<=date.d_minute);
    else
        return false;
}
