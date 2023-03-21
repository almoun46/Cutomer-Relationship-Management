#ifndef CRMGA_H
#define CRMGA_H

#include <QRegExp>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextBlock>
#include <QTextDocument>
#include <QRegularExpression>
#include <QTextEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include "contact.h"
#include "interaction.h"
#include "todo.h"
#include "sqldataContact.h"
#include "sqldatainteraction.h"
QT_BEGIN_NAMESPACE
namespace Ui{class CRMGA;}
QT_END_NAMESPACE
using namespace std;

class CRMGA : public QMainWindow
{
    Q_OBJECT

public:
    CRMGA(QWidget *parent = nullptr);
    ~CRMGA();
    sqlDataContact bd;
    sqldataInteraction interbd;

private:
    Ui::CRMGA *ui;

    QDialog *DialogCreerContact;//un boite de dialog pour des données d'un nouveau contact
    QLabel *nom;
    QLabel *prenom;
    QLabel *email;
    QLabel *entreprise;
    QLabel *telephone;
    QLabel *photo;
    QLabel *image;
    QLineEdit *nm;
    QLineEdit *pr;
    QLineEdit *ml;//espace de saisie dediée à l'adresse mail
    QLineEdit *entp;//la partie de saisie du nom de l'entreprise
    QLineEdit *tel;
    QPushButton *ph;
    QPushButton *annuler;
    QPushButton *valider;
    QVBoxLayout *Vbligne1;//uniquement pour regrouper les labels en vertical
    QVBoxLayout *Vbligne2;//uniquement pour regrouper les champs d'édition en vertical
    QHBoxLayout *Hbligne3;//pour le regoupement des deux VBoxLayout en horizontale
     QHBoxLayout *Horizontal;

    QDialog *DialogModifContact;//un boite de dialog pour des données d'un nouveau contact lors de la modification de ses données
    QLabel *listecontact;
    QLabel *nomf;
    QLabel *prenomf;
    QLabel *emailf;
    QLabel *entreprisef;
    QLabel *telephonef;
    QLabel *photof;
    QComboBox *ComboModif;
    QLineEdit *nmf;
    QLineEdit *prf;
    QLineEdit *mlf;//espace de saisie dediée à l'adresse mail
    QLineEdit *entpf;//la partie de saisie du nom de l'entreprise
    QLineEdit *telf;
    QPushButton *phf;
    QPushButton *annulerf;
    QPushButton *validerf;
    QVBoxLayout *Vbligne1f;//uniquement pour regrouper les labels en vertical
    QVBoxLayout *Vbligne2f;//uniquement pour regrouper les champs d'édition en vertical
    QHBoxLayout *Hbligne3f;//pour le regoupement des deux VBoxLayout en horizontale


    QDialog *DialogSuppContact;//un boite de dialog pour supprimer un  contact
    QLabel *id_contact;
    QPushButton *annulerSuppC;
    QLineEdit *nm_pr;
    QPushButton *supprimer;
    QComboBox *ComboSupp;
    QVBoxLayout *Vbligne1S;//uniquement pour regrouper les widget en vertical
    QVBoxLayout *Vbligne2S;//uniquement pour regrouper les  widget en vertical
    QHBoxLayout *Hbligne3S;


    QDialog *DialogRechContact;//un boite de dialog pour rechercher un  contact entre deux dates
    QLabel *label_nom_Rech;
    QPushButton *annulerRechC;
    QLineEdit *nm_rech;//le champs de saisie du nom de contact à recherher
    QPushButton *BRechercher;
    //permettent la saisie ou la selection d'une date
    QDateEdit *date1;
    QDateEdit *date2;
    QVBoxLayout *Vbligne1Rech;//uniquement pour regrouper les widget en vertical
    QVBoxLayout *Vbligne2Rech;//uniquement pour regrouper les  widget en vertical
    QHBoxLayout *Hbligne3Rech;


    QDialog *DialogRechContactNom;//un boite de dialog pour rechercher tous les  contacts du nom victor par example
    QLabel *rech_nom_;
    QLineEdit *nom_RechercheCnom;
    QPushButton *annulerRechercheCnom;
    QPushButton *RechercheCnom;


    QDialog *DialogRechContactentreprise;//un boite de dialog pour rechercher tous les  contacts d'une entreprise
    QLabel *rech_nom_entreprise;
    QLineEdit *nom_RechercheC_entreprise;
    QPushButton *annulerRechercheC_entreprise;
    QPushButton *RechercheC_entreprise;


