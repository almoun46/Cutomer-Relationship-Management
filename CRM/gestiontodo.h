#ifndef GESTIONTODO_H
#define GESTIONTODO_H
#include <list>
#include "todo.h"
using namespace std;

class gestiontodo
{  /** *@brief déclaration des attributs de la classe*/
private:
     /** *@brief déclaration de l'attribut de type todo qui contiendra tous les taches d'un contact*/
    list <todo>listTodo;

public:
     /**
      *  @brief constructeur de la classe*/
    gestiontodo();
     /**
      *  @brief destructeur de la classe qui vide la liste des tâches d'un contact*/
    ~gestiontodo();
     /**
      *  @brief retourne la liste courante*/
    list <todo> getListTodo();
     /**
      *  @brief fonction qui permet l'ajout d'une tâche sur la liste des tâches*/
    void ajoutTodo(todo &);
     /**
      *  @brief fonction qui permet la suppression d'une tâche de la liste des taches*/
    void supprimeTodo(todo & );

 /**
  *  @brief fonction qui permet la récupération  de la date courante*/
    todo recuperetodo(const date::year_month_day &);
     /**
      *  @brief affichage du conténu de notre liste todo*/
    void afficheListTodo();
};

#endif // GESTIONTODO_H
