#include"PersonneLCH.h"
#include"Personne.h"
#include"string_transforme.h"
#include"Rdv.h"

#include<iostream>
#include<string>
using namespace std;
using namespace string_transforme;

PersonneCH::PersonneCH(const Personne& personne): d_personne{personne} , d_suiv{nullptr} , d_prec{nullptr}
{}

PersonneCH::PersonneCH(const string& nom, const string& prenom, const string& tel, const string& email):
d_personne{nom,prenom,tel,email} , d_suiv{nullptr} , d_prec{nullptr}
{}




PersonneLCH::PersonneLCH() : d_tete{nullptr} , d_fin{nullptr} , d_taille{0}
{}

PersonneLCH::PersonneLCH(const PersonneLCH& list_personne) : d_tete{nullptr} , d_fin{nullptr} , d_taille{list_personne.taille()}
{
    PersonneCH *crt{list_personne.d_tete};
    while(crt!=nullptr)
    {
        PersonneCH *pers=new PersonneCH{crt->d_personne.nom(),crt->d_personne.prenom(),crt->d_personne.tel(),crt->d_personne.email()};
        if(d_tete==nullptr)
            ajout_vide(pers);
        else
            ajout_fin(pers);
        crt=crt->d_suiv;
    }
}

int PersonneLCH::taille() const
{
    return d_taille;
}

bool PersonneLCH::vide() const
{
    return d_tete==nullptr;
}

void PersonneLCH::ajout_vide(const string& nom, const string& prenom, const string& tel,const string& email)
{
    //inserer vide
    PersonneCH *pers=new PersonneCH{nom,prenom,tel,email};
    d_tete=pers;
    d_fin=pers;
}
void PersonneLCH::ajout_entete(const string& nom, const string& prenom, const string& tel,const string& email)
{
    PersonneCH *pers=new PersonneCH{nom,prenom,tel,email};
    pers->d_suiv=d_tete;
    d_tete->d_prec=pers;
    d_tete=pers;
}
void PersonneLCH::ajout_milieu(PersonneCH*& crt,const string& nom, const string& prenom, const string& tel,const string& email)
{
    //inserer milieu
    PersonneCH *pers=new PersonneCH{nom,prenom,tel,email};
    //crt est l'element qui suit le nouveau elem
    crt->d_prec->d_suiv=pers;
    pers->d_suiv=crt;
    pers->d_prec=crt->d_prec;
    crt->d_prec=pers;
}
void PersonneLCH::ajout_fin(const string& nom, const string& prenom, const string& tel,const string& email)
{
    //inserer fin
    PersonneCH *pers=new PersonneCH{nom,prenom,tel,email};
    d_fin->d_suiv=pers;
    pers->d_prec=d_fin;
    d_fin=pers;
}

bool PersonneLCH::ajouter(const string& nom, const string& prenom, const string& tel,const string& email)
{
    string nom_modif{nom};
    en_maj(nom_modif);
    if(pers_existe(nom_modif)>=0)
        return false;
    if(vide())
    {
        //inserer vide
        ajout_vide(nom_modif,prenom,tel,email);
        ++d_taille;
        return true;
    }
    else
    {
        PersonneCH *crt{d_tete};
        while(crt->d_suiv!=nullptr && crt->d_personne.nom()<nom_modif)
            crt=crt->d_suiv;
        if(crt==d_tete && crt->d_personne.nom()>nom_modif)
        {
            //inserer a l'entete
            ajout_entete(nom_modif,prenom,tel,email);
        }
        else if(crt==d_fin && crt->d_personne.nom()<nom_modif)
        {
            //inserer fin
            ajout_fin(nom_modif,prenom,tel,email);
        }
        else
        {
            //inserer milieu
            ajout_milieu(crt,nom_modif,prenom,tel,email);
        }
    }
    d_taille++;
    return true;
}