    QDialog *dialogInteraction;
    QLabel *commentaire;
    QLineEdit *cInteraction;
    QLineEdit *interactionText;
    QPushButton *BajoutInteraction;
    QPushButton *BannulerInteraction;
    QLabel *interText;
    QTextEdit *editTaches;
    QComboBox *ComboInteraction;
    QVBoxLayout *Vbligne1Inter;//uniquement pour regrouper les widget en vertical
    QVBoxLayout *Vbligne2Inter;//uniquement pour regrouper les  widget en vertical
    QVBoxLayout *Vbligne3Inter;//uniquement pour regrouper les  widget en vertical
    QVBoxLayout *Vbligne4Inter;
    QHBoxLayout *Hbligne3Inter;
    QHBoxLayout *Hhhbligne3Inter;
    QHBoxLayout *Hhbligne3Inter;
    QHBoxLayout *Hhbligne4Inter;


    QDialog *dialogListInteraction;//pour lister tous les interactions
    QLabel *LbListeContact;
    QLineEdit *ListeContact;
    QLabel *Lbnom_prenom;
    QLineEdit *nomp_prenom_Liste;
    QPushButton *BvaliderlisteInteraction;
    QPushButton *BannulerlisteInteraction;
    QComboBox   *ComboBoxListeInteraction;
    QVBoxLayout *VblisteInter1;//uniquement pour regrouper les labels en vertical
    QVBoxLayout *VblisteInter2;//uniquement pour regrouper les champs d'édition en vertical
    QHBoxLayout *HblisteInter3;//pour le regoupement des deux VBoxLayout en horizontale


    QDialog *Dialog_interactions_deux_dates;//un boite de dialog pour la recherche des interactions entre deux dates
    QLabel *ldebut_interactions_deux_dates;
    QLabel *lfin_interactions_deux_dates;
    QDateEdit *debut_interactions_deux_dates;
    QDateEdit *fin_interactions_deux_dates;
    QPushButton *Brechercher_interactions_deux_dates;
    QPushButton *Bannuler_interactions_deux_dates;
    QVBoxLayout *Vbligne1_interactions_deux_dates;//uniquement pour regrouper les labels en vertical
    QVBoxLayout *Vbligne2_interactions_deux_dates;//uniquement pour regrouper les champs d'édition en vertical
    QHBoxLayout *Hblignein_interactions_deux_dates;


    QDialog *DialogRechInterContact;//un boite de dialog pour rechercher les interactions d'un  contact entre deux dates
    QLabel *label_nom_RechInterContact;
    QPushButton *annulerRechInterContact;
    QLineEdit *nm_RechInterContact;//le champs de saisie du nom de contact à recherher ses interaction
    QPushButton *BRechInterContact;
    QLabel *indice_id_RechInterContact;
    QComboBox  *Combo_RechInterContact;
    QDateEdit *date1_RechInterContact;
    QDateEdit *date2_RechInterContact;
    QVBoxLayout *Vbligne1RechInterContact;//uniquement pour regrouper les widget en vertical
    QVBoxLayout *Vbligne2RechInterContact;//uniquement pour regrouper les  widget en vertical
    QHBoxLayout *Hbligne3RechInterContact;

    QDialog *Dialog_todo_deux_dates;//un boite de dialog pour la recherche des todo entre deux dates
    QLabel *ldebut_todo_deux_dates;
    QLabel *lfin_todo_deux_dates;
    QDateEdit *debut_todo_deux_dates;
    QDateEdit *fin_todo_deux_dates;
    QPushButton *Brechercher_todo_deux_dates;
    QPushButton *Bannuler_todo_deux_dates;
    QVBoxLayout *Vbligne1_todo_deux_dates;//uniquement pour regrouper les labels en vertical
    QVBoxLayout *Vbligne2_todo_deux_dates;//uniquement pour regrouper les champs d'édition en vertical
    QHBoxLayout *Hblignein_todo_deux_dates;

    QDialog *dialogListTodo;//pour lister tous les todos d'un contact entre deux dates
    QLabel *LbListeTodoContact;
    QDateEdit *debut_todocontact_deux_dates;
    QDateEdit *fin_todocontact_deux_dates;
    QLabel *LbTodonom_prenom;

    QPushButton *BvaliderlisteTodo;
    QPushButton *BannulerlisteTodo;
    QComboBox   *ComboBoxListeTodo;
    QVBoxLayout *VblisteTodo1;//uniquement pour regrouper les labels en vertical
    QVBoxLayout *VblisteTodo2;//uniquement pour regrouper les champs d'édition en vertical
    QHBoxLayout *HblisteTodo3;


private slots:
    void apropos();//nous
    void creerContacts();
    void ParcourirPhoto();//permet d'ouvrir une QFile pour charger sa photo
    void AnnulerCrcontact();//permet d'annuler les actions en cours
    void ValiderCrcontact();//permet de recupere, valider les données sasies

    void ModifContact();
    void ParcourirPhotof();//permet d'ouvrir une QFile pour charger une photo
    void AnnulerCrcontactf();//permet d'annuler les actions en cours
    void ValiderCrcontactf();//permet de recupere, valider les données sasies
    void remplirComboboxContact(const QString &);//reçoit un signal et remplit le formulaire

