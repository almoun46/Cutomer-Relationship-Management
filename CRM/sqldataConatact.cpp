#include "sqldataContact.h"
#include "QObject"
#include "date.h"
#include "chrono_io.h"
sqlDataContact::sqlDataContact(QObject *parent) : QObject(parent)
{
    dbOuvert=false;
    connexionDb();
}
//destruction de la base de donnée avec fermeture
sqlDataContact::~sqlDataContact()
{
    closeDb();
}
//connexion la base de donnée
bool sqlDataContact::connexionDb()
{
    QString chemin = "C:/Users/almou/Desktop/CDAA/CRM1/Bdprojet.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(chemin);

    if(!db.open())
    {
        qDebug()<<"connexion à la base coontact a echoué";
        dbOuvert = false;
    }else {
        qDebug()<<"Connexion à la base  reussi";
        dbOuvert = !dbOuvert;
        QSqlQuery query;
        //création de la table contact si elle n'existe pas
        query.exec("CREATE TABLE IF NOT EXISTS CONTACT"
                   "(id_contact integer primary key AUTOINCREMENT, "
                   "nom TEXT NOT NULL,"
                   "prenom TEXT NOT NULL,"
                   "entreprise TEXT NOT NULL,"
                   "mail TEXT NOT NULL,"
                   "telephone TEXT NOT NULL,"
                   "photo TEXT NOT NULL ,"
                   "datecreation TEXT NOT NULL)");
        if(!query.exec())
        {
            qDebug()<<"Erreur de création de la table CONTACT";
        }else {
            qDebug()<<"Création reussi de la table CONTACT";
        }

    }
    return dbOuvert;
}


//On fait un test  avec le booléan si la base est ouvert on la ferme
void sqlDataContact::closeDb()
{
    if(dbOuvert==true)
        db.close();
}

void sqlDataContact::isDbopen(bool &b)
{
    dbOuvert = b;
}



//affichage de la liste des contacts
void sqlDataContact::afficheListecontact(std::list<contact> &lst)
{
    lst.clear();
    if(dbOuvert == true)
    {
        QSqlQuery query("SELECT* FROM CONTACT");
        if(!query.exec())
        {
            qDebug()<<"Requete impossible";
        }else {
            qDebug()<<"Requete reussi";
            while(query.next())
            {
                    contact con;
                    QString res = query.value(0).toString();
                    con.setIdentifiantC(res.toInt());
                    res = query.value(1).toString();
                    con.setNom(res.toStdString());
                    res = query.value(2).toString();
                    con.setPrenom(res.toStdString());
                    res = query.value(3).toString();
                    con.setNomEntresprise(res.toStdString());
                    res = query.value(4).toString();
                    con.setEmail(res.toStdString());
                   res = query.value(5).toString();
                   con.setTelephone(res.toStdString());
                   res = query.value(6).toString();
                   con.setPhoto(res.toStdString());
                   res = query.value(7).toString();
                   //conversion de la date
                   string  str=res.toStdString();
                  const day_contact da=con.conversion(str);//fin de conversion
                   con.setDateContact(da);
                    lst.push_back(con);
                }
        }
        //faire un qDebug
    }

}
//ajouter un contact dans la base
bool sqlDataContact::ajouteContact( contact &ct)const
{

    if(dbOuvert==true)
    {
        QSqlQuery query("PRAGMA foreign_keys = ON"
                        "select * from CONTACT");
        //préparation de la requete et les champs conçus
        query.prepare("INSERT INTO CONTACT (nom, prenom, entreprise, mail,telephone, photo, datecreation) "
                      "VALUES(:n, :p, :e, :m, :t, :ph, :d)");
        //remplissage des champs
        query.bindValue(":n",QString::fromStdString(ct.getNom()));
        query.bindValue(":p",QString::fromStdString(ct.getPrenom()));
        query.bindValue(":e",QString::fromStdString(ct.getNomEntreprise()));
        query.bindValue(":m",QString::fromStdString(ct.getEmail()));
        query.bindValue(":t",QString::fromStdString(ct.getTelephone()));
        query.bindValue(":ph",QString::fromStdString(ct.getPhoto()));contact c;
        query.bindValue(":d",QString::fromStdString(ct.conversiondateToString(ct.getdateContct())));
        if(!query.exec())
         {
             qDebug()<<"Ajout de contact echoue";
             return false;
         }
         qDebug()<<"AJout de contact   accepté";
         cout<<"ho"+ct.getNom();
    }
    return true;
}

