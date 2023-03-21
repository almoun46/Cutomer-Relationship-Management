#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>
#include <string>
#include <interaction.h>
#include <list>
#include "date.h"
#include "chrono_io.h"
#include<chrono>
#include <vector>
using namespace std;
using namespace date;
using namespace std::chrono;
using day_contact = std::chrono::time_point<std::chrono::system_clock, days>;
class contact
{
 private:
     /**
     * @brief declaration des attributs de la classe
*/
    string nom,email,nomEntreprise,prenom,photo;
   string telephone;
   day_contact dateContact;
   int identifiantC;//pour faire la liaison dans la base de donnée avec les interactions




public:
   /**
   * @brief le constructeur de la classe qui prend les parametre
*/
    contact(const string &,const string &,const string &,const string &,const string&,const string &);
   //constructeur sans paramètre
   contact();
    /**
    * @brief  Destructeur de la classe qui vide la liste des interaction d'un contact
*/
    ~contact();
    /**
    * @brief  déclaration des accésseur de la classe
*/
   string getNom() const;
   string getPrenom()const;
   string getEmail()const;
   string getNomEntreprise()const;
   string getPhoto()const;
   day_contact getdateContct()const;
   int getIdentifiantC()const;

   string getTelephone()const;
   /**
   * @brief  déclaration des setteur de la classe
*/
   void setNom(const string &);
   void setPrenom(const string &);
   void setEmail(const string &);
   void setNomEntresprise(const string &);
   void setTelephone(const string &);
   void setPhoto(const string &);
   void setDateContact(const day_contact &);
   void setIdentifiantC(const int &);
   //convertion de day_contact à string
    string conversiondateToString(const day_contact d);
   /**
   * @brief  les fonction d'affichage  des information du contact
*/
   void affichecontact();//pas de paramètre
   /**
   * @brief  l'affichage du numéro de téléphone stocker dans la liste de type vector
*/
   void VectorAffichage();

  day_contact conversion(const string &);

};

#endif // CONTACT_H
