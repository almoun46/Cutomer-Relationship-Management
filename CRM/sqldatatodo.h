#ifndef SQLDATATODO_H
#define SQLDATATODO_H

#include <QObject>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>

#include<QtDebug>
#include "todo.h"
class sqldataTodo : public QObject
{
    Q_OBJECT


private:
    QSqlDatabase db;/*!< connexion a la base de donnee*/
    bool dbOuvert;/*! < Tester si la base est ouverte ou non*/
    /*!
     *\brief Fermeture de la base
     *Methode qui ferme la base quand elle est ouverte home1/aa800033/Téléchargements/CRM1
     */
    bool connexionDb();
    void closeDb();
    void isDbopen(bool &);
    //permet d'ajouter un todo pour un contact
    bool AjouterTodo(const int&, todo &)const;
    //affiche la liste des todoo d'un contact qu'on choisi
    void listeTodoContact(const int&,std::list<todo> &)const;
public:
public:
    explicit sqldataTodo(QObject *parent = nullptr);
    //permet d'afficher toutes les todo présentes dans la base de donnée
    ~sqldataTodo();
    void ListeTodo(std::list<todo> &);
    //recherche et enregistre dans une liste toutes les todo entre deux dates
    void rechercheTodo(QString &,QString &,std::list<todo> &);
    //recherche et enregistre dans une liste toutes les todo d'un contact entre deux dates
    void rechercheTodocontact(const int &,QString &,QString &,std::list<todo> &);
signals:

public slots:
    void slotAjouterTodo(const int &, todo&);
    void slotListeTodos(list<todo> &);
    void slotListeTodoContact(const int&,std::list<todo> &);
    void slotRechercheTodo(QString &,QString &,std::list<todo> &);
    void slotRechercheTodoContact(const int &,QString &,QString &,std::list<todo> &);
    //il faut pour la modification egalement
};

#endif // SQLDATATODO_H