//supprimer un contact
bool sqlDataContact::supprimeContact(const int &ct)const
{
    if(dbOuvert==true)
    {
        QSqlQuery query("PRAGMA forein_keys = ON");
        query.prepare("DELETE FROM CONTACT WHERE id_contact=:n;");
        query.bindValue(":n",QString::number(ct));
        if(!query.exec())
        {
            qDebug()<<"ECHEC DE SUPPRESSION";
            return  false;
        }
        qDebug()<<"REUSSITE DE SUPPRESSION";
    }
    return true;
}
bool sqlDataContact::modifierContact(const int &iid_ancien, contact &ct)const
{
    if(dbOuvert==true)
    {

        QSqlQuery query("PRAGMA forein_keys = ON");
        query.prepare(("UPDATE CONTACT SET nom=:n,prenom=:p,entreprise=:e,mail=:m,telephone=:t,"
                       "photo:ph,datecreation:d WHERE id_contact=:iid"));
        query.bindValue(":",QString::number(iid_ancien));
        query.bindValue(":n",QString::fromStdString(ct.getNom()));
        query.bindValue(":p",QString::fromStdString(ct.getPrenom()));
        query.bindValue(":e",QString::fromStdString(ct.getNomEntreprise()));
        query.bindValue(":m",QString::fromStdString(ct.getEmail()));
        query.bindValue(":t",QString::fromStdString(ct.getTelephone()));
        query.bindValue(":ph",QString::fromStdString(ct.getPhoto()));
        query.bindValue(":d",QString::fromStdString(ct.conversiondateToString(ct.getdateContct())));
        //la date
        if(!query.exec())
         {
             qDebug()<<"Modification   echoue";
             return false;
         }
         qDebug()<<"Modification   effectuée avec succès";
    }
    return  true;
}
//rechercher un contact entre deux dates
void sqlDataContact::rechercheContact(QString &nom1, QString &date1, QString &date2, std::list<contact> &lst)
{
    //conversion des deux date en day_contact
    contact con;
    day_contact d1=con.conversion(date1.toStdString());
    day_contact d2=con.conversion(date2.toStdString());
    if(dbOuvert==true)
    {
        QSqlQuery query;
        query.prepare("SELECT* FROM CONTACT WHERE nom=:n;");//recuperation de la ligne où nom=nom1
        query.bindValue(":n",QString::fromStdString(nom1.toStdString()));
        query.exec();

        if(!query.exec())
        {
            qDebug()<<"Requete echouée";
        }else {
                qDebug()<<"Requete reussie";
                while (query.next()) {
                    QString res = query.value(7).toString();//recupération d'une date
                    //conversion de la date en day_contact
                    contact con;
                    string str=res.toStdString();
                    day_contact date = con.conversion(str);
                    if(d1<date && d2<date)//date1<date && date<date2)//vérification de l'inclusion de la date recupérée entre date1 et date2)
                    {
                        contact con;
                        res = query.value(0).toString();
                        con.setIdentifiantC(res.toInt());
                        res = query.value(1).toString();
                        con.setNom(res.toStdString());
                        res = query.value(2).toString();
                        con.setPrenom(res.toStdString());
                        res = query.value(3).toString();
                        con.setNomEntresprise(res.toStdString());
                        res = query.value(4).toString();
                        con.setEmail(res.toStdString());
                       res = query.value(5).toString();
                       con.setTelephone(res.toStdString());
                       res = query.value(6).toString();
                       con.setPhoto(res.toStdString());
                       res = query.value(7).toString();
                       //ajouter la date
                       con.setDateContact(date);
                       lst.push_back(con);
                    }
                }
              // lst.sort();//trie des contacts
            }
    }
}
void sqlDataContact::rechercontact_par_nom(QString &nom1,std::list<contact> &lst)
{
    if(dbOuvert==true)
    {
        QSqlQuery query;
        query.prepare("SELECT* FROM CONTACT WHERE nom=:n;");//recuperation de la ligne où nom=nom1
        query.bindValue(":n",QString::fromStdString(nom1.toStdString()));
        query.exec();

        if(!query.exec())
        {
            qDebug()<<"Requete echouée";
        }else {
                qDebug()<<"Requete  de cherche avec un  nom de contact reussit";
                QString res;
                while (query.next()) {
                    contact con;
                    res = query.value(0).toString();
                    con.setIdentifiantC(res.toInt());
                    res = query.value(1).toString();
                    con.setNom(res.toStdString());
                    res = query.value(2).toString();
                    con.setPrenom(res.toStdString());
                    res = query.value(3).toString();
                    con.setNomEntresprise(res.toStdString());
                    res = query.value(4).toString();
                    con.setEmail(res.toStdString());
                   res = query.value(5).toString();
                   con.setTelephone(res.toStdString());
                   res = query.value(6).toString();
                   con.setPhoto(res.toStdString());
                   res = query.value(7).toString();
                   //ajouter la date
                   con.setDateContact(con.conversion(res.toStdString()));
                   lst.push_back(con);

                }
           }
     }
}



