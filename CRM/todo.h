//je ne sais comment faut-il recuperer la date d'un todo pour
#ifndef TODO_H
#define TODO_H
#include<string>
#include "date.h"
#include "chrono_io.h"
#include <QString>
using namespace std;
using namespace date;
using namespace std::chrono;
using day_todo = std::chrono::time_point<std::chrono::system_clock, days>;

class todo
{
     /**
      *  @brief création des attributs de la classe*/
private:
     /**
      *  @brief déclaration d'attribut qui contient la date courante*/
    day_todo modifTodo;//uniquemment pour le teste
    //Je devrais juste utilsé un attribut de type YMD
     /**
      *  @brief déclaration des date qui contient le jour , mois, et l'année*/
    unsigned int y,m,d;
    //date::year_month_day ymd;
     /**
      *  @brief conténu de la date d'interaction*/
    string contenu;
     /**
      *  @brief le nom du modificateur de la date*/
    string NomModificateur;
     /**
      *  @brief date de modification*/
    date::year_month_day datemodif;
    /**
     *  @brief l'id de linteraction*/
   int id_interation;
   /**
    *  @brief l'id du todo*/
  int iid_todo;
public:
     /**
      *  @brief constructeur par défaut de la classe*/
    todo();
     /**
      *  @brief constructeur avec parametre de la classe*/
    todo(const string &,const unsigned int &,const unsigned int &,const unsigned int &);
     /**
      *  @brief elle retourne le conténu d'un message*/
    string getcontenu()const;
     /**
      *  @brief elle échange le conténu d'un message*/
    void setcontenu(const string &);
     /**
      *  @brief elle permet de changé le conténu des jour , mois, et année d'un contact  à celui passé en parametre*/
    void setY(const unsigned int& );
    void setM(const unsigned int& );
    void setD(const unsigned int& );
     /**
      *  @brief elle permet juste de retournée la date courante*/
    unsigned int getY()const;
    unsigned int getM()const;
    unsigned int getD()const;
     /**
      *  @brief elle retourne le nom du modificateur de la date*/
    string getNomModificateur()const;
     /**
      *  @brief elle retourne la date de modification*/
    date::year_month_day getDatemodif()const;
     /**
      *  @brief retourne la date courante*/
    date::year_month_day getDate()const;
    void setDate(date::year_month_day &);
     /**
      *  @brief une fonction friend qui permet l'accès au  attribut de la classe sans l'appel des getter*/
    friend std::ostream & operator<<(std::ostream& os ,const todo &t);
    //ceux deux fonction a pour but de pouvoir changé le contenu ou la date mais en recuperant la date de modification
    //et le nom du nodificateur
    //ceux des fonctions seront utilisé pour la base de donnée
     /**
      *  @brief  cette méthode permet de changé le conténu d'un todo du prémier paramètre au seconde*/
    void changeContenuTodo(const string &,const string &);
     /**
      *  @brief modification de la date des taches d'un contact*/
    void changedate (const unsigned int &,const unsigned int &,const unsigned int &,const string &) ;
    int getId_interation() const;
    void setId_interation(int value);
    int getIid_todo() const;
    void setIid_todo(int value);
    date::year_month_day conversionStringToDate(const string &);
    date::year_month_day conversionStringToDate2( QString a);
    string conversiondateToString(date::year_month_day y);
};

#endif // TODO_H
