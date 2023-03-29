#include"RdvLCH.h"
#include"Rdv.h"
#include"Personne.h"
#include"Date.h"
#include"string_transforme.h"
using namespace string_transforme;

RdvCH::RdvCH(const Rdv& rdv) : d_rdv{rdv} , d_suiv{nullptr} , d_prec{nullptr}
{}

RdvCH::RdvCH(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne>& personnes)
: d_rdv{nom,date_deb,date_fin,personnes} , d_suiv{nullptr} , d_prec{nullptr}
{}



RdvLCH::RdvLCH() : d_tete{nullptr} , d_fin{nullptr} , d_taille{0}
{}
RdvLCH::RdvLCH(const RdvLCH& list_rdv): d_tete{nullptr} , d_fin{nullptr} , d_taille{list_rdv.taille()}
{
    RdvCH *crt{list_rdv.d_tete};
    while(crt!=nullptr)
    {
        RdvCH *rdv=new RdvCH{crt->d_rdv};
        if(d_tete==nullptr)
            ajout_vide(rdv);
        else
            ajout_fin(rdv);
        crt=crt->d_suiv;
    }
}

int RdvLCH::taille() const
{
    return d_taille;
}
bool RdvLCH::vide() const
{
    return !(d_taille);
}


void RdvLCH::ajout_vide(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes)
{
    //inserer vide
    RdvCH*rdv=new RdvCH{nom,date_deb,date_fin,personnes};
    d_tete=rdv;
    d_fin=rdv;
}
void RdvLCH::ajout_entete(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes)
{
    RdvCH*rdv=new RdvCH{nom,date_deb,date_fin,personnes};
    rdv->d_suiv=d_tete;
    d_tete->d_prec=rdv;
    d_tete=rdv;
}
void RdvLCH::ajout_milieu(RdvCH*& crt,const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes)
{
    //inserer milieu
    RdvCH*rdv=new RdvCH{nom,date_deb,date_fin,personnes};
    //crt est l'element qui suit le nouveau elem
    crt->d_prec->d_suiv=rdv;
    rdv->d_suiv=crt;
    rdv->d_prec=crt->d_prec;
    crt->d_prec=rdv;
}
void RdvLCH::ajout_fin(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes)
{
    //inserer fin
    RdvCH*rdv=new RdvCH{nom,date_deb,date_fin,personnes};
    d_fin->d_suiv=rdv;
    rdv->d_prec=d_fin;
    d_fin=rdv;
}

void RdvLCH::ajouter(const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes)
{
    std::string nom_modif{nom};
    en_maj(nom_modif);
    if(rechercher(nom_modif)>=0)
        return;
    if(vide())
    {
        //inserer vide
        ajout_vide(nom_modif,date_deb,date_fin,personnes);
    }
    else
    {
        RdvCH *crt{d_tete};
        while(crt->d_suiv!=nullptr && crt->d_rdv.nom()<nom_modif)
            crt=crt->d_suiv;
        if(crt==d_tete && crt->d_rdv.nom()>nom_modif)
        {
            //inserer a l'entete
            ajout_entete(nom_modif,date_deb,date_fin,personnes);
        }
        else if(crt==d_fin && crt->d_rdv.nom()<nom_modif)
        {
            //inserer fin
            ajout_fin(nom_modif,date_deb,date_fin,personnes);
        }
        else
        {
            //inserer milieu
            ajout_milieu(crt,nom_modif,date_deb,date_fin,personnes);
        }
    }

    d_taille++;
}


//RdvCHen parametre
void RdvLCH::ajout_vide(RdvCH*& rdv)
{
    //inserer vide
    d_tete=rdv;
    d_fin=rdv;
}
void RdvLCH::ajout_entete(RdvCH*& rdv)
{
    rdv->d_suiv=d_tete;
    d_tete->d_prec=rdv;
    d_tete=rdv;
}
void RdvLCH::ajout_milieu(RdvCH*& crt,RdvCH*& rdv)
{
    //inserer milieu
    //crt est l'element qui suit le nouveau elem
    crt->d_prec->d_suiv=rdv;
    rdv->d_suiv=crt;
    rdv->d_prec=crt->d_prec;
    crt->d_prec=rdv;
}
void RdvLCH::ajout_fin(RdvCH*& rdv)
{
    //inserer fin
    d_fin->d_suiv=rdv;
    rdv->d_prec=d_fin;
    d_fin=rdv;
}