void PersonneLCH::ajout_vide(PersonneCH*& pers)
{
    //inserer vide
    d_tete=pers;
    d_fin=pers;
}
void PersonneLCH::ajout_entete(PersonneCH*& pers)
{
    pers->d_suiv=d_tete;
    d_tete->d_prec=pers;
    d_tete=pers;
}
void PersonneLCH::ajout_milieu(PersonneCH*& crt,PersonneCH*& pers)
{
    //inserer milieu
    //crt est l'element qui suit le nouveau elem
    crt->d_prec->d_suiv=pers;
    pers->d_suiv=crt;
    pers->d_prec=crt->d_prec;
    crt->d_prec=pers;
}
void PersonneLCH::ajout_fin(PersonneCH*& pers)
{
    //inserer fin
    d_fin->d_suiv=pers;
    pers->d_prec=d_fin;
    d_fin=pers;
}

void PersonneLCH::ajouter(PersonneCH*& pers)
{
    //si le nom de la nouvelle pers existe deja dans la liste
    //ne pas ajouter cette pers
    if(pers_existe(pers)>=0)
        return;
    if(vide())
    {
        //inserer vide
        ajout_vide(pers);
    }
    else
    {
        PersonneCH *crt{d_tete};
        while(crt->d_suiv!=nullptr && crt->d_personne.nom()<pers->d_personne.nom())
            crt=crt->d_suiv;
        if(crt==d_tete && crt->d_personne.nom()>pers->d_personne.nom())
        {
            //inserer a l'entete
            ajout_entete(pers);
        }
        else if(crt==d_fin && crt->d_personne.nom()<pers->d_personne.nom())
        {
            //inserer fin
            ajout_fin(pers);
        }
        else
        {
            //inserer milieu
            ajout_milieu(crt,pers);
        }
    }
    d_taille++;
}

void PersonneLCH::supprimer_entete()
{
     //supprimer en tete
    d_tete=d_tete->d_suiv;
}
void PersonneLCH::supprimer_milieu(PersonneCH*& crt)
{
    //supprimer milieu
    if(crt->d_prec!=nullptr)
        crt->d_prec->d_suiv=crt->d_suiv;
    if(crt->d_suiv!=nullptr)
        crt->d_suiv->d_prec=crt->d_prec;
}
void PersonneLCH::supprimer_fin()
{
    //supprimer fin
    d_fin=d_fin->d_suiv;
}

bool PersonneLCH::supprimer(const string &nom)
{
    string nom_modif{nom};
    en_maj(nom_modif);
    if(vide())
        return false;
    PersonneCH *crt{d_tete};
    while(crt!=nullptr && crt->d_personne.nom()!=nom_modif)
        crt=crt->d_suiv;
    if(crt==nullptr)
        return false;
    if(crt==d_tete)
    {
        supprimer_entete();

    }
    if(crt==d_fin)
    {
        supprimer_fin();
    }
    supprimer_milieu(crt);
    delete crt;
    d_taille--;
    return true;
}

bool PersonneLCH::supprimer(const string& nom , const vector<Rdv>& list_rdv)
{
    if(list_rdv.size()==0)
    {
        return supprimer(nom);
    }
    else
        return false;
}