void sqlDataContact::rechercontact_par_entreprise(QString &nom1,std::list<contact> &lst)
{
    if(dbOuvert==true)
    {
        QSqlQuery query;
        query.prepare("SELECT* FROM CONTACT WHERE entreprise=:n;");
        query.bindValue(":n",QString::fromStdString(nom1.toStdString()));
        query.exec();

        if(!query.exec())
        {
            qDebug()<<"Requete echouée";
        }else {
                qDebug()<<"Requete de cherche avec le nom d'entreprise reussit";
                QString res;
                while (query.next()) {
                    contact con;
                    res = query.value(0).toString();
                    con.setIdentifiantC(res.toInt());
                    res = query.value(1).toString();
                    con.setNom(res.toStdString());
                    res = query.value(2).toString();
                    con.setPrenom(res.toStdString());
                    res = query.value(3).toString();
                    con.setNomEntresprise(res.toStdString());
                    res = query.value(4).toString();
                    con.setEmail(res.toStdString());
                   res = query.value(5).toString();
                   con.setTelephone(res.toStdString());
                   res = query.value(6).toString();
                   con.setPhoto(res.toStdString());
                   res = query.value(7).toString();
                   //ajouter la date
                   con.setDateContact(con.conversion(res.toStdString()));
                   lst.push_back(con);

                }
           }
     }
}



//les slots
void sqlDataContact::slotAfficheListeContact(std::list<contact> &lst)
{
    afficheListecontact(lst);
}
void sqlDataContact::slotAjouteContact(contact &ct)
{
    ajouteContact(ct);
}
void sqlDataContact::slotModifContact(const int & id, contact &co)
{
    modifierContact(id,co);
}

void sqlDataContact::slotSupprimeContact(const int &ct)
{
    supprimeContact(ct);
}
void sqlDataContact::slotrecheContact(QString &nom1,QString &date1,QString &date2,std::list<contact> &lst)
{
    rechercheContact(nom1,date1,date2,lst);
}
void sqlDataContact::slotrechercontact_par_nom(QString &nom1,std::list<contact> &lst)
{
    rechercontact_par_nom(nom1,lst);
}
void sqlDataContact::slotrechercontact_par_entreprise(QString &nom1,std::list<contact> &lst)
{
    rechercontact_par_entreprise(nom1,lst);
}
