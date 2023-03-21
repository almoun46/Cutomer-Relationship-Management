#include "sqldatainteraction.h"

sqldataInteraction::sqldataInteraction(QObject *parent) : QObject(parent)
{
    dbOuvert = false;
    connexionDb();
}
sqldataInteraction::~sqldataInteraction()
{
    closeDb();
}

bool sqldataInteraction::connexionDb()
{
      db = QSqlDatabase::addDatabase("QSQLITE");
      QString chemin ="C:/Users/almou/Desktop/CDAA/CRM1/Bdprojet.sqlite";
      db.setDatabaseName(chemin);
      if(!db.open()){
          qDebug()<<"connexion à la base a echoué";
          dbOuvert = false;
      }else {
          qDebug()<<"Connexion à la base  reussi";
          dbOuvert = !dbOuvert;
          QSqlQuery query;
          //création de la table interaction si elle n'existe pas
          query.exec("CREATE TABLE IF NOT EXISTS INTERACTION"
                     "(id_interaction integer primary key AUTOINCREMENT,"
                     "id_contact integer NOT NULL,"
                     "contenu TEXT,"
                     "dateInteraction TEXT,"
                     "FOREIGN KEY (id_contact) REFERENCES CONTACT(id_contact) ON DELETE CASCADE) ");
          if(!query.exec())
          {
              qDebug()<<"Echec de création de la table Interaction";
          }else {
              qDebug()<<"Création de la table Interaction reussit";
          }
      }
      return  dbOuvert;
}


//fermeture dela base de donnée
void sqldataInteraction::closeDb()
{
    if(dbOuvert==true)
        db.close();
}

void sqldataInteraction::isDbopen(bool &b)
{
    dbOuvert = b;
}

bool sqldataInteraction::AjouterInteraction(const int  &id, interaction &inter) const
{
    if(dbOuvert)
    {   //activation des clés externes sur la table
        QSqlQuery query("PRAGMA foreign_keys = ON"
                        "select * from INTERACTION");
        //preparation de la requete
                query.prepare("INSERT INTO INTERACTION(id_contact,contenu,dateInteraction)"
                        "VALUES(:co,:c,:d)");
        query.bindValue(":co",QString::number(id));
        query.bindValue(":c",QString::fromStdString(inter.getCommentaire()));
        query.bindValue(":d",QString::fromStdString(inter.conversiondateToStringI(inter.getDateInteraction())));
        if(!query.exec())
        {
            qDebug()<<"Insertion d'interaction echouée";
            return false;
        }
        qDebug()<<"Insertion dans la table INTERACTION reussi";
    }
    return true;
}

void sqldataInteraction::listeInteractionContact(const int  &id, std::list<interaction> &lstInter) const
{

    lstInter.clear();//par precaution
    if(dbOuvert)
    {
        QSqlQuery query("SELECT * FROM INTERACTION WHERE id_contact =:idc");
        query.bindValue(":idc",QString::number(id));
        query.exec();
        if(!query.exec())
        {
            qDebug()<<"Affichage des interactions de ce contact a été echoué";
        }else {
            qDebug()<<"Affichage reussit";
            while(query.next())
            {
                interaction inter;
                QString res = query.value(0).toString();
                inter.setIdInteraction(res.toInt());
                res=query.value(1).toString();
                inter.setIdentifiantC(res.toInt());
                res=query.value(2).toString();
                inter.setCommentaire(res.toStdString());
                res = query.value(3).toString();
                inter.setDateInteraction(inter.conversionStringToDate(res.toStdString()));
                lstInter.push_back(inter);
            }
            //lstInter.sort();
        }

    }
}

void sqldataInteraction::ListeInteraction(std::list<interaction> &lstInter)

{
    lstInter.clear();
    if(dbOuvert)
    {
        QSqlQuery query("SELECT * FROM INTERACTION ");

        if(!query.exec())
        {
            qDebug()<<"Affichage des interactions  a été echoué";
        }else {
            qDebug()<<"Affichage reussit";
            while(query.next())
            {
                interaction inter;
                QString res = query.value(0).toString();
                inter.setIdInteraction(res.toInt());
                res=query.value(1).toString();
                inter.setIdentifiantC(res.toInt());
                res=query.value(2).toString();
                inter.setCommentaire(res.toStdString());
                res=query.value(3).toString();
                inter.setDateInteraction(inter.conversionStringToDate(res.toStdString()));
                lstInter.push_back(inter);
            }

        }

    }
}