int PersonneLCH::pers_existe(PersonneCH*& pers) const
{
    PersonneCH *crt{d_tete};
    int i{0};
    while(crt!=nullptr && crt->d_personne.nom()!=pers->d_personne.nom())
    {
        ++i;
        crt=crt->d_suiv;
    }
    if(crt==nullptr)
        return -1;
    return i;
}
int PersonneLCH::pers_existe(const std::string& nom) const
{
    string nom_modif{nom};
    en_maj(nom_modif);
    PersonneCH *crt{d_tete};
    int i{0};
    while(crt!=nullptr && crt->d_personne.nom()!=nom_modif)
    {
        ++i;
        crt=crt->d_suiv;
    }
    if(crt==nullptr)
        return -1;
    return i;
}
Personne& PersonneLCH::get_personne(const std::string& nom)const
{
    string nom_modif{nom};
    en_maj(nom_modif);
    PersonneCH *crt{d_tete};
    while(crt!=nullptr && nom_modif!=crt->d_personne.nom())
        crt=crt->d_suiv;
    if(crt==nullptr)
        throw std::runtime_error("Il n'existe pas une personne avec tel nom");
    return crt->d_personne;
}
Personne& PersonneLCH::get_personne(int idx) const
{
    PersonneCH *crt{d_tete};
    int i{0};
    while(crt!=nullptr && i<idx)
    {
        crt=crt->d_suiv;
        ++i;
    }
    if(crt==nullptr)
        throw std::runtime_error("Il n'existe pas une personne avec tel indice");
    return crt->d_personne;
}
Personne PersonneLCH::personne(const std::string& nom)const
{
    string nom_modif{nom};
    en_maj(nom_modif);
    PersonneCH *crt{d_tete};
    while(crt!=nullptr && nom_modif!=crt->d_personne.nom())
        crt=crt->d_suiv;
    if(crt!=nullptr)
        return crt->d_personne;
    else return Personne{};
}
Personne PersonneLCH::personne(int idx) const
{
    PersonneCH *crt{d_tete};
    int i{0};
    while(crt!=nullptr && i<idx)
    {
        crt=crt->d_suiv;
        ++i;
    }
    if(crt!=nullptr)
        return crt->d_personne;
    else return Personne{};
}


bool PersonneLCH::modifier(const string& nom_p,const string& nom,const string& prenom, const string& tel,const string& email)
{
    string nom_modif{nom};
    string nomp_modif{nom_p};
    en_maj(nom_modif);
    en_maj(nomp_modif);
    if(!vide())
    {
        PersonneCH *crt{d_tete};
        while(crt!=nullptr && nomp_modif!=crt->d_personne.nom())
            crt=crt->d_suiv;
        if(crt==nullptr)
            return false;
        else
        {
            //modifier la personne sans contrainte car:
            //le nom reste le meme on change pas la position
            //et on regarde pas si ce nom existe
            if(nomp_modif==nom_modif)
                crt->d_personne.set_pers(nom_modif,prenom,tel,email);
            //il faut gerer les cas
            else
            {
                //le nouveau nom existe
                if(recherche(nom_modif))
                    return false;
                //le nv nom != nomp donc il faut modifier la pos
                else
                {
                    //remettre en ordre
                    supprimer(nom_modif);
                    PersonneCH *pers{new PersonneCH{nom_modif,prenom,tel,email}};
                    ajouter(pers);
                }
            }
            return true;
        }
    }
    return false;
}
bool PersonneLCH::recherche(const string& nom) const
{
    string nom_modif{nom};
    en_maj(nom_modif);
    if(vide())
        return false;
    PersonneCH *crt{d_tete};
    while(crt!=nullptr && nom_modif!=crt->d_personne.nom())
        crt=crt->d_suiv;
    return crt;
}

void PersonneLCH::lire(istream& ist)
{
    Personne pers{};
    //remplacer eof par getline(ist,line(string))
    while(ist>>pers)
    {
        if(ist.good())
        {
            PersonneCH *p=new PersonneCH{pers};
            ajouter(p);
        }
    }
}

void PersonneLCH::ecrire(ostream& ost) const
{
    if(vide())
    {
        cout<<"vide";
        return;
    }
    for(PersonneCH *crt{d_tete}; crt!=nullptr ;crt=crt->d_suiv)
    {
        crt->d_personne.ecrire(ost);
        ost<<endl;
    }
}

ostream& operator<<(ostream& ost,const PersonneLCH& p)
{
    p.ecrire(ost);
    return ost;
}
istream& operator>>(istream& ist,PersonneLCH& p)
{
    p.lire(ist);
    return ist;
}
