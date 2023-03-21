#ifndef SQLDATACONTACT_H
#define SQLDATACONTACT_H

#include <QObject>
#include<QtSql/QSqlDatabase>
#include "contact.h"
#include <QtSql/QSqlQuery>

#include<QDebug>
class sqlDataContact : public QObject
{

    Q_OBJECT
private:
    QSqlDatabase db;/*!< connexion a la base de donnee*/
    bool dbOuvert;/*! < Tester si la base est ouverte ou non*/
    /*!
     *\brief Fermeture de la base
     *Methode qui ferme la base quand elle est ouverte
     */
    bool connexionDb();
    void closeDb();
    void isDbopen(bool &);
public:
    explicit sqlDataContact(QObject *parent = nullptr);
    ~sqlDataContact();
    day_contact conversion(const string &);
    void afficheListecontact(std::list<contact> &);
    bool ajouteContact( contact &)const;
    bool modifierContact(const int &, contact &)const;
    bool supprimeContact(const int &)const;
    void rechercheContact(QString &,QString &,QString &,std::list<contact> &);
    void rechercontact_par_nom(QString &,std::list<contact> &);
    void rechercontact_par_entreprise(QString &,std::list<contact> &);
signals:

public slots:
    void slotAfficheListeContact(std::list<contact> &);
    void slotAjouteContact( contact &);
    void slotModifContact(const int &, contact &);
    void slotSupprimeContact(const int &);
    void slotrecheContact(QString &,QString &,QString &,std::list<contact> &);
    void slotrechercontact_par_nom(QString &,std::list<contact> &);
    void slotrechercontact_par_entreprise(QString &,std::list<contact> &);
};

#endif // SQLDATA_H