void sqldataInteraction::rechercheInteract(QString &date1, QString &date2, std::list<interaction> &lst)
{
    lst.clear();//on vide la liste pour être sûre que la liste est vide
    //conversion des deux date en day_contact
    interaction inter;
    day_interaction d1=inter.conversionStringToDate(date1.toStdString());
    day_interaction d2=inter.conversionStringToDate(date2.toStdString());
    if(dbOuvert==true)
    {
        QSqlQuery query;
        query.prepare("SELECT* FROM INTERACTION;");

        if(!query.exec())
        {
            qDebug()<<"Requete echouée";
        }else {
                qDebug()<<"Requete reussie";
                while (query.next()) {
                    QString res = query.value(3).toString();//recupération d'une date
                    //conversion de la date en day_interaction
                    interaction intr;
                    string str=res.toStdString();
                    day_interaction date = intr.conversionStringToDate(str);
                    if(d1<date && d2<date)//date1<date && date<date2)//vérification de l'inclusion de la date recupérée entre date1 et date2)
                    {
                        res=query.value(0).toString();
                        intr.setIdInteraction(res.toInt());
                        res=query.value(1).toString();
                        intr.setIdentifiantC(res.toInt());
                        res=query.value(2).toString();
                        intr.setCommentaire(res.toStdString());
                        res=query.value(3).toString();
                        intr.setDateInteraction(inter.conversionStringToDate(res.toStdString()));
                        lst.push_back(inter);
                    }
                }
        }
     }
}

void sqldataInteraction::rechercheInteractioncontact(const int &id, QString &date1, QString &date2, std::list<interaction> &lst)
{
    lst.clear();//on vide la liste pour être sûre que la liste est vide
    //conversion des deux date en day_interaction
    interaction inter;
    day_interaction d1=inter.conversionStringToDate(date1.toStdString());
    day_interaction d2=inter.conversionStringToDate(date2.toStdString());
    if(dbOuvert==true)
    {
        QSqlQuery query;
        query.prepare("SELECT* FROM INTERACTION,CONTACT WHERE INTERACTION.id_interaction = CONTACT.id_contact and CONTACT.id_contact=:con;");
        query.bindValue(":con",QString::number(id));
        query.exec();

        if(!query.exec())
        {
            qDebug()<<"Recherche d'interaction contact echouée";
        }else {
                qDebug()<<"Recherche d'interaction contact reussie";
                while (query.next()) {
                    QString res = query.value(3).toString();//recupération d'une date
                    //conversion de la date en day_interaction
                    interaction intr;
                    string str=res.toStdString();
                    day_interaction date = intr.conversionStringToDate(str);
                    if(d1<date && d2<date)//date1<date && date<date2)//vérification de l'inclusion de la date recupérée entre date1 et date2)
                    {
                        res=query.value(0).toString();
                        intr.setIdInteraction(res.toInt());
                        res=query.value(1).toString();
                        intr.setIdentifiantC(res.toInt());
                        res=query.value(2).toString();
                        intr.setCommentaire(res.toStdString());
                        res=query.value(3).toString();
                        intr.setDateInteraction(inter.conversionStringToDate(res.toStdString()));
                        lst.push_back(inter);
                    }
               }
        }

     }
}



void sqldataInteraction::slotAjouterInteraction(const int &id,interaction &inter)
{
    AjouterInteraction(id,inter);
}
void sqldataInteraction::slotListeInteractionContact(const int &id,std::list<interaction> &lst)
{
    listeInteractionContact(id,lst);
}
void sqldataInteraction::slotListeInteraction(std::list<interaction> &lst)
{
    ListeInteraction(lst);
}
void sqldataInteraction::slotRechercheInteraction(QString &r1,QString &r2,std::list<interaction> &lst)
{
    rechercheInteract(r1,r2,lst);
}
void sqldataInteraction::slotRechercheInteractionContact(const int &id,QString &r1,QString &r2,std::list<interaction> &lst)
{
    rechercheInteractioncontact(id,r1,r2,lst);
}
