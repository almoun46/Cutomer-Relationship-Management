#ifndef GESTIONINTERACTION_H
#define GESTIONINTERACTION_H
#include "interaction.h"
#include <list>
#include "date.h"
using namespace std;
class gestionInteraction
{
     /**
* @brief declaration des attributs de la classe*/
private:
     /**
* @brief déclaration de la liste qui contiendra les intéraction d'un contact*/
    list<interaction> listInter;
public:
     /**
* @brief Constructeur par défaut de la classe */
    gestionInteraction();
     /**
* @brief le destructeur de la classe*/
    ~gestionInteraction();
     /**
* @brief cet getteur retrourne la liste des interaction*/
    list<interaction> getListInter()const;
     /**
* @brief elle récupère la liste et change la liste courante à celle passé en paramètre*/
    void setListInter(const list<interaction> &);
     /**
* @brief cette fonction permet l'ajout d'une interaction dansla liste des intération qui a été déclarée*/
    void ajouteInter(interaction &);
     /**
* @brief cette méthode supprime une interaction qui a été passé en paramètre de la liste des interaction*/
    void supprimeInter(interaction &);
     /**
* @brief cette méthode permet la récuperaton de l'indice de l'interaction qui à été passée en paramètre*/
    interaction getInter(const int &);
     /**
* @brief l'affichage de notre liste d'interaction est possible grâce à cette  méthode*/
    void afficheListInter();

};

#endif // GESTIONINTERACTION_H
