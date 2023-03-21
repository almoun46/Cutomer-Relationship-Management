#ifndef SQLDATAINTERACTION_H
#define SQLDATAINTERACTION_H

#include <QObject>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtDebug>
#include "interaction.h"
class sqldataInteraction : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase db;/*!< connexion a la base de donnee*/
    bool dbOuvert;/*! < Tester si la base est ouverte ou non*/
    /*!
     *\brief Fermeture de la base
     *Methode qui ferme la base quand elle est ouvertehome1/aa800033/Téléchargements/CRM1
     */
    bool connexionDb();
    void closeDb();
    void isDbopen(bool &);
    //permet d'ajouter une interaction pour un contact
    bool AjouterInteraction(const int&, interaction &)const;
    //affiche la liste des interaction d'un contact qu'on choisi
    void listeInteractionContact(const int&,std::list<interaction> &)const;
public:
    explicit sqldataInteraction(QObject *parent = nullptr);
    //permet d'afficher toutes les interactions présentes dans la base de donnée
    ~sqldataInteraction();
    void ListeInteraction(std::list<interaction> &);
    //recherche et enregistre dans une liste toutes les interactions entre deux dates
    void rechercheInteract(QString &,QString &,std::list<interaction> &);
    //recherche et enregistre dans une liste toutes les interactions d'un contact entre deux dates
    void rechercheInteractioncontact(const int &,QString &,QString &,std::list<interaction> &);
signals:

public slots:
    void slotAjouterInteraction(const int &, interaction &);
    void slotListeInteractionContact(const int&,std::list<interaction> &);
    void slotListeInteraction(std::list<interaction> &);
    void slotRechercheInteraction(QString &,QString &,std::list<interaction> &);
    void slotRechercheInteractionContact(const int &,QString &,QString &,std::list<interaction> &);
};

#endif // SQLDATAINTERACTION_H
