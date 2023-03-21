#include "sqldatatodo.h"

sqldataTodo::sqldataTodo(QObject *parent) : QObject(parent)
{
    dbOuvert = false;
    connexionDb();
}
 sqldataTodo::~sqldataTodo()
 {
     closeDb();
 }
 bool sqldataTodo::connexionDb()
 {
     QString chemin = "C:/Users/almou/Desktop/CDAA/CRM1/Bdprojet.sqlite";
     db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName(chemin);

     if(!db.open())
     {
         qDebug()<<"connexion à la base a echoué: todo";
         dbOuvert = false;
     }else {
         qDebug()<<"Connexion à la base  reussit";
         dbOuvert = true;
         QSqlQuery query;
         //création de la table todo si elle n'existe pas
         query.exec("CREATE TABLE IF NOT EXISTS TODO"
                    "(id_todo integer primary key AUTOINCREMENT, "
                    "id_interaction  integer NOT NULL,"
                    "contenu TEXT,"
                    "date TEXT ,"
                    "FOREIGN KEY (id_interaction) REFERENCES INTERACTION (id_interaction) ON DELETE CASCADE )");
         if(!query.exec())
         {
             qDebug()<<"Erreur de création de la table TODO";
         }else {
             qDebug()<<"Création  de la table TODO reussit";
         }

     }
     return dbOuvert;
 }
 void sqldataTodo::closeDb()
 {
     db.close();
 }