void RdvLCH::ajouter(RdvCH*& rdv)
{
    if(rechercher(rdv->d_rdv.nom())>=0)
        return;
    if(vide())
    {
        //inserer vide
        ajout_vide(rdv);
    }
    else
    {
        RdvCH *crt{d_tete};
        while(crt->d_suiv!=nullptr && crt->d_rdv.nom()<rdv->d_rdv.nom())
            crt=crt->d_suiv;
        if(crt==d_tete && crt->d_rdv.nom()>rdv->d_rdv.nom())
        {
            //inserer a l'entete
            ajout_entete(rdv);
        }
        else if(crt==d_fin && crt->d_rdv.nom()<rdv->d_rdv.nom())
        {
            //inserer fin
            ajout_fin(rdv);
        }
        else
        {
            //inserer milieu
            ajout_milieu(crt,rdv);
        }
    }
    d_taille++;
}


void RdvLCH::supprimer_entete()
{
     //supprimer en tete
    d_tete=d_tete->d_suiv;
}
void RdvLCH::supprimer_milieu(RdvCH*& crt)
{
    //supprimer milieu
    crt->d_prec->d_suiv=crt->d_suiv;
    crt->d_suiv->d_prec=crt->d_prec;
}
void RdvLCH::supprimer_fin()
{
    //supprimer fin
    d_fin=d_fin->d_prec;
}


void RdvLCH::supprimer(const string &nom)
{

    std::string nom_modif{nom};
    en_maj(nom_modif);
    if(vide())
        return;
    RdvCH*crt{d_tete};
    while(crt!=nullptr && crt->d_rdv.nom()!=nom_modif)
        crt=crt->d_suiv;
    if(crt==nullptr)
        return;
    //si la personne n'a acun rdv
    if(crt==d_tete)
    {
        supprimer_entete();
    }
    else if(crt==d_fin)
    {
        supprimer_fin();
    }
    else
    {
        supprimer_milieu(crt);
    }
    delete crt;
    d_taille--;
}
void RdvLCH::modifier(const std::string& nom_p,const std::string& nom,const Date& date_deb,const Date& date_fin,const std::vector<Personne> &personnes)
{
    std::string nom_modif{nom};
    en_maj(nom_modif);
    std::string nomp_modif{nom_p};
    en_maj(nomp_modif);
    if(!vide() && rechercher(nom_modif)<0)
    {
        RdvCH *crt{d_tete};
        while(crt!=nullptr && nomp_modif!=crt->d_rdv.nom())
            crt=crt->d_suiv;
        if(crt==nullptr)
            return;
        else
        {
            crt->d_rdv.set_rdv(nom_modif,date_deb,date_fin,personnes);
            if(nomp_modif!=nom_modif )
            {
                //remettre en ordre
                string n{crt->d_rdv.nom()};
                supprimer(n);
                RdvCH *rdv{new RdvCH{nom_modif,date_deb,date_fin,personnes}};
                ajouter(rdv);
            }
        }
    }
}

