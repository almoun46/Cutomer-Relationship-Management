#include "gestioninteraction.h"
#include "interaction.h"
#include "date.h"
gestionInteraction::gestionInteraction()
{

}
gestionInteraction::~gestionInteraction()
{
    this->getListInter().clear();
}
list<interaction> gestionInteraction::getListInter() const
{
    return listInter;
}
void gestionInteraction::setListInter(const list<interaction> &lst)
{
    listInter=lst;
}
void gestionInteraction::ajouteInter(interaction &inter)
{
    listInter.push_back(inter);
}
void gestionInteraction::supprimeInter(interaction &inter)
{
    auto it = listInter.begin();
    bool trouve = false;
    while ((it != listInter.end()) && (trouve ==false)) {
        if( it->getCommentaire() == inter.getCommentaire())
        {
            trouve=true;
            it = listInter.erase(it);
        }
        else
            ++it;
    }
}
interaction gestionInteraction::getInter(const int &i)
{
    list<interaction>::iterator it = listInter.begin();
    advance(it,i);
    return *it;
}
void gestionInteraction::afficheListInter()
{

    for (int i=0;i<(int)listInter.size();i++ ) {
        getInter(i).afficheInter();

    }
}


