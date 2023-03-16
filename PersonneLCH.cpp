#include"PersonneLCH.h"
#include"Personne.h"
#include"string_transforme.h"

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
    return !d_taille;
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

void PersonneLCH::ajouter(string& nom, const string& prenom, const string& tel,const string& email)
{
    en_maj(nom);
    if(pers_existe(nom)>=0)
        return;
    if(vide())
    {
        //inserer vide
        ajout_vide(nom,prenom,tel,email);
    }
    else
    {
        PersonneCH *crt{d_tete};
        while(crt->d_suiv!=nullptr && crt->d_personne.nom()<nom)
            crt=crt->d_suiv;
        if(crt==d_tete && crt->d_personne.nom()>nom)
        {
            //inserer a l'entete
            ajout_entete(nom,prenom,tel,email);
        }
        else if(crt==d_fin && crt->d_personne.nom()<nom)
        {
            //inserer fin
            ajout_fin(nom,prenom,tel,email);
        }
        else
        {
            //inserer milieu
            ajout_milieu(crt,nom,prenom,tel,email);
        }
    }
    d_taille++;
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

void PersonneLCH::supprimer(string &nom)
{
    en_maj(nom);
    if(vide())
        return;
    PersonneCH *crt{d_tete};
    while(crt!=nullptr && crt->d_personne.nom()!=nom)
        crt=crt->d_suiv;
    if(crt==nullptr)
        return;
    if(crt==d_tete)
    {
        //supprimer en tete
//        d_tete=d_tete->d_suiv;
//        delete crt;
//        d_tete->d_prec=nullptr;
//        d_taille--;
        supprimer_entete();

    }
    if(crt==d_fin)
    {
        //supprimer fin
//        d_fin=d_fin->d_prec;
//        delete crt;
//        d_fin->d_suiv=nullptr;
//        d_taille--;
        supprimer_fin();
    }
    supprimer_milieu(crt);
    delete crt;
    d_taille--;
//    else
//    {
        //supprimer milieu
//        crt->d_prec->d_suiv=crt->d_suiv;
//        crt->d_suiv->d_prec=crt->d_prec;
//        delete crt;
//        d_taille--;

//    }
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
int PersonneLCH::pers_existe(std::string& nom) const
{
    en_maj(nom);
    PersonneCH *crt{d_tete};
    int i{0};
    while(crt!=nullptr && crt->d_personne.nom()!=nom)
    {
        ++i;
        crt=crt->d_suiv;
    }
    if(crt==nullptr)
        return -1;
    return i;
}
Personne& PersonneLCH::get_personne(std::string& nom)const
{
    en_maj(nom);
    PersonneCH *crt{d_tete};
    while(crt!=nullptr && nom!=crt->d_personne.nom())
        crt=crt->d_suiv;
    if(crt!=nullptr)
        return crt->d_personne;
}

//il manque remettreenordre()
void PersonneLCH::modifier(string& nom_p,string& nom,const string& prenom, const string& tel,const string& email)
{
    en_maj(nom);
    en_maj(nom_p);
    if(!vide() && !recherche(nom))
    {
        PersonneCH *crt{d_tete};
        while(crt!=nullptr && nom_p!=crt->d_personne.nom())
            crt=crt->d_suiv;
        if(crt==nullptr)
            return;
        else
        {
//            set_pers(crt,nom,prenom,tel,email);
            crt->d_personne.set_pers(nom,prenom,tel,email);
            if(nom_p!=nom)
            {
                //remettre en ordre
                string n{crt->d_personne.nom()};
                supprimer(n);
                PersonneCH *pers{new PersonneCH{nom,prenom,tel,email}};
                ajouter(pers);
            }
        }
    }
}
bool PersonneLCH::recherche(string& nom) const
{
    en_maj(nom);
    if(vide())
        return false;
    PersonneCH *crt{d_tete};
    while(crt!=nullptr && nom!=crt->d_personne.nom())
        crt=crt->d_suiv;
    return crt;
}


//void PersonneLCH::swapNodes(PersonneCH* node1, PersonneCH* node2)
//{
//    // Si les deux nœuds sont les mêmes, il n'y a rien à faire
//    if(node1 == node2) {
//        return;
//    }
//
//    // Vérifiez si l'un des nœuds est la tête de la liste et mettez à jour la tête si nécessaire
//    if(node1 == d_tete) {
//        d_tete = node2;
//    }
//    else if(node2 == d_tete) {
//        d_tete = node1;
//    }
//
//    // Échangez les liens prev et next des deux nœuds
//    PersonneCH* temp = node1->d_prec;
//    node1->d_prec = node2->d_prec;
//    node2->d_prec = temp;
//    temp = node1->d_suiv;
//    node1->d_suiv = node2->d_suiv;
//    node2->d_suiv = temp;
//
//    // Mettez à jour les liens prev et next des nœuds adjacents pour qu'ils pointent vers les nœuds échangés
//    if(node1->d_prec != NULL) {
//        node1->d_prec->d_suiv = node1;
//    }
//    if(node1->d_suiv != NULL) {
//        node1->d_suiv->d_prec = node1;
//    }
//    if(node2->d_prec != NULL) {
//        node2->d_prec->d_suiv = node2;
//    }
//    if(node2->d_suiv != NULL) {
//        node2->d_suiv->d_prec = node2;
//    }
//}

//error
//void PersonneLCH::remettreEnOrdre(PersonneCH*& crt)
//{
//    supprimer(crt->d_personne.nom());
//    PersonneCH *pers{new Personne(crt->d_personne.nom(),crt->d_personne.prenom(),crt->d_personne.tel(),crt->d_personne.email())};
//    ajouter(pers);
//}

void PersonneLCH::lire(istream& ist)
{
    char ch;
    string nom,prenom,tel,email;
    //remplacer eof par getline(ist,line(string))
    while(!ist.eof())
    {
        ist>>nom>>ch>>prenom>>ch>>tel>>email;
        if(ist.good())
        {
            PersonneCH *p=new PersonneCH{nom,prenom,tel,email};
            ajouter(p);
        }

    }
}

//void PersonneLCH::lire(istream& ist)
//{
//
//    while(!ist.eof())
//    {
//          //il faut ajouter le constructeur par defaut
//          //et la methode ajouter(PersonneCH*& pers)
//        PersonneCH *pers=new PersonneCH{};
//        pers.lire(ist);
//        ajouter(pers);
//    }
//}

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
istream& operator<<(istream& ist,PersonneLCH& p)
{
    p.lire(ist);
    return ist;
}