void RdvLCH::rdvs_personne(const Personne& pers,std::vector<Rdv>& list_rdvs) const
{
    RdvCH* crt{d_tete};
    list_rdvs.reserve(10);
    while(crt!=nullptr)
    {
        for(unsigned i=0 ; i<crt->d_rdv.d_personnes.size() ; i++)
        {
            if(crt->d_rdv.d_personnes[i].nom()== pers.nom())
            {
                list_rdvs.push_back(crt->d_rdv);
            }

        }
        crt=crt->d_suiv;
    }
}
void RdvLCH::rdvs_personne(const std::string& nom,std::vector<Rdv>& list_rdvs) const
{
    std::string nom_modif{nom};
    en_maj(nom_modif);
    RdvCH* crt{d_tete};
    list_rdvs.reserve(10);
    while(crt!=nullptr)
    {
        for(unsigned i=0 ; i<crt->d_rdv.d_personnes.size() ; i++)
        {
            if(crt->d_rdv.d_personnes[i].nom()== nom_modif)
            {
//                cout<<crt->d_personnes[i].nom()<<"=="<<pers->nom();
                list_rdvs.push_back(crt->d_rdv);
            }

        }
        crt=crt->d_suiv;
    }
}
std::vector<Rdv> RdvLCH::rdvs_personne(const std::string& nom) const
{
    std::vector<Rdv> res={};
    res.reserve(10);
    std::string nom_modif{nom};
    en_maj(nom_modif);
    RdvCH* crt{d_tete};
    while(crt!=nullptr)
    {
        for(unsigned i=0 ; i<crt->d_rdv.d_personnes.size() ; i++)
        {
            if(crt->d_rdv.d_personnes[i].nom()== nom_modif)
            {
//                cout<<crt->d_personnes[i].nom()<<"=="<<pers->nom();
                res.push_back(crt->d_rdv);
            }

        }
        crt=crt->d_suiv;
    }
    return res;
}
std::vector<Rdv> RdvLCH::rdvs_personne(const Personne& personne) const
{
    return rdvs_personne(personne.nom());
}


bool RdvLCH::pers_avoir_rdv(const std::string& nom,const Date& date) const
{
    string nom_modif{nom};
    en_maj(nom_modif);
   std::vector<Rdv> rdvs=rdvs_personne(nom_modif);
    unsigned i=0;
    while(i<rdvs.size() && rdvs[i].date_deb()!=date)
        ++i;
    return !(i==rdvs.size());
}

Rdv& RdvLCH::rdv(int idx) const
{
    RdvCH*crt{d_tete};
    int i{0};
    while(crt!=nullptr && i<idx)
    {
        crt=crt->d_suiv;
        ++i;
    }
    if(crt==nullptr)
        throw std::runtime_error("Il n'existe pas un rdv avec tel indice");
    return crt->d_rdv;

}

Rdv& RdvLCH::rdv(const std::string& nom) const
{
    string nom_modif{nom};
    en_maj(nom_modif);
    RdvCH*crt{d_tete};
    while(crt!=nullptr && crt->d_rdv.nom()!=nom_modif)
    {
        crt=crt->d_suiv;
    }
    if(crt==nullptr)
        throw std::runtime_error("Il n'existe pas un rdv avec tel nom");
    return crt->d_rdv;
}

int RdvLCH::rechercher(const std::string& nom) const
{
    string nom_modif{nom};
    en_maj(nom_modif);
    RdvCH *crt{d_tete};
    int i{0};
    while(crt!=nullptr && crt->d_rdv.nom()!=nom_modif)
    {
        crt=crt->d_suiv;
        ++i;
    }
    if(crt==nullptr)
        return -1;
    return i;
}
vector<Rdv> RdvLCH::rdvsDeDate(const Date& date) const
{
    vector<Rdv> res;
    res.reserve(30);
    RdvCH* crt{d_tete};
    while(crt!=nullptr)
    {
        if( date==crt->d_rdv.date_deb() )
            res.push_back(crt->d_rdv);
        crt=crt->d_suiv;
    }
    return res;
}



void RdvLCH::lire(std::istream& ist)
{
    Rdv rdv{};
    while(ist>>rdv)
    {
        if(ist.good())
        {
            ajouter(rdv.nom(),rdv.date_deb(),rdv.date_fin(),rdv.personnes());
        }
    }
}
void RdvLCH::ecrire(ostream& ost) const
{
    if(vide())
    {
        cout<<"vide";
        return;
    }

    for(RdvCH *crt{d_tete}; crt!=nullptr ;crt=crt->d_suiv)
    {
        crt->d_rdv.ecrire(ost);
        ost<<endl;
    }
}

std::ostream& operator<<(std::ostream& ost,const RdvLCH& r)
{
    r.ecrire(ost);
    return ost;
}
std::istream& operator>>(std::istream& ist,RdvLCH& r)
{
    r.lire(ist);
    return ist;
}
