#include "crmga.h"
#include <contact.h>
#include <gestioncontact.h>
#include "sqldataContact.h"
#include "sqldatainteraction.h"
#include "sqldatatodo.h"
#include<iostream>
#include <QApplication>
#include <iostream>
#include<QCoreApplication>
#include<QObject>

int main(int argc, char *argv[])
{
    contact ct;

    auto ymd = year_month_day{ct.getdateContct()};
    string djour = to_string(ymd.day().operator unsigned int());
    string dmonth = to_string(ymd.month().operator unsigned int());
    string dyear = to_string(ymd.year().operator int());
    string date = djour+"-"+dmonth+"-"+dyear;
    //cout<< date;
    //cout<<ct.conversiondateToString(ct.getdateContct());
    //ct.setDateContact(ct.conversion("26-11-2022"));
   //string U= ct.conversiondateToString(ct.getdateContct());
    QApplication a(argc, argv); /*!< Initialisation de a avec les parametres argc et argv */
    CRMGA w;
    sqlDataContact co;
    sqldataInteraction inter;
    sqldataTodo tt;

    //etablissement des connections signaux avec les slots de la base de donnée
    //contact
    QObject::connect(&w,SIGNAL(sigListcontact(std::list<contact> &)),&co,SLOT(slotAfficheListeContact(std::list<contact> &)));
    QObject::connect(&w,SIGNAL(sigAjouter(contact &)),&co,SLOT(slotAjouteContact( contact &)));
    QObject::connect(&w,SIGNAL(sigSupprimer( const int &)),&co,SLOT(slotSupprimeContact(const int &)));
    QObject::connect(&w,SIGNAL(sigModifContact(const int &, contact &)),&co,SLOT(slotModifContact(const int & , contact &)));
    QObject::connect(&w,SIGNAL(sigRechercheContact(QString &,QString &,QString &,std::list<contact> &)),&co,SLOT(slotrecheContact(QString &,QString &,QString &,std::list<contact> &)));
    QObject::connect(&w,SIGNAL(sigRech_contact_par_nom(QString &,std::list<contact>&)),&co,SLOT(slotrechercontact_par_nom(QString &,std::list<contact> &)));
    QObject::connect(&w,SIGNAL(sigRech_contact_par_entreprise(QString &,std::list<contact>&)),&co,SLOT(slotrechercontact_par_entreprise(QString &,std::list<contact> &)));

    //interaction
    QObject::connect(&w,SIGNAL(sigAjoutInteraction(const int &,interaction &)),&inter,SLOT(slotAjouterInteraction(const int &, interaction &)));
    QObject::connect(&w,SIGNAL(sigListeInteraction(const int &,std::list<interaction> &)),&inter,SLOT(slotListeInteractionContact(const int&,std::list<interaction> &)));
    QObject::connect(&w,SIGNAL(sigListeInteractions(std::list<interaction> &)),&inter,SLOT(slotListeInteraction(std::list<interaction> &)));
    QObject::connect(&w,SIGNAL(sigRechercheInteraction(QString &,QString &,std::list<interaction> &)),&inter,SLOT(slotRechercheInteraction(QString &,QString &,std::list<interaction> &)));
    QObject::connect(&w,SIGNAL(sigRechercheInteractionContact(int ,QString & ,QString & ,std::list<interaction> &)),&inter,SLOT(slotRechercheInteractionContact(const int &,QString &,QString &,std::list<interaction> &)));

    //TodosigAjoutTodo(const int &,todo &)
    QObject::connect(&w,SIGNAL(sigAjoutTodo(const int &,todo &)),&tt,SLOT(slotAjouterTodo(const int &, todo&)));
    QObject::connect(&w,SIGNAL(sigListeTodos(list<todo>&)),&tt,SLOT(slotListeTodos(list<todo> &)));
    QObject::connect(&w,SIGNAL(sigRechercheTodoCont(const int &, QString &,QString &, std::list<todo> &)),&tt,SLOT(slotRechercheTodoContact(const int &,QString &,QString &,std::list<todo> &)));
    QObject::connect(&w,SIGNAL(sigRechercheTodos(QString &,QString &,std::list<todo> &)),&tt,SLOT(slotRechercheTodo(QString &,QString &,std::list<todo> &)));


    w.show();
    return a.exec();
}