void sqldataTodo::isDbopen(bool &v)
{
    dbOuvert = v;
}
 bool sqldataTodo::AjouterTodo(const int &id,todo &td)const
 {

     if(dbOuvert)
     {
         QSqlQuery query("SELECT * FROM TODO");
         query.prepare("INSERT INTO TODO(id_todo,id_interaction,contenu,date) VALUES(:in,:c,:d)");
         query.bindValue(":t",QString::number(id));
         query.bindValue(":c",QString::fromStdString(td.getcontenu()));
         query.bindValue(":d",QString::fromStdString(td.conversiondateToString(td.getDate())));
         if(!query.exec())
         {
             qDebug()<<"Insertion de todo echoué";
             return false;
         }
         qDebug()<<"Insertion reussi";
     }
     return true;
 }

 void sqldataTodo::listeTodoContact(const int&id,std::list<todo> &lst)const
 {
     lst.clear();
     if(dbOuvert)
     {
         QSqlQuery query;
          query.prepare("SELECT * FROM TODO,INTERACTION,CONTACT WHERE TODO.id_interaction = INTERACTION.id_interaction "
                        "AND INTERACTION.id_contact=CONTACT.id_contact AND CONTACT.id_contact=:in");
         query.bindValue(":in",QString::number(id));
         query.exec();
         if(!query.exec())
         {
             qDebug()<<"requête echouée";
         }else{
             qDebug()<<"Requête reussit";
             while (query.next()) {
                 todo t;
                 QString res = query.value(0).toString();
                 t.setIid_todo(res.toInt());
                 res = query.value(1).toString();
                 t.setId_interation(res.toInt());
                 res = query.value(2).toString();
                 t.setcontenu(res.toStdString());
                 res = query.value(3).toString();
                 date::year_month_day d= t.conversionStringToDate(res.toStdString());
                 t.setD(d.day().operator unsigned int());
                 t.setD(d.month().operator unsigned int());
                 t.setD(d.year().operator  int());
                 lst.push_back(t);

             }
             //lst.sort();
         }

     }

 }

 void sqldataTodo::ListeTodo(std::list<todo> &lst)
 {
     lst.clear();
     if(dbOuvert)
     {
         QSqlQuery query("SELECT * FROM TODO,INTERACTION,CONTACT WHERE TODO.id_interaction = INTERACTION.id_interaction "
                        "AND INTERACTION.id_contact=CONTACT.id_contact ");

         if(!query.exec())
         {
             qDebug()<<"Affichage  liste complète todo echouée";
         }else{
             qDebug()<<"Affichage  liste complète todo reussit";
             while (query.next()) {
                 todo t;
                 QString res = query.value(0).toString();
                 t.setIid_todo(res.toInt());
                 res = query.value(1).toString();
                 t.setId_interation(res.toInt());
                 res = query.value(2).toString();
                 t.setcontenu(res.toStdString());
                 res = query.value(3).toString();
                 date::year_month_day d= t.conversionStringToDate(res.toStdString());
                 t.setD(d.day().operator unsigned int());
                 t.setD(d.month().operator unsigned int());
                 t.setD(d.year().operator  int());
                 lst.push_back(t);

             }
             //lst.sort();
         }

     }

 }

 void sqldataTodo::rechercheTodo(QString &date1,QString &date2,std::list<todo> &lst)
 {
     lst.clear();//on vide la liste pour être sûre que la liste est vide
     //conversion des deux date en year_month_day
     todo inter;
     year_month_day d1=inter.conversionStringToDate(date1.toStdString());
     year_month_day d2=inter.conversionStringToDate(date2.toStdString());
     if(dbOuvert==true)
     {
         QSqlQuery query;
         query.prepare("SELECT* FROM TODO;");

         if(!query.exec())
         {
             qDebug()<<"Requete echouée";
         }else {
                 qDebug()<<"Requete reussie";
                 while (query.next()) {
                     QString res = query.value(3).toString();//recupération d'une date
                    date::year_month_day date= inter.conversionStringToDate(res.toStdString());
                     if(d1<date && d2<date)//date1<date && date<date2)//vérification de l'inclusion de la date recupérée entre date1 et date2)
                     {
                         todo t;
                         QString res = query.value(0).toString();
                         t.setIid_todo(res.toInt());
                         res = query.value(1).toString();
                         t.setId_interation(res.toInt());
                         res = query.value(2).toString();
                         t.setcontenu(res.toStdString());
                         res = query.value(3).toString();
                         t.setD(date.day().operator unsigned int());
                         t.setD(date.month().operator unsigned int());
                         t.setD(date.year().operator  int());
                         lst.push_back(t);
                     }

                 }
         }
     }
 }

 void sqldataTodo::rechercheTodocontact(const int &id,QString &date1,QString &date2,std::list<todo> &lst)
 {
     lst.clear();//on vide la liste pour être sûre que la liste est vide
     //conversion des deux date en year_month_day
     todo inter;
     year_month_day d1=inter.conversionStringToDate(date1.toStdString());
     year_month_day d2=inter.conversionStringToDate(date2.toStdString());
     if(dbOuvert==true)
     {
         QSqlQuery query;
         query.prepare("SELECT * FROM TODO,iNTERACTION,CONTACT WHERE TODO.id_interaction = INTERACTION.id_interaction "
                       "AND INTERACTION.id_contact=CONTACT.id_contact AND CONTACT.id_contact=:in");
        query.bindValue(":in",QString::number(id));
        query.exec();

         if(!query.exec())
         {
             qDebug()<<"Requete echouée";
         }else {
                 qDebug()<<"Requete reussie";
                 while (query.next()) {
                     QString res = query.value(3).toString();//recupération d'une date
                    date::year_month_day date= inter.conversionStringToDate(res.toStdString());
                     if(d1<date && d2<date)//date1<date && date<date2)//vérification de l'inclusion de la date recupérée entre date1 et date2)
                     {
                         todo t;
                         QString res = query.value(0).toString();
                         t.setIid_todo(res.toInt());
                         res = query.value(1).toString();
                         t.setId_interation(res.toInt());
                         res = query.value(2).toString();
                         t.setcontenu(res.toStdString());
                         res = query.value(3).toString();
                         t.setD(date.day().operator unsigned int());
                         t.setD(date.month().operator unsigned int());
                         t.setD(date.year().operator  int());
                         lst.push_back(t);
                     }

                 }
         }
     }
 }




 //les slots
 void sqldataTodo::slotAjouterTodo(const int &id,todo &td)
 {
     AjouterTodo(id,td);
 }
 void sqldataTodo::slotListeTodoContact(const int&id,std::list<todo> &lst)
 {
     slotListeTodoContact(id,lst);
 }
 void sqldataTodo::slotRechercheTodo(QString &date1,QString &date2,std::list<todo> &lst)
 {
      rechercheTodo(date1,date2,lst);
 }
void sqldataTodo::slotRechercheTodoContact(const int &id,QString &date1,QString &date2,std::list<todo> &lst)
{
    rechercheTodocontact(id,date1,date2,lst);
}
void sqldataTodo::slotListeTodos(list<todo> &t)
{
    ListeTodo(t);
}
