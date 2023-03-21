#include "todo.h"
#include <string>
#include <iostream>

int todo::getId_interation() const
{
    return id_interation;
}

void todo::setId_interation(int value)
{
    id_interation = value;
}

int todo::getIid_todo() const
{
    return iid_todo;
}

void todo::setIid_todo(int value)
{
    iid_todo = value;
}

todo::todo()
{//aucun todo prevu donc pas de date
    this->setcontenu("");

}
todo::todo(const string & c,const unsigned int &d,const unsigned int &m,const unsigned int &y)
{
    this->setcontenu(c);
    setY(y);setM(m);setD(d);
}
string todo::getcontenu()const {return contenu;}
void todo:: setcontenu(const string &c)
{
    contenu=c;
}
string todo::getNomModificateur() const{return NomModificateur;}
void todo::setD(const unsigned int &j){d=j;}
void todo::setM(const unsigned int &M){m=M;}
void todo::setY(const unsigned int &a){y=a;}
unsigned int todo::getD() const{return d;}
unsigned int todo::getM() const{return m;}
unsigned int todo::getY() const{return y;}
////il faut une autre fonction ou ajuster celle-ci pour affecter aux todos ayant pas des dates
////la date courante(celle de la creation de l'interaction)
date::year_month_day todo::getDate()const
{ date::year_month_day ymd;//il faut utilisé un auto
     ymd=year(this->getY())/month(getM())/day(getD());
     return ymd;
}
void todo::setDate(date::year_month_day &d)
{
    this->setD(d.day().operator unsigned int());
    this->setM(d.month().operator unsigned int());
    this->setY((unsigned)d.year().operator int());
}
//change la date d'une action tout en recuperant  le nom du modificateur et la date courante
void todo::changedate(const unsigned int &d,const unsigned int &m,const unsigned int &y,const string&nom)
{
    setY(y);setM(m);setD(d);
    NomModificateur=nom;
    modifTodo=floor<days>(system_clock::now());//lors de l'affichage utilisé le format YMD

}

void todo::changeContenuTodo(const string &c, const string &nomMf)
{
    setcontenu(c);
    NomModificateur=nomMf;
}



date::year_month_day todo::conversionStringToDate(const string &str)
{
    string str1=str.substr(0,2);
    string str2=str.substr(3,2);
    string str3=str.substr(6,4);
    year_month_day date;
    try {
         date=year(std::stoi(str1))/month(std::stoi(str2))/day(std::stoi(str3));

    }
    catch (std::invalid_argument const &e) {
        std::cout << "Bad input: std::invalid_argument thrown" << std::endl;
    }
    catch (std::out_of_range const &e) {
        std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
    }
    return date;
}

date::year_month_day todo::conversionStringToDate2( QString strr)
{
    string str =strr.toStdString();
    string str1=str.substr(0,3);
    string str2=str.substr(5,6);
    string str3=str.substr(8,9);
    year_month_day date;
    try {
         date=year(std::stoi(str1))/month(std::stoi(str2))/day(std::stoi(str3));

    }
    catch (std::invalid_argument const &e) {
        std::cout << "Bad input: std::invalid_argument thrown" << std::endl;
    }
    catch (std::out_of_range const &e) {
        std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
    }
    return date;
}


string todo::conversiondateToString(date::year_month_day ymd)
{
    string djour = to_string(ymd.day().operator unsigned int());
    string dmonth = to_string(ymd.month().operator unsigned int());
    string dyear = to_string(ymd.year().operator int());
    string date = djour+"-"+dmonth+"-"+dyear;
    return date;
}


//il faut une autre fonction qui permet de comparer les dates mais dans la classe Gestiontodo
 std::ostream & operator<<(std::ostream& os ,const todo &t)
{
    os<<"@todo "<<t.getcontenu()+""<<"@date "<<t.getDate()<<endl;
    return os;
}
