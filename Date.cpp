#include"Date.h"
#include<sstream>
#include<vector>

Date::Date() : d_jour{1},d_mois{1},d_annee{2023} , d_heure{1} , d_minute{0} {}
Date::Date(unsigned jour,unsigned mois, unsigned annee , unsigned heure, unsigned minute) :
    d_jour{jour} , d_mois{mois} , d_annee{annee} , d_heure{heure} , d_minute{minute}
{}
Date::Date(const std::string& date)
{
    std::istringstream iss{date};
    std::string str;
    std::vector<unsigned> d;
    d.reserve(4);
    while(getline(iss,str,'/'))
    {
        d.push_back(std::stoi(str));
    }
    d_jour=d[0];
    d_mois=d[1];
    d_annee=d[2];
    d_heure=d[3];
    d_minute=d[4];
}


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
bool Date::egale(const Date& date) const
{
    return (d_jour==date.jour() && d_mois==date.mois() && d_annee==date.annee() && d_heure==date.heure() && d_minute==date.minute());
}

bool operator ==(const Date& date1,const Date& date2)
{
    return date1.egale(date2);
}
bool operator !=(const Date& date1,const Date& date2)
{
    return !date1.egale(date2);
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

bool operator >(const Date& date1,const Date& date2)
{
    return ((date1.annee()>date2.annee()) ||
            (date1.annee()==date2.annee() && date1.mois()>date2.mois()) ||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()>date2.jour()) ||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()==date2.jour() && date1.heure()>date2.heure())||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()==date2.jour() && date1.heure()==date2.heure() && date1.minute()>date2.minute()));
}
bool operator <(const Date& date1,const Date& date2)
{
    return ((date1.annee()<date2.annee()) ||
            (date1.annee()==date2.annee() && date1.mois()<date2.mois()) ||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()<date2.jour()) ||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()==date2.jour() && date1.heure()<date2.heure())||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()==date2.jour() && date1.heure()==date2.heure() && date1.minute()<date2.minute()));
}
bool operator <=(const Date& date1,const Date& date2)
{
    return ((date1.annee()<=date2.annee()) ||
            (date1.annee()==date2.annee() && date1.mois()<=date2.mois()) ||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()<=date2.jour()) ||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()==date2.jour() && date1.heure()<=date2.heure())||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()==date2.jour() && date1.heure()==date2.heure() && date1.minute()<=date2.minute()));
}
bool operator >=(const Date& date1,const Date& date2)
{
    return ((date1.annee()>=date2.annee()) ||
            (date1.annee()==date2.annee() && date1.mois()>=date2.mois()) ||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()>=date2.jour()) ||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()==date2.jour() && date1.heure()>=date2.heure())||
            (date1.annee()==date2.annee() && date1.mois()==date2.mois() && date1.jour()==date2.jour() && date1.heure()==date2.heure() && date1.minute()>=date2.minute()));
}