    void SupprimerContact();//prmet douvrir une boîte de dialog qui pemet la suppression d'un contact
    void annulerSuppcontact();
    void Boutonsupprimer();
    void remplirComboboxSupprimer(const QString &);

    void RechercherContact();//ouvre un boîte de recherche d'un contact entre deux dates
    void Bouton_annuler_RechC();//ferme la boîte de dialog
    void Bouton_RechercherC();//permet de rechercher les contactats du nom 'nom' entre deux dates  et de les affichés

    void rechercherContact_par_nom();//ouvre la boîte de recherche des contact par un nom
    void rechercherContact_par_entreprise();//ouvre la boîte de recherche des contact par un entreprise
    void bannulerRechercheCnom();
    void bRechercheCnom();
    void bannulerRechercheC_entreprise();
    void bRechercheC_entreprise();

    void AjoutInteraction();//ouvre une boite de dialog pour l'ajout d'une interaction à un contact
    void RemplirAjoutInter(const QString  & );//permet de remplir la combobox lors de l'ajout
    void AjoutUneInteraction();//
    void AnnulerInteraction();
    void Toutes_les_interactions();//permet le reaffichage de toutes les interactions après suppression ou mise à jour

    void ListeInteraction();//permet d'ouvrir la boîte pour affiche après la liste des interactions d'un contact
    void ListeInteractionContact();//recupère la liste des interactions et  les affichent
    void AnnulerListeInteraction();//pour fermer la boîte de dialog
    void RemplirSupInters(const QString  & );//permet de remplir la combobox après avoir donné le nom du contact


    void Interactions_deux_dates();//ouvre une boîte de dialog pour la recherche  de tous les interactions entre deux dates
    void chercher_Interactions_deux_dates();//permet de faire la requête et affiche le resultat obtenu
    void annuler_Interactions_deux_dates();//ferme la boîte de dialog


    void Rechercher_Interactioncontact_deux_dates();//permet l'ouverture de la boîte de dioalog de recherche d'interactions d'un contact entre deux dates
    void Bouton_annuler_RechInterContact();
    void Bouton_RechInterContact();
    void remplir_comboRechInterContact(const QString &);


    void Todo_deux_dates();//ouvre une boîte de dialog pour la recherche  de tous les interactions entre deux dates
    void chercher_Todo_deux_dates();//permet de faire la requête et affiche le resultat obtenu pour les todo
    void annuler_Todo_deux_dates();//ferme la boîte de dialog

    void Todo_contact_deux_dates();//permet d'ouvrir la boite de dialog de recherche des todo d'un contact entre deux dates
    void chercher_Todocontact_deux_dates();//permet de faire la requête et affiche le resultat obtenu pour les todo d'un contact
    void annuler_Todocontact_deux_dates();//ferme la boîte de dialog

    void afficheListeContacts();//lors du clic sur le bouton liste contact permet d'afficher les données de tous les contacts(inter,todo)
    void affichListeInteraction();//lors du clic surle bouton liste interaction permet l'affichage des interactions
    void ListeTodos();//pareil


    void Jsoncontact();//ppour l'export en json
    void JsonInteraction();//exportion en json;

private: signals:
    void sigAjouter(contact &);//signal pour l'insertion dans la base
    void sigModifContact(const int &, contact &);//signal de mise à jour des donnée d'un contact
    void sigListcontact(std::list<contact> &);//signal pour recuperer tous les contacts dde la base de donnéz
    void sigSupprimer(const int &);//envoie l'id du contact à supprimer
    void sigRechercheContact(QString &,QString &,QString &,std::list<contact> &);
    void sigAjoutInteraction(const int &,interaction &);//signal qui permet l'envoie d'id du contact qu'on veut lui ajouter une interaction
    void sigAjoutTodo(const int &,todo &);//
    void sigListeInteraction(const int &,std::list<interaction> &);//permet d'envouyer un signal pour la recuperation de tous les interactions du contact d'id i
    void sigListeInteractions(std::list<interaction> &);//permet la recuperation de toute les interactions
    void sigRechercheInteraction(QString &,QString &,std::list<interaction> &);//recupere de la base de donnée la liste des interactions entre ddeux dates
    void sigRechercheInteractionContact(const int ,QString & ,QString & ,std::list<interaction> &);//permet la recuperation de toute les interactions d'un contact et stock dans une liste
    void sigRechercheTodos(QString &,QString &,std::list<todo> &);//recupère tous les todos entre deux dates
    void sigRechercheTodoCont(const int &, QString &,QString &, std::list<todo> &);
    void sigListeTodos(list<todo>&);//permet l'affichage de todo de tous les contacts
    void sigRech_contact_par_nom(QString &,std::list<contact>&);//permet la recuperation de tous contact ayant un nom passé en parametre
    void sigRech_contact_par_entreprise(QString &,std::list<contact>&);//permet la recuperation de tous contact ayant d'une entreprise
};
#endif // CRMGA_H
