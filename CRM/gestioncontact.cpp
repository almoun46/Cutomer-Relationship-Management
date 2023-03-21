#include "gestioncontact.h"
#include<iostream>

GestionContact::GestionContact(){}
GestionContact::~GestionContact(){listContact.clear();}
void GestionContact::ajouterContact(const contact & c)
{
    listContact.push_back(c);
}
//suppression d'un catact par son nom
void GestionContact::supprimercontact(const string & nom)
{
    auto it = listContact.begin();
    bool trouve = false;
    while ((it != listContact.end()) && (trouve ==false)) {
        if( it->getNom() == nom)
        {
            trouve=true;
            it = listContact.erase(it);
        }
        else
            ++it;
    }
}
std::list<contact>GestionContact::getListecontact()const{return listContact;}

void GestionContact::afficheListecontact()
{
    std::cout << "la liste des contacts: " << std::endl;
    for (auto & c : listContact)
         c.affichecontact();
}

