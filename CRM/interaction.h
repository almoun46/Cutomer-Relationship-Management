#ifndef INTERACTION_H
#define INTERACTION_H
#include <list>
#include<string>
#include"date.h"
#include"gestiontodo.h"
#include<chrono>
#include "chrono_io.h"
using namespace std;
using namespace date;
using namespace std::chrono;
using day_interaction = std::chrono::time_point<std::chrono::system_clock, days>;
class interaction
{ /**
* @brief création des attributs de la classe*/
private://je prefère une classe qui gère les todos avec les personnes qui changent la date
     /**
* @brief création d'un attributs de type date interaction*/
    day_interaction dateInteraction;
     /**
* @brief  attributs de type string pour le commentaire apporté à une tache*/
    string commentaire;
     /**
* @brief liste de type gesitontodo qui contiendra les taches du contact*/
    gestiontodo listTodo;
    /**
* @brief attributs de liaison avec un contact*/
    int identifiantC;
    /**
* @brief attributs de liaison avec les todos et pour la choérance d'affichage sur L'IHM*/
    int idInteraction;

public:
     /**
* @brief constructeur avec un paramètre  de type gestiontodo*/
    interaction();
     /**
* @brief  deuxième constructeur qui prend deux paramètre le commentaire et la liste des taches du contact*/
    interaction(const string &,const gestiontodo &);
     /**
* @brief destructeur de la classe qui vide la intéraction*/
    ~interaction();
     /**
* @brief elle retourne juste le commentaire d'un contact*/
    string getCommentaire()const;
     /**
* @brief cette méthode retourne la liste des taches*/
    gestiontodo getListTodo()const;

    int getIdentifiantC()const;
    int getIdInteraction()const;
     /**
* @brief permet d'échangé le conténu de la liste a celui de la liste passé en paramètre*/
    void setListTodo(const gestiontodo &);
     /**
* @brief échange le commentaire à celui passée en paramètre*/
    void setCommentaire(const string &);
    //friend std::ostream & operator<<(std::ostream& os ,const interaction &);
     /**
* @brief elle affiche juste les interaction d'un contact*/
    void afficheInter()const;
    void setIdentifiantC(const int &);
    void setIdInteraction(const int &);
    day_interaction getDateInteraction() const;
    void setDateInteraction(const day_interaction &value);
    string conversiondateToStringI( day_interaction d);
     day_interaction conversionStringToDate(const string &);
};

#endif // INTERACTION_H
