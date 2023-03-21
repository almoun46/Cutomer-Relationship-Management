//Cette classse permet de gerer l'ensemble  des todos avec leurs eventuels modification
//les noms des persoones qui modifie ou supprime un todo et la date
#include "gestiontodo.h"
#include<iostream>

gestiontodo::gestiontodo(){}
gestiontodo::~gestiontodo(){listTodo.clear();}

void gestiontodo::ajoutTodo(todo &t)
{
   // listTodo.sort();
    listTodo.push_back(t);


}
list<todo> gestiontodo::getListTodo(){return listTodo;}
//supprime le todo en comparant les dates
//j'utilise la première occurance par ce que à une date il ya qu'une et seule interaction
void gestiontodo::supprimeTodo(todo &t)
{
    auto it = listTodo.begin();
    bool trouve = false;
    while ((it != listTodo.end()) && (trouve ==false)) {
        if( it->getDate() == t.getDate())
        {
            trouve=true;
            it = listTodo.erase(it);
        }
        else
            ++it;
    }
}
todo gestiontodo::recuperetodo(const date::year_month_day &date)
{
    auto it = listTodo.begin();
    bool trouve = false;
    while ((it != listTodo.end()) && (trouve ==false)) {
        if( it->getDate() == date)
        {
            trouve=true;

        }
        else
            ++it;
    }
    return *it;
}
//affichage de chaque todo
void gestiontodo::afficheListTodo()
{
   auto it=listTodo.begin();
    for (int i=0;i<(int)listTodo.size();i++) {
        advance(it,i);
        cout<<*it<<endl;
    }
    /*for (auto & c : this->getListTodo())
          cout<<c<<endl;*/
}
/*void gestiontodo::tripardate()
{
    this->getListTodo().sort();
}*/
