#include "interaction.h"
#include <iostream>
using namespace std;
//lorsque le client  n'a pas prevu d'interaction sur son emploi du temps
day_interaction interaction::getDateInteraction() const
{
    return dateInteraction;
}

void interaction::setDateInteraction(const day_interaction &value)
{
    dateInteraction = value;
}

interaction::interaction()
{
    this->setCommentaire(" ");
    dateInteraction=floor<days>(system_clock::now());

}
interaction::interaction(const string & com,const gestiontodo & td)
{
    this->setCommentaire(com);
    dateInteraction=floor<days>(system_clock::now());
    this->setListTodo(td);
}
interaction::~interaction(){
    listTodo.getListTodo().clear();
}
void interaction::setCommentaire(const string &c)
{
    commentaire=c;
}
void interaction::setIdentifiantC(const int &id){identifiantC=id;}
void interaction::setIdInteraction(const int &id){idInteraction=id;}

int interaction::getIdentifiantC() const{return identifiantC;}
int interaction::getIdInteraction() const{return idInteraction;}
string interaction::getCommentaire() const{return commentaire;}
gestiontodo interaction::getListTodo() const
{
    return listTodo;
}
void interaction::setListTodo(const gestiontodo &lst)
{
    listTodo=lst;
}
//affiche le contenu de l'interaction ,sa date courante et la  liste des  todos associée;
void interaction::afficheInter()const
{
    auto ymd = year_month_day{this->dateInteraction};
   cout<<"Contenu : "<<this->getCommentaire() +"\n "<< "date d'interaction "<<ymd.year() << ymd.month() << ymd.day() << std::endl;
    this->getListTodo().afficheListTodo();
}

day_interaction interaction::conversionStringToDate(const string &str)
{

//conversion de la date
    string str1=str.substr(0,2);
    string str2=str.substr(3,2);
    string str3=str.substr(6,4);
    day_interaction date;
    try {

        auto d=year(std::stoi(str1))/month(std::stoi(str2))/day(std::stoi(str3));
        date = day_interaction{d};
    }
    catch (std::invalid_argument const &e) {
        std::cout << "Bad input: std::invalid_argument thrown" << std::endl;
    }
    catch (std::out_of_range const &e) {
        std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
    }
    return date;
}

string interaction::conversiondateToStringI( day_interaction d)
{
    auto ymd = year_month_day{d};
    string djour = to_string(ymd.day().operator unsigned int());
    string dmonth = to_string(ymd.month().operator unsigned int());
    string dyear = to_string(ymd.year().operator int());
    string date = djour+"-"+dmonth+"-"+dyear;
    return date;
}
