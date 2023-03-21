
#include "contact.h"
#include<iostream>
#include <vector>
#include <QObject>
contact::contact(const string & nom,const string & prenom,const string & email,const string & nomEntreprise,const string&telephone,const string &ph)
{
   this->setNom(nom);
   this->setPrenom(prenom);
   this->setEmail(email);
   this->setNomEntresprise(nomEntreprise);
   this->setTelephone(telephone);
   this->setPhoto(ph);
   dateContact=floor<days>(system_clock::now());
}
contact::contact()
{
    this->setNom("");
    this->setPrenom("");
    this->setEmail("");
    this->setNomEntresprise("");
    this->setTelephone("");
    this->setPhoto("");
    dateContact=floor<days>(system_clock::now());
}
contact::~contact(){

}
string contact::getNom() const{return nom;}
string contact::getPrenom() const{return prenom;}
string contact::getEmail() const{return email;}
string contact::getNomEntreprise() const{return nomEntreprise;}
string contact::getTelephone()const {return  telephone ;}
string contact::getPhoto() const{return photo;}
day_contact contact::getdateContct()const{return  dateContact;}
int contact::getIdentifiantC() const{return identifiantC;}

void contact::setNom(const string &n){nom=n;}
void  contact::setPrenom(const  string & p){prenom=p;}
void contact::setEmail(const string &e){email=e;}
void contact::setNomEntresprise(const string &NE){nomEntreprise =NE;}
void contact::setTelephone(const string &telephone){this->telephone=telephone;}
void contact::setPhoto(const string & ph){photo=ph;}
void contact::setIdentifiantC(const int &id){this->identifiantC =id;}
void contact::setDateContact(const day_contact &date)
{
    dateContact = date;
}
day_contact contact::conversion(const string &str)
{

//conversion de la date

    string str1=str.substr(0,2);
    string str2=str.substr(3,2);
    string str3=str.substr(6,4);
    day_contact date;
    try {

        auto d=year((unsigned)std::stoi(str1))/month((unsigned)std::stoi(str2))/day((unsigned)std::stoi(str3));
        date = day_contact{d};
    }
    catch (std::invalid_argument const &e) {
        std::cout << "Bad input: std::invalid_argument thrown" << std::endl;
    }
    catch (std::out_of_range const &e) {
        std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
    }
    return date;
}
string contact::conversiondateToString(const day_contact d)
{
    auto ymd = year_month_day{d};
    string djour = to_string(ymd.day().operator unsigned int());
    string dmonth = to_string(ymd.month().operator unsigned int());
    string dyear = to_string(ymd.year().operator int());
    string date = djour+"-"+dmonth+"-"+dyear;
    return date;
}
//affichage du contact avec ses details

/*void contact:: VectorAffichage(){
    for (int i = 0; i <(int) telephone.size(); i++)
         cout << telephone[i] << " ";
}

void contact::affichecontact()
{
    auto ymd = year_month_day{this->dateContact};
    std::cout << "Nom :" << this->getNom() << "Prenom : " << this->getPrenom() +"\n"
              << "Email :"<<this->getEmail()+"\n"<<"Nom d'entreprise :"<<this->getNomEntreprise()+"\n";
              this->VectorAffichage();
   cout<< "date d'interaction "<<ymd.year() << ymd.month() << ymd.day() << std::endl;
    this->getInteractionsContact().afficheListInter();
}*/



