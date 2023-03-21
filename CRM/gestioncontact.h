#ifndef GESTIONCONTACT_H
#define GESTIONCONTACT_H
#include "contact.h"
#include <list>

class GestionContact
{
private:
    /**
     *  @brief création d'un attribut de type contact qui stockera tous les contact*/
    std::list<contact>listContact;
public:
    /**
     *  @brief constructeur de la classe qui est par défaut*/
    GestionContact();
    /**
     *  @brief destructeur de la classe*/
    ~GestionContact();
    /**
     *  @brief définition de la méthode qui ajoute un contact dans la liste*/
    void ajouterContact(const contact &);
     /**
      *  @brief définition de la méthode d'une méthode qui permet de supprimée un contacte de la liste des contact*/
    void supprimercontact(const string &);
     /**
      *  @brief definition de la méthode getSize() qui retourne la taille de notre liste*/
    inline unsigned getSize() {return listContact.size();};
     /**
      *  @brief cette methode retourne la liste des contact*/
    std::list<contact> getListecontact() const;
     /**
      *  @brief Une méthode qui permet d'afficher la liste des contact ayant été entregistré */
    void afficheListecontact();


};

#endif // GESTIONCONTACT_H
