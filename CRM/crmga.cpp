 #include "crmga.h"
#include "ui_crmga.h"
#include <QDebug>
CRMGA::CRMGA(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::CRMGA)
{
    ui->setupUi(this);

    ComboModif   = new QComboBox ();
    ComboSupp    = new QComboBox ();
    ComboInteraction =new QComboBox ();
    ComboBoxListeInteraction =new QComboBox ();
    Combo_RechInterContact = new QComboBox ();
    ComboBoxListeTodo =new QComboBox();

    //comboTodo =new QComboBox();
    //les connections des actions des sous menu avec leur slot respectif

    connect(ui->action_Apropos,SIGNAL(triggered()),this,SLOT(apropos()));
    connect(ui->actionCreerContact,SIGNAL(triggered()),this,SLOT(creerContacts()));//ajouter un contact à la base
    connect(ui->actionModifier,SIGNAL(triggered()),this,SLOT(ModifContact()));//modifier
    connect(ui->actionSupprimer,SIGNAL(triggered()),this,SLOT(SupprimerContact()));//supprimer
    connect(ui->actionRechercher,SIGNAL(triggered()),this,SLOT(RechercherContact()));//chercher un contact entre deux dates
    connect(ui->actionRechercher_par_nom,SIGNAL(triggered()),this,SLOT(rechercherContact_par_nom()));//chercher les contact avec un nom
    connect(ui->actionRechercher_par_entreprise,SIGNAL(triggered()),this,SLOT(rechercherContact_par_entreprise()));//chercher les contact avec un nom
    connect(ui->actionAjouter,SIGNAL(triggered()),this,SLOT(AjoutInteraction()));//ajouter une interaction à un contact
    connect(ui->actionAfficher_liste,SIGNAL(triggered()),this,SLOT(ListeInteraction()));//affiché les interactions présent dans la base de donnéé
    connect(ui->actionInteraction_entre_deux_dates,SIGNAL(triggered()),this,SLOT(Interactions_deux_dates()));
    connect(ui->actionInteraction_d_un_contact_entre_deux_dates,SIGNAL(triggered()),this,SLOT(Rechercher_Interactioncontact_deux_dates()));//pour la recherche dinteraction d'un contact entre deux dates
    connect(ui->actionTous_les_Taches,SIGNAL(triggered()),this,SLOT(Todo_deux_dates()));//x
    connect(ui->actionTous_les_taches_d_un_contact_entre_deux_dates,SIGNAL(triggered()),this,SLOT(Todo_contact_deux_dates()));

    //clic sur les boutons
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(afficheListeContacts()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(Jsoncontact()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(affichListeInteraction()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(JsonInteraction()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(ListeTodos()));


}
CRMGA::~CRMGA()
{

}


void CRMGA::creerContacts()
{
    DialogCreerContact = new QDialog (this);
    DialogCreerContact->setWindowTitle("Créer un contact");
    DialogCreerContact->resize(400,10);
    DialogCreerContact->setModal(true);

    nom = new QLabel ("Nom :");
    prenom = new QLabel ("prenom :");
    email = new QLabel ("E-mail :");
    entreprise = new QLabel ("Entreprise :");
    telephone = new QLabel ("Téléphone :");
    photo = new QLabel ("Photo :");
    image = new QLabel("Mon Image");

    nm = new QLineEdit ();
    pr = new QLineEdit ();
    ml = new QLineEdit ();
    entp = new QLineEdit ();
    tel = new QLineEdit ();
    ph = new QPushButton ("Parcourir");

    annuler = new QPushButton ("Annuler");
    valider = new  QPushButton ("Valider");

    Vbligne1 =new QVBoxLayout ();
    Vbligne2 =new QVBoxLayout ();
    Hbligne3 =new QHBoxLayout ();
    Vbligne1->addWidget(nom);
    Vbligne1->addWidget(prenom);
    Vbligne1->addWidget(email);
    Vbligne1->addWidget(entreprise);
    Vbligne1->addWidget(telephone);
    Vbligne1->addWidget(photo);
    Vbligne1->addWidget(annuler);

    Vbligne2->addWidget(nm);
    Vbligne2->addWidget(pr);
    Vbligne2->addWidget(ml);
    Vbligne2->addWidget(entp);
    Vbligne2->addWidget(tel);
    Vbligne2->addWidget(ph);
    Vbligne2->addWidget(valider);

    Hbligne3->addLayout(Vbligne1);
    Hbligne3->addLayout(Vbligne2);
    Horizontal = new QHBoxLayout();
    Horizontal->addLayout(Hbligne3);
    Horizontal->addWidget(image);

    DialogCreerContact->setLayout(Horizontal);
    DialogCreerContact->show();

    //conexion des trois bouton aux slots respectifs
    connect(ph,SIGNAL(clicked()),this,SLOT(ParcourirPhoto()));
    connect(annuler,SIGNAL(clicked()),this,SLOT(AnnulerCrcontact()));
    connect(valider,SIGNAL(clicked()),this,SLOT(ValiderCrcontact()));

}

void CRMGA::ParcourirPhoto()
{
    int w =image->width();
    int h =image->height();
   //ouverture d'une boite de dialogue pour un fiechier
    QString dir = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier "),QString(),
                                               "Images (*.png *.gif *.jpg *.jpeg *.bmp)");
    image->setPixmap(QPixmap(dir).scaled(w,h,Qt::KeepAspectRatio));
    ph->setText(dir);
}
void CRMGA::AnnulerCrcontact()
{
    DialogCreerContact->close();
}
void CRMGA::ValiderCrcontact()
{
    if(nm->text()!=NULL and pr->text()!=NULL and ml->text()!=NULL and entp!= NULL and tel->text()!=NULL and ph->text()!=NULL)
    {



        QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");//pour la gestion du format de mail
        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);
       // qDebug() << mailREX.exactMatch("me@me.com");
        bool regMat = mailREX.exactMatch(ml->text());

       if(regMat == false)
       {
           QMessageBox *message = new QMessageBox(this);
           message->setWindowModality(Qt::NonModal);
           message->setText("mail au format incorrect");
           message->setStandardButtons(QMessageBox::Ok);
           message->setWindowTitle("MainWindow");
           message->setIcon(QMessageBox::Information);
           message->exec();

           ml->clear();
       }
       else{


        contact con;
        con.setNom(nm->text().toStdString());
        con.setPrenom(pr->text().toStdString());
        con.setEmail(ml->text().toStdString());
        con.setNomEntresprise(entp->text().toStdString());
        QRegExp telRegex("^+[0-9]{10,15}$");
        QRegExpValidator *telValidator = new QRegExpValidator(telRegex, this);
        tel->setValidator(telValidator);
        con.setTelephone(tel->text().toStdString());
        con.setPhoto(ph->text().toStdString());
        emit sigAjouter(con);
        std::list<contact> lst;
        ui->CentreText->clear();
        //liste vide et signal
        lst.clear();
        emit sigListcontact(lst);
        ComboModif->clear();
        ComboSupp->clear();
        Combo_RechInterContact->clear();
        ComboInteraction->clear();
        ComboBoxListeInteraction->clear();
        ComboBoxListeTodo->clear();

        QMessageBox::information(this,"Creation contact","Creation de contact reussit");
        DialogCreerContact->close();
       }
   }else {
    QMessageBox::information(this,"Erreur","Veuillez remplir correctement tous les champsœ");
    }

}

//Modifier sous menu
void CRMGA::ModifContact()
{
    DialogModifContact = new QDialog (this);
    DialogModifContact->setWindowTitle("Modifier un contact");
    DialogModifContact->resize(400,200);
    DialogModifContact->setModal(true);
    listecontact = new QLabel("Liste contact");
    nomf = new QLabel ("Nom :");
    prenomf = new QLabel ("prenom :");
    emailf = new QLabel ("E-mail :");
    entreprisef = new QLabel ("Entreprise :");
    telephonef = new QLabel ("Téléphone :");
    photof = new QLabel ("Photo :");


    nmf = new QLineEdit ();
    prf = new QLineEdit ();
    mlf = new QLineEdit ();
    entpf = new QLineEdit ();
    telf = new QLineEdit ();
    phf = new QPushButton ("Parcourir");

    annulerf = new QPushButton ("Annuler");
    validerf = new  QPushButton ("Valider");

    Vbligne1f =new QVBoxLayout ();
    Vbligne2f =new QVBoxLayout ();
    Hbligne3f =new QHBoxLayout ();
    Vbligne1->addWidget(listecontact);
    Vbligne1f->addWidget(nomf);
    Vbligne1f->addWidget(prenomf);
    Vbligne1f->addWidget(emailf);
    Vbligne1f->addWidget(entreprisef);
    Vbligne1f->addWidget(telephonef);
    Vbligne1f->addWidget(photof);
    Vbligne1f->addWidget(annulerf);

    Vbligne2->addWidget(ComboModif);
    Vbligne2f->addWidget(nmf);
    Vbligne2f->addWidget(prf);
    Vbligne2f->addWidget(mlf);
    Vbligne2f->addWidget(entpf);
    Vbligne2f->addWidget(telf);
    Vbligne2f->addWidget(phf);
    Vbligne2f->addWidget(validerf);

    Hbligne3f->addLayout(Vbligne1f);
    Hbligne3f->addLayout(Vbligne2f);

    DialogModifContact->setLayout(Hbligne3f);
    DialogModifContact->show();

    //conexion des trois bouton aux slots respectifs
    connect(phf,SIGNAL(clicked()),this,SLOT(ParcourirPhotof()));
    connect(annulerf,SIGNAL(clicked()),this,SLOT(AnnulerCrcontactf()));
    connect(validerf,SIGNAL(clicked()),this,SLOT(ValiderCrcontactf()));
    connect(ComboModif,SIGNAL(currentTextChanged(const QString &)),this,SLOT(remplirComboboxContact(const QString &val)));
}

void CRMGA::AnnulerCrcontactf()
{
    DialogModifContact->close();
}
void CRMGA::ValiderCrcontactf()
{
    if(nm->text()!=NULL and pr->text()!=NULL and ml->text()!=NULL and entp!= NULL and tel->text()!=NULL and ph->text()!=NULL)
    {
        contact con;
        con.setNom(nmf->text().toStdString());
        con.setPrenom(prf->text().toStdString());
        con.setEmail(mlf->text().toStdString());
        con.setNomEntresprise(entpf->text().toStdString());
        con.setTelephone(telf->text().toStdString());
        con.setPhoto(phf->text().toStdString());
        int id_c = ComboModif->currentText().toInt();//recuperation de valeur(id du contact) du combox
        emit sigModifContact(id_c,con);//envoie du signal pour la modification ou la mise en jour dans la base de donnée
        std::list<contact> lst;
        ui->CentreText->clear();
        lst.clear();//pour être sûre d'envoyé une liste vide
        emit sigListcontact(lst);
        ComboModif->clear();
        ComboSupp->clear();
        ComboBoxListeTodo->clear();
        ComboInteraction->clear();
        Combo_RechInterContact->clear();
        ComboBoxListeInteraction->clear();

        QString resultat, entete;
        entete = "id_contact \t";
        entete +="Nom \t";
        entete += "Prenom \t";
        entete +="Email \t";
        entete += "entreprise \t";
        entete +="Téléphone \t";
        entete +="Photo \t";
        entete +="Date\n\n";
        //on affiche la liste des contacts recuperée
        for (auto &co: lst) {contact c;
            resultat+=QString::number(co.getIdentifiantC()) +"\t";
            resultat+=QString::fromStdString(co.getNom())+"\t";
            resultat+=QString::fromStdString(co.getPrenom())+"\t";
            resultat+=QString::fromStdString(co.getEmail())+"\t";
            resultat+=QString::fromStdString(co.getNomEntreprise())+"\t";
            resultat+=QString::fromStdString(co.getTelephone())+"\t";
            resultat+=QString::fromStdString(co.getPhoto())+"\t";
            resultat+=QString::fromStdString(co.conversiondateToString(co.getdateContct())) +"\n";
            ComboSupp->addItem(QString::number(co.getIdentifiantC()));
            ComboModif->addItem(QString::number(co.getIdentifiantC()));
            ComboInteraction->addItem(QString::number(co.getIdentifiantC()));
            Combo_RechInterContact->addItem(QString::number(co.getIdentifiantC()));
            ComboBoxListeInteraction->addItem(QString::number(co.getIdentifiantC()));
            ComboBoxListeTodo->addItem(QString::number(co.getIdentifiantC()));

        }

        //liste vide et signal

        QMessageBox::information(this,"Modication contact","Modification de contact reussit");
        ui->CentreText->insertPlainText(resultat);//affichage de tous les contacts avec mise à jour sur le QlineEdit central
        DialogCreerContact->close();
    }else {
        QMessageBox::warning(this,"Erreur","Veuillez remplir  tous les champs");
    }
}
 void  CRMGA::ParcourirPhotof()
 {
     QString dir = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier "),QString(),
                                                "Images (*.png *.gif *.jpg *.jpeg *.bmp)");
     phf->setText(dir);
 }
//lorsqu'on choisit un id dans la combobox on remplie automatiquement les champs pour l'utilisateur
 void CRMGA::remplirComboboxContact(const QString &val)
 {
     list<contact> lst;lst.clear();
     emit sigListcontact(lst);
     for(auto &con:lst)
     {
         if (con.getIdentifiantC()==val.toInt()) {
             nmf->setText(QString::fromStdString(con.getNom()));
             prf->setText(QString::fromStdString(con.getPrenom()));
             mlf->setText(QString::fromStdString(con.getEmail()));
             entpf->setText(QString::fromStdString(con.getNomEntreprise()));
             phf->setText(QString::fromStdString(con.getPhoto()));
             telf->setText(QString::fromStdString(con.getTelephone()));


         }
     }
 }


 //permet d'ouvrir la boite de dialog qui permet la suppression d'un contact
 void CRMGA::SupprimerContact()
 {
     DialogSuppContact =new QDialog();
     DialogSuppContact->setWindowTitle("Suppression ");
     //permet aux layouts contenuent de fixer la taille de la boîte
     //DialogSuppContact->layout()->setSizeConstraint( QLayout::SetFixedSize );
     DialogSuppContact->setModal(true);

     id_contact =new QLabel ("id contat :");
     QLabel *nom_prenom=new QLabel ("Nom/prenom");
      nm_pr= new QLineEdit ();
     annulerSuppC = new QPushButton("Annuler");
     supprimer = new QPushButton ("Supprimer");

     Vbligne1S =new QVBoxLayout();
     Vbligne2S =new QVBoxLayout ();
     Hbligne3S =new QHBoxLayout ();
     Vbligne1S->addWidget(id_contact);
     Vbligne2S->addWidget(ComboSupp);
     Vbligne1S->addWidget(nom_prenom);
     Vbligne2S->addWidget(nm_pr);
     Vbligne1S->addWidget(annulerSuppC);
     Vbligne2S->addWidget(supprimer);
     Hbligne3S->addLayout(Vbligne1S);
     Hbligne3S->addLayout(Vbligne2S);

     DialogSuppContact->setLayout(Hbligne3S);
     DialogSuppContact->show();
     //connect
     connect(annulerSuppC,SIGNAL(clicked()),this,SLOT(annulerSuppcontact()));
     connect(supprimer,SIGNAL(clicked()),this,SLOT(Boutonsupprimer()));
     connect(ComboSupp,SIGNAL(currentTextChanged(const QString &)),SLOT(remplirComboboxSupprimer(const QString &)));



 }
void CRMGA::annulerSuppcontact()
{
    DialogSuppContact->close();
}
void CRMGA::Boutonsupprimer()
{
    //on efface tous les contacts étant affichés
    ui->CentreText->clear();
    if(ComboSupp->currentText()!=NULL)
    {
        int id = ComboSupp->currentText().toInt();
        emit sigSupprimer(id);
        list<contact>lst;//listqui sera remplit de la base de donnée après la suppression du contact d'id id
        lst.clear();
        emit sigListcontact(lst);
        ComboModif->clear();//on efface tous les id contenues au paravant
        ComboSupp->clear();
        ComboInteraction->clear();
        ComboBoxListeInteraction->clear();
        Combo_RechInterContact->clear();
        ComboBoxListeTodo->clear();
        QString resultat, entete;
        entete = "id_contact \t";
        entete +="Nom \t";
        entete += "Prenom \t";
        entete +="Email \t";
        entete += "entreprise \t";
        entete +="Téléphone \t";
        entete +="Photo \t";
        entete +="Date\n\n";
        //on affiche la liste des contacts recuperée
        for (auto &co: lst) {contact c;
            resultat+=QString::number(co.getIdentifiantC()) +"\t";
            resultat+=QString::fromStdString(co.getNom())+"\t";
            resultat+=QString::fromStdString(co.getPrenom())+"\t";
            resultat+=QString::fromStdString(co.getEmail())+"\t";
            resultat+=QString::fromStdString(co.getNomEntreprise())+"\t";
            resultat+=QString::fromStdString(co.getTelephone())+"\t";
            resultat+=QString::fromStdString(co.getPhoto())+"\t";
            resultat+=QString::fromStdString(co.conversiondateToString(co.getdateContct())) +"\n";
            ComboModif->addItem(QString::number(co.getIdentifiantC()));//on remet les nouvelles id
            ComboSupp->addItem(QString::number(co.getIdentifiantC()));//
            ComboInteraction->addItem(QString::number(co.getIdentifiantC()));
            ComboBoxListeInteraction->addItem(QString::number(co.getIdentifiantC()));
            Combo_RechInterContact->addItem(QString::number((co.getIdentifiantC())));
            ComboBoxListeTodo->addItem(QString::number((co.getIdentifiantC())));
        }
        ui->CentreText->insertPlainText(resultat);

        //appel des fonctions d'affichage des interactions et des todos
        Toutes_les_interactions();
   }else {
        QMessageBox::warning(this,"Erreur ","Suppression impossible sans affichage des contacts");
    }
}
void CRMGA::remplirComboboxSupprimer(const QString &val)
{
    list<contact> lst;lst.clear();
    emit sigListcontact(lst);
    for(auto &con:lst)
    {
        if (con.getIdentifiantC()==val.toInt()) {
            nm_pr->setText(QString::fromStdString(con.getNom())+" "+QString::fromStdString(con.getPrenom()));
        }
    }
}


//rechercher un contact
void CRMGA::RechercherContact()
{
    DialogRechContact = new QDialog ();
    DialogRechContact->setWindowTitle("Recherher un contact par son nom");
    DialogRechContact->setModal(true);

    label_nom_Rech = new QLabel ("Nom :");
    nm_rech = new QLineEdit ();
    annulerRechC = new QPushButton ("Annuler");
    BRechercher = new QPushButton ("Recherher");
    QLabel *debut = new QLabel ("Date de debut :");
    QLabel *fin =  new QLabel ("Date de fin :");
    date1 =new QDateEdit ();
    date2 = new QDateEdit();

    Vbligne1Rech = new QVBoxLayout ();
    Vbligne2Rech = new QVBoxLayout ();
    Hbligne3Rech = new QHBoxLayout ();
    Vbligne1Rech->addWidget(label_nom_Rech);
    Vbligne2Rech->addWidget(nm_rech);
    Vbligne1Rech->addWidget(debut);
    Vbligne2Rech->addWidget(date1);
    Vbligne1Rech->addWidget(fin);
    Vbligne2Rech->addWidget(date2);
    Vbligne1Rech->addWidget(annulerRechC);
    Vbligne2Rech->addWidget(BRechercher);
    Hbligne3Rech->addLayout(Vbligne1Rech);
    Hbligne3Rech->addLayout(Vbligne2Rech);

    DialogRechContact->setLayout(Hbligne3Rech);
    DialogRechContact->show();
    //connect

    connect(annulerRechC,SIGNAL(clicked()),this,SLOT(Bouton_annuler_RechC()));
    connect(BRechercher,SIGNAL(clicked()),this,SLOT(Bouton_RechercherC()));


}
void CRMGA::Bouton_annuler_RechC()
{
    DialogRechContact->close();
}
void CRMGA::Bouton_RechercherC()
{
    if(nm_rech->text()!=NULL)
    {
        std::list<contact> lst;
        ui->CentreText->clear();//Pour raffraichir l'affichage sur la base de donnée
        QString date01="";
        QString date02="";
        QString sep="-";

        QString tr=date1->text();
        date01=(((date01.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

        tr=date2->text();
        date02=(((date02.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

        tr=nm_rech->text();
        emit sigRechercheContact(tr,date01,date02,lst);//on envoie le nom,les dates et une liste vide à être remplit

        QString resultat, entete;
        entete = "id_contact \t";
        entete +="Nom \t";
        entete += "Prenom \t";
        entete +="Email \t";
        entete += "entreprise \t";
        entete +="Téléphone \t";
        entete +="Photo \t";
        entete +="Date\n\n";
        ui->CentreText->insertPlainText(entete);
        for(auto &co:lst)
        {
            resultat+=QString::number(co.getIdentifiantC()) +"\t";
            resultat+=QString::fromStdString(co.getNom())+"\t";
            resultat+=QString::fromStdString(co.getPrenom())+"\t";
            resultat+=QString::fromStdString(co.getEmail())+"\t";
            resultat+=QString::fromStdString(co.getNomEntreprise())+"\t";
            resultat+=QString::fromStdString(co.getTelephone())+"\t";
            resultat+=QString::fromStdString(co.getPhoto())+"\t";
            resultat+=QString::fromStdString(co.conversiondateToString(co.getdateContct())) +"\n";
        }

      ui->CentreText->insertPlainText(resultat);
      DialogRechContact->close();
    }else {
        QMessageBox::warning(this,"Recherche Impossible","Veuilez Donnez un nom de contact");
    }

}


//rechercher des contact par un nom
void CRMGA::rechercherContact_par_nom()
{
    DialogRechContactNom = new QDialog(this);
    DialogRechContactNom->setWindowTitle("Recheche des contacts du nom ");
    DialogRechContactNom->setModal(true);
    rech_nom_ = new QLabel("Nom :");
    nom_RechercheCnom = new QLineEdit();
    annulerRechercheCnom = new QPushButton("Annuler");
    RechercheCnom = new QPushButton("Rechercher");
    QVBoxLayout *v1 =new QVBoxLayout();
    QVBoxLayout *v2 = new QVBoxLayout();
    QHBoxLayout *h1 = new QHBoxLayout();
    v1->addWidget(rech_nom_);
     v2->addWidget(nom_RechercheCnom);
    v1->addWidget(annulerRechercheCnom);
    v2->addWidget(RechercheCnom);
    h1->addLayout(v1);
    h1->addLayout(v2);
    DialogRechContactNom->setLayout(h1);
    DialogRechContactNom->show();

    connect(annulerRechercheCnom,SIGNAL(clicked()),this,SLOT(bannulerRechercheCnom()));
    connect(RechercheCnom,SIGNAL(clicked()),this,SLOT(bRechercheCnom()));
}
void CRMGA::bannulerRechercheCnom()
{
    DialogRechContactNom->close();
}
void CRMGA::bRechercheCnom()
{
    QString r =nom_RechercheCnom->text();
    if(r!=NULL)
    {
            std::list<contact> lst;

            lst.clear();

            emit sigRech_contact_par_nom(r,lst);
            ui->CentreText->clear();
            QString resultat, entete;
            entete = "id_contact \t";
            entete +="Nom \t";
            entete += "Prenom \t";
            entete +="Email \t";
            entete += "entreprise \t";
            entete +="Téléphone \t";
            entete +="Photo \t";
            entete +="Date\n\n";
            ui->CentreText->insertPlainText(entete);
            for(auto &co:lst)
            {
                resultat+=QString::number(co.getIdentifiantC()) +"\t";
                resultat+=QString::fromStdString(co.getNom())+"\t";
                resultat+=QString::fromStdString(co.getPrenom())+"\t";
                resultat+=QString::fromStdString(co.getEmail())+"\t";
                resultat+=QString::fromStdString(co.getNomEntreprise())+"\t";
                resultat+=QString::fromStdString(co.getTelephone())+"\t";
                resultat+=QString::fromStdString(co.getPhoto())+"\t";
                resultat+=QString::fromStdString(co.conversiondateToString(co.getdateContct())) +"\n";
            }

          ui->CentreText->insertPlainText(resultat);
          DialogRechContact->close();
    }else {
        QMessageBox::warning(this,"Recherche Impossible","Veuilez Donnez un nom de contact");
    }
}



//cherche des contacts par le nom de l'entreprise
void CRMGA::rechercherContact_par_entreprise()
{
    DialogRechContactentreprise = new QDialog(this);
    DialogRechContactentreprise->setWindowTitle("Recheche des contacts par le nom de l'entreprise ");
    DialogRechContactentreprise->setModal(true);
    rech_nom_entreprise = new QLabel("Nom entreprise:");
    nom_RechercheC_entreprise = new QLineEdit();
    annulerRechercheC_entreprise = new QPushButton("Annuler");
    RechercheC_entreprise = new QPushButton("Rechercher");
    QVBoxLayout *v1 =new QVBoxLayout();
    QVBoxLayout *v2 = new QVBoxLayout();
    QHBoxLayout *h1 = new QHBoxLayout();
    v1->addWidget(rech_nom_entreprise);
     v2->addWidget(nom_RechercheC_entreprise);
    v1->addWidget(annulerRechercheC_entreprise);
    v2->addWidget(RechercheC_entreprise);
    h1->addLayout(v1);
    h1->addLayout(v2);
    DialogRechContactentreprise->setLayout(h1);
    DialogRechContactentreprise->show();

    connect(annulerRechercheC_entreprise,SIGNAL(clicked()),this,SLOT(bannulerRechercheC_entreprise()));
    connect(RechercheC_entreprise,SIGNAL(clicked()),this,SLOT(bRechercheC_entreprise()));
}
void CRMGA::bannulerRechercheC_entreprise()
{
    DialogRechContactentreprise->close();
}
void CRMGA::bRechercheC_entreprise()
{
    QString r =nom_RechercheC_entreprise->text();
    if(r!=NULL)
    {
            list<contact> lst;

            lst.clear();

            emit sigRech_contact_par_entreprise(r,lst);
            ui->CentreText->clear();
            QString resultat, entete;
            entete = "id_contact \t";
            entete +="Nom \t";
            entete += "Prenom \t";
            entete +="Email \t";
            entete += "entreprise \t";
            entete +="Téléphone \t";
            entete +="Photo \t";
            entete +="Date\n\n";
            ui->CentreText->insertPlainText(entete);
            for(auto &co:lst)
            {
                resultat+=QString::number(co.getIdentifiantC()) +"\t";
                resultat+=QString::fromStdString(co.getNom())+"\t";
                resultat+=QString::fromStdString(co.getPrenom())+"\t";
                resultat+=QString::fromStdString(co.getEmail())+"\t";
                resultat+=QString::fromStdString(co.getNomEntreprise())+"\t";
                resultat+=QString::fromStdString(co.getTelephone())+"\t";
                resultat+=QString::fromStdString(co.getPhoto())+"\t";
                resultat+=QString::fromStdString(co.conversiondateToString(co.getdateContct())) +"\n";
            }

          ui->CentreText->insertPlainText(resultat);
          DialogRechContact->close();
    }else {
        QMessageBox::warning(this,"Recherche Impossible","Veuilez Donnez un nom d'entrepriset");
    }
}




//interaction
void CRMGA::AjoutInteraction()
{
    dialogInteraction=new QDialog();
    dialogInteraction->setWindowTitle(tr("Ajout Intéraction "));
    dialogInteraction->setModal(true);

    commentaire=new QLabel("Commentaire");
    cInteraction=new QLineEdit();
    QLabel *NomContact=new QLabel("Indice Contact ");
    BajoutInteraction= new QPushButton("Ajout Interaction");
    BannulerInteraction= new QPushButton("Annuler");
    //champ de texte
    editTaches=new QTextEdit();


    Hhbligne3Inter=new QHBoxLayout();
    Hhhbligne3Inter=new QHBoxLayout();
    Hhbligne4Inter=new QHBoxLayout();
    Hbligne3Inter=new QHBoxLayout();
    Vbligne1Inter=new QVBoxLayout();
    Vbligne2Inter=new QVBoxLayout();
    Vbligne3Inter=new QVBoxLayout();
    Vbligne4Inter=new QVBoxLayout();
    interText=new QLabel("nom/Prenom");
    interactionText=new QLineEdit();


    Hhbligne3Inter->addWidget(NomContact);
    Hhbligne3Inter->addWidget(ComboInteraction);
    Hhbligne3Inter->addWidget(commentaire);
    Hhbligne3Inter->addWidget(cInteraction);
    Hbligne3Inter->addWidget(interText);
    Hbligne3Inter->addWidget(interactionText);
    /*Hhbligne3Inter->addLayout(Vbligne1Inter);
    Hhbligne3Inter->addLayout(Vbligne2Inter);*/

    //Hhhbligne3Inter->addWidget(editTaches);
    Hhhbligne3Inter->addWidget(BannulerInteraction);
    Hhhbligne3Inter->addWidget(BajoutInteraction);
    Vbligne4Inter->addLayout(Hbligne3Inter);
    Vbligne4Inter->addLayout(Hbligne3Inter);
    Vbligne4Inter->addLayout(Hhbligne3Inter);
    Vbligne4Inter->addWidget(editTaches);
    Vbligne4Inter->addLayout(Hhhbligne3Inter);
    /*Vbligne4Inter->addWidget(editTaches);

    Hbligne3Inter->addLayout(Hhbligne3Inter);
    Hbligne3Inter->addLayout(Hhhbligne3Inter);
    Hbligne3Inter->addLayout(Hhbligne4Inter);*/

    dialogInteraction->setLayout(Vbligne4Inter);
    dialogInteraction->show();

    connect(BajoutInteraction,SIGNAL(clicked()),this,SLOT(AjoutUneInteraction()));/*!< connection du bouton BajoutInteraction de l'application au slot AjoutUneInteraction*/
    connect(BannulerInteraction,SIGNAL(clicked()),this,SLOT(AnnulerInteraction()));/*!< la connection pour le bouton BannulerInteraction pour fermet la fenetre */
    connect(ComboInteraction,SIGNAL(currentTextChanged(const QString  & )),this,SLOT(RemplirAjoutInter(const QString  & )));/*!< la connection de la combo au IHM lorsque l'on appui sur la Combo box */

}

void CRMGA::AnnulerInteraction()
{
    dialogInteraction->close();
}
void CRMGA::AjoutUneInteraction()
{
     interaction inter;
    QString t=ComboInteraction->currentText();

    if(t!=NULL)
     {

                int  c1=t.toInt();
                inter.setCommentaire(cInteraction->text().toStdString());

                inter.setIdentifiantC(c1);
                emit  sigAjoutInteraction(c1,inter);
                QTextDocument * qdoc=editTaches->document();
                QTextCursor c(qdoc);
                 QTextDocument::FindFlag  fcs=(QTextDocument::FindFlag) 0;
                 QStringList ltodos;
                 while(!c.isNull())
                 {
                     QRegularExpression qreg("^@todo .*$");
                     c=qdoc->find(qreg, c.position(),fcs);
                     if(!c.isNull())
                     {
                         QTextBlock qtb = c.block ();
                         ltodos.append(qtb.text());
                     }

                 }

                 int position;
                         QString contenu;
                          int  ci=t.toInt();
                         for(auto& s:ltodos)
                         {
                             todo in;

                             in.setId_interation(ci);
                             position=s.toStdString().find("@date");
                             if(position>0)
                             {
                                    QString date=s.mid(position+6,s.size());
                                    std::string tmp(date.toStdString());
                                    tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
                                     QString date3="";
                                     QString sep="-";
                                     date=QString::fromStdString(tmp);
                                     date3=(((date3.append(date.mid(6,4)).append(sep)).append(date.mid(3,2)).append(sep)).append(date.mid(0,2)));
                                      contenu=s.mid(6,position-6);
                                     in.setcontenu(contenu.toStdString());
                                     const string  str= date3.toStdString();
                                     date::year_month_day d=in.conversionStringToDate(str);
                                     //in.setDate( in.conversionStringToDate((d)));

                             }
                             else
                             {
                                   contenu=s.mid(6,s.size());
                                  contenu+= " à faire maintenant";

                                     in.setcontenu(contenu.toStdString());

                             }
                             emit  sigAjoutTodo(ci,in);
                         }

                QMessageBox msgBox;
                msgBox.setText("L'intéraction  a été ajouté avec succés sur le  contact qui a pour identifiant "
                               +QString::number(inter.getIdentifiantC()));
                msgBox.exec();

        }else{
                QMessageBox::warning(this,"Ajouter une intéraction ","Impossible d'ajouter une intéraction sans voir la liste des contacts \n"
                                          "ou sans entrer un contenu \n"
                                          "veuillez afficher les contacts sur la fenetre principale avant ." );
              }
        ComboInteraction->clear();
        ui->textInteraction->clear();
        dialogInteraction->close();

}
void CRMGA::RemplirAjoutInter(const QString  &valeur)
{
    std::list<contact> lst;
    lst.clear();
    emit sigListcontact(lst);
     int val=valeur.toInt();
    for(auto &co:lst)
    {
         if(co.getIdentifiantC()==val)
         {
                     interactionText->setText(QString::fromStdString(co.getNom())+"  "+QString::fromStdString(co.getPrenom()));

         }
    }
}



//liste interaction
void CRMGA::ListeInteraction()
{
    dialogListInteraction=new QDialog();
    dialogListInteraction->setWindowTitle(tr("Liste des Interactions "));
    dialogListInteraction->setModal(true);

    VblisteInter1=new QVBoxLayout();
    VblisteInter2=new QVBoxLayout();
    HblisteInter3=new QHBoxLayout();

    //Bouton
    BvaliderlisteInteraction= new QPushButton("valider");
    BannulerlisteInteraction= new QPushButton("Annuler");

    LbListeContact=new QLabel(" Liste des Conctact ");
    Lbnom_prenom=new QLabel("nom/Prenom");
    nomp_prenom_Liste=new QLineEdit();

    VblisteInter1->addWidget(LbListeContact);
    VblisteInter2->addWidget(ComboBoxListeInteraction);

    VblisteInter1->addWidget(Lbnom_prenom);
    VblisteInter2->addWidget(nomp_prenom_Liste);

    VblisteInter1->addWidget(BvaliderlisteInteraction);
    VblisteInter2->addWidget(BannulerlisteInteraction);

    HblisteInter3->addLayout(VblisteInter1);
    HblisteInter3->addLayout(VblisteInter2);

    dialogListInteraction->setLayout(HblisteInter3);
    dialogListInteraction->show();

    connect(BvaliderlisteInteraction,SIGNAL(clicked()),this,SLOT(ListeInteractionContact()));
    connect(BannulerlisteInteraction,SIGNAL(clicked()),this,SLOT(AnnulerListeInteraction()));
    connect(ComboBoxListeInteraction,SIGNAL(currentTextChanged(const QString  & )),this,SLOT(RemplirSupInters(const QString  & )));
}

void CRMGA::ListeInteractionContact()
{
    ui->textInteraction->clear();
    QString t=ComboBoxListeInteraction->currentText();
    int  c=t.toInt();

   if(t!=NULL)
    {
        std::list<interaction> li;
        li.clear();
        emit sigListeInteraction(c,li);
         QString resultat;

         QString entete;
         entete+="idInteract |   ";
         entete+="idContact  |   ";
         entete+="dateInter  |\t  ";
         entete+=" Contenu \n\n";
         ui->textInteraction->insertPlainText(entete);
        for(auto &p:li)
        {
            resultat+=QString::number(p.getIdInteraction())+ "\t";
            resultat+=QString::number(p.getIdentifiantC())+"\t";
            resultat+=QString::fromStdString(p.conversiondateToStringI(p.getDateInteraction()))+ "\t";
            resultat+=QString::fromStdString(p.getCommentaire())+"\n";
        }

        ui->textInteraction->insertPlainText(resultat); ///insertion de l'affichage sur le textEdit dedié à l'interaction
        dialogListInteraction->close();
   }else{
        QMessageBox::warning(this,"Liste intéractions","Impossible d'afficher les intéractions d'un contact sans connaitre le nom du contact ! \n"
                                       "veuillez afficher la liste des contacts sur la fenetre principale avant");
      }


}
void CRMGA::AnnulerListeInteraction()
{
    dialogListInteraction->close();
}
void CRMGA::RemplirSupInters(const QString  &valeur )
{
    std::list<contact> lst;
    lst.clear();
    emit sigListcontact(lst);
     int val=valeur.toInt();
    for(auto &co:lst)
    {
         if(co.getIdentifiantC()==val)
         {
               nomp_prenom_Liste->setText(QString::fromStdString(co.getNom())+"  "+QString::fromStdString(co.getPrenom()));

         }
    }
}

void CRMGA::Toutes_les_interactions()
{
    ui->textInteraction->clear();
    std::list<interaction> li;
    li.clear();
    ComboBoxListeTodo->clear();
    sigListeInteractions(li);
    QString texte;
    QString inter;

    inter+="idContact  | ";
    inter+="idInteract | ";

    inter+="dateInter |   ";
    inter+=" Contenu |\n\n ";

    ui->textInteraction->insertPlainText(inter);
    for(auto &p:li)
    {

         texte+=QString::number(p.getIdInteraction())+ " \t| ";
         texte+=QString::number(p.getIdentifiantC())+ " \t| ";
         texte+=QString::fromStdString(p.conversiondateToStringI(p.getDateInteraction()))+ " \t| ";
        texte+=QString::fromStdString(p.getCommentaire())+" \t \n";

        ComboBoxListeTodo->addItem(QString::number(p.getIdInteraction()));

    }
    ListeTodos();
    ui->textInteraction->insertPlainText(texte);
}




//les requetes
void CRMGA::Interactions_deux_dates()
{
    Dialog_interactions_deux_dates = new QDialog ();
    Dialog_interactions_deux_dates->setWindowTitle("Interactions entre deux dates");
    Dialog_interactions_deux_dates->setModal(true);

    ldebut_interactions_deux_dates = new QLabel ("Date de debut :");
    lfin_interactions_deux_dates = new QLabel ("Date de fin :");
    debut_interactions_deux_dates = new QDateEdit () ;
    fin_interactions_deux_dates = new QDateEdit();
    Brechercher_interactions_deux_dates = new QPushButton ("Rechercher");
    Bannuler_interactions_deux_dates = new QPushButton ("Annuler");

    Vbligne1_interactions_deux_dates = new QVBoxLayout ();
    Vbligne2_interactions_deux_dates = new QVBoxLayout ();
    Hblignein_interactions_deux_dates = new QHBoxLayout () ;

    Vbligne1_interactions_deux_dates->addWidget(ldebut_interactions_deux_dates);
    Vbligne2_interactions_deux_dates->addWidget(debut_interactions_deux_dates);
    Vbligne1_interactions_deux_dates->addWidget(lfin_interactions_deux_dates);
    Vbligne2_interactions_deux_dates->addWidget(fin_interactions_deux_dates);
    Vbligne1_interactions_deux_dates->addWidget(Brechercher_interactions_deux_dates);
    Vbligne2_interactions_deux_dates->addWidget(Bannuler_interactions_deux_dates);

    Hblignein_interactions_deux_dates->addLayout(Vbligne1_interactions_deux_dates);
    Hblignein_interactions_deux_dates->addLayout(Vbligne2_interactions_deux_dates);

    Dialog_interactions_deux_dates->setLayout(Hblignein_interactions_deux_dates);
    Dialog_interactions_deux_dates->show();
    //connect
    connect(Brechercher_interactions_deux_dates,SIGNAL(clicked()),this,SLOT(chercher_Interactions_deux_dates()));
    connect(Bannuler_interactions_deux_dates,SIGNAL(clicked()),this,SLOT(annuler_Interactions_deux_dates()));

}
void CRMGA::annuler_Interactions_deux_dates()
{
    Dialog_interactions_deux_dates->close();
}
void CRMGA::chercher_Interactions_deux_dates()
{

    std::list<interaction> li;
    ui->textInteraction->clear();//Pour raffraichir l'affichage sur la base de donnée
    QString date1="";
    QString date2="";
    QString sep="-";

    QString tr=debut_interactions_deux_dates->text();
    date1=(((date1.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

    tr=fin_interactions_deux_dates->text();
    date2=(((date2.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

    sigRechercheInteraction(date1,date2,li);

    QString texte;
    QString inter;
    inter+="idInteract |   ";
    inter+="idContact  |   ";
    inter+="dateInter  |\t  ";
    inter+=" Contenu \n\n";
    ui->textInteraction->insertPlainText(inter);
    for(auto &p:li)
    {
       texte+=QString::number(p.getIdInteraction())+ "\t";
       texte+=QString::number(p.getIdentifiantC())+"\t";
       texte+=QString::fromStdString(p.conversiondateToStringI(p.getDateInteraction()))+ "\t";
       texte+=QString::fromStdString(p.getCommentaire())+"\n";
    }
    ui->textInteraction->insertPlainText(texte);// insertion de l'affichage sur le textEdit dedié .*/
    Dialog_interactions_deux_dates->close();
}







void CRMGA::Rechercher_Interactioncontact_deux_dates()
{
    DialogRechInterContact = new QDialog ();
    DialogRechInterContact->resize(400,100);
    DialogRechInterContact->setWindowTitle("Recherhe d'interaction d'un contact par son nom");
    DialogRechInterContact->setModal(true);

    label_nom_RechInterContact = new QLabel ("Nom/prenom :");
    nm_RechInterContact = new QLineEdit ();
    annulerRechInterContact = new QPushButton ("Annuler");
    BRechInterContact = new QPushButton ("Recherher");
    QLabel *debut = new QLabel ("Date de debut :");
    QLabel *fin =  new QLabel ("Date de fin :");
    indice_id_RechInterContact =new QLabel ("id_contact :");
    date1_RechInterContact =new QDateEdit ();
    date2_RechInterContact = new QDateEdit();

    Vbligne1RechInterContact = new QVBoxLayout ();
    Vbligne2RechInterContact = new QVBoxLayout ();
    Hbligne3RechInterContact = new QHBoxLayout ();
    Vbligne1RechInterContact->addWidget(indice_id_RechInterContact);
    Vbligne2RechInterContact->addWidget(Combo_RechInterContact);
    Vbligne1RechInterContact->addWidget(label_nom_RechInterContact);
    Vbligne2RechInterContact->addWidget(nm_RechInterContact);
    //Vbligne2RechInterContact->addWidget(Combo_RechInterContact);
    Vbligne1RechInterContact->addWidget(debut);
    Vbligne2RechInterContact->addWidget(date1_RechInterContact);
    Vbligne1RechInterContact->addWidget(fin);
    Vbligne2RechInterContact->addWidget(date2_RechInterContact);
    Vbligne1RechInterContact->addWidget(annulerRechInterContact);
    Vbligne2RechInterContact->addWidget(BRechInterContact);
    Hbligne3RechInterContact->addLayout(Vbligne1RechInterContact);
    Hbligne3RechInterContact->addLayout(Vbligne2RechInterContact);

    DialogRechInterContact->setLayout(Hbligne3RechInterContact);
    DialogRechInterContact->show();
    //connect

    connect(annulerRechInterContact,SIGNAL(clicked()),this,SLOT(Bouton_annuler_RechInterContact()));
    connect(BRechInterContact,SIGNAL(clicked()),this,SLOT(Bouton_RechInterContact()));
    connect(Combo_RechInterContact,SIGNAL(currentTextChanged(const QString  & )),this,SLOT(remplir_comboRechInterContact(const QString &)));

}

void CRMGA::Bouton_annuler_RechInterContact()
{
    DialogRechInterContact->close();
}
void CRMGA::Bouton_RechInterContact()
{
    std::list<interaction> li;
    ui->textInteraction->clear();

    QString date1="";
    QString date2="";
    QString sep="-";
    QString tr=date1_RechInterContact->text();
    date1=(((date1.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

    tr=date2_RechInterContact->text();
    date2=(((date2.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));
    QString t=Combo_RechInterContact->currentText();
    int  c=t.toInt();

    sigRechercheInteractionContact(c ,date1 ,date2 ,li);
    Combo_RechInterContact->clear();
    QString texte;
    QString inter;
    inter+="idInteract |   ";
    inter+="idContact  |   ";
    inter+="dateInter  |\t  ";
    inter+=" Contenu \n\n";
    ui->textInteraction->insertPlainText(inter);
    for(auto &p:li)
   {
      texte+=QString::number(p.getIdInteraction())+ "  |  ";
      texte+=QString::number(p.getIdentifiantC())+"  |  ";
      texte+=QString::fromStdString(p.conversiondateToStringI(p.getDateInteraction()))+ "  |  ";
      texte+=QString::fromStdString(p.getCommentaire())+"\n";
   }
   ui->textInteraction->insertPlainText(texte);
   DialogRechInterContact->close();
}

void CRMGA::remplir_comboRechInterContact(const QString &valeur)
{
    std::list<contact> lst;
    lst.clear();
    emit sigListcontact(lst);
     int val=valeur.toInt();
    for(auto &co:lst)
    {
         if(co.getIdentifiantC()==val)
         {
                     nm_RechInterContact->setText(QString::fromStdString(co.getNom())+"  "+QString::fromStdString(co.getPrenom()));

         }
    }
}


void CRMGA::Todo_deux_dates()
{
    Dialog_todo_deux_dates = new QDialog ();
    Dialog_todo_deux_dates->setWindowTitle("Taches entre deux dates");
    Dialog_todo_deux_dates->setModal(true);

    ldebut_todo_deux_dates = new QLabel ("Date de debut :");
    lfin_todo_deux_dates = new QLabel ("Date de fin :");
    debut_todo_deux_dates = new QDateEdit () ;
    fin_todo_deux_dates = new QDateEdit();
    Brechercher_todo_deux_dates = new QPushButton ("Rechercher");
    Bannuler_todo_deux_dates = new QPushButton ("Annuler");

    Vbligne1_todo_deux_dates = new QVBoxLayout ();
    Vbligne2_todo_deux_dates = new QVBoxLayout ();
    Hblignein_todo_deux_dates = new QHBoxLayout () ;

    Vbligne1_todo_deux_dates->addWidget(ldebut_todo_deux_dates);
    Vbligne2_todo_deux_dates->addWidget(debut_todo_deux_dates);
    Vbligne1_todo_deux_dates->addWidget(lfin_todo_deux_dates);
    Vbligne2_todo_deux_dates->addWidget(fin_todo_deux_dates);
    Vbligne1_todo_deux_dates->addWidget(Brechercher_todo_deux_dates);
    Vbligne2_todo_deux_dates->addWidget(Bannuler_todo_deux_dates);

    Hblignein_todo_deux_dates->addLayout(Vbligne1_todo_deux_dates);
    Hblignein_todo_deux_dates->addLayout(Vbligne2_todo_deux_dates);

    Dialog_todo_deux_dates->setLayout(Hblignein_todo_deux_dates);
    Dialog_todo_deux_dates->show();
    //connect
    connect(Brechercher_todo_deux_dates,SIGNAL(clicked()),this,SLOT(chercher_Todo_deux_dates()));
    connect(Bannuler_todo_deux_dates,SIGNAL(clicked()),this,SLOT(annuler_Todo_deux_dates()));

}
void CRMGA::annuler_Todo_deux_dates()
{
    Dialog_todo_deux_dates->close();
}
void CRMGA::chercher_Todo_deux_dates()
{
    std::list<todo> lt;
    lt.clear();
    ui->textTodo->clear();
    QString date1="";
    QString date2="";
    QString sep="-";

   QString tr=debut_todo_deux_dates->text();
   date1=(((date1.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

   tr=fin_todo_deux_dates->text();
   date2=(((date2.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

   emit  sigRechercheTodos( date1,date2,lt);
   QString texte;
   QString tache;
   tache+="idTodo    | ";
   tache+="idIntera  | ";
   tache+=" ContenuTodo | ";
   tache+="  dateTodo\n\n";
   ui->textTodo->insertPlainText(tache);

   for(auto &t:lt)
     {

      texte+=QString::number(t.getIid_todo())+ "\t";
      texte+=QString::number(t.getId_interation())+"\t";
      texte+=QString::fromStdString(t.conversiondateToString(t.getDate()))+"\t";
      texte+=QString::fromStdString(t.getcontenu())+"\n";

  }
  ui->textTodo->insertPlainText(texte); /*!< insertion de l'affichage sur le textEdit dedié .*/
  Dialog_todo_deux_dates->close();

}


void CRMGA::Todo_contact_deux_dates()
{
    dialogListTodo=new QDialog();
    dialogListTodo->resize(400,10);
    dialogListTodo->setWindowTitle(tr("Liste des Taches "));
    dialogListTodo->setModal(true);

    VblisteTodo1=new QVBoxLayout();
    VblisteTodo2=new QVBoxLayout();
    HblisteTodo3=new QHBoxLayout();

    //Bouton
    BvaliderlisteTodo= new QPushButton("Recherher");
    BannulerlisteTodo= new QPushButton("Annuler");

    LbListeTodoContact=new QLabel(" Liste des Conctact ");
    LbTodonom_prenom=new QLabel("Debut :");
    QLabel *Tfin =new QLabel ("Fin :");
    debut_todocontact_deux_dates =new QDateEdit ();
    fin_todocontact_deux_dates =new QDateEdit ();

    VblisteTodo1->addWidget(LbListeTodoContact);
    VblisteTodo2->addWidget(ComboBoxListeTodo);

    VblisteTodo1->addWidget(LbTodonom_prenom);
    VblisteTodo2->addWidget(debut_todocontact_deux_dates);
    VblisteTodo1->addWidget(Tfin);
    VblisteTodo2->addWidget(fin_todocontact_deux_dates);

    VblisteTodo1->addWidget(BvaliderlisteTodo);
    VblisteTodo2->addWidget(BannulerlisteTodo);

    HblisteTodo3->addLayout(VblisteInter1);
    HblisteTodo3->addLayout(VblisteInter2);

    dialogListTodo->setLayout(HblisteTodo3);
    dialogListTodo->show();

    connect(BvaliderlisteTodo,SIGNAL(clicked()),this,SLOT(chercher_Todocontact_deux_dates()));
    connect(BannulerlisteTodo,SIGNAL(clicked()),this,SLOT(annuler_Todocontact_deux_dates()));

}
void CRMGA::annuler_Todocontact_deux_dates()
{
    dialogListTodo->close();
}
void CRMGA::chercher_Todocontact_deux_dates()
{
    ui->textTodo->clear();
    ComboBoxListeTodo->clear();
    QString date1="";
    QString date2="";
    QString sep="-";
    QString t=ComboBoxListeTodo->currentText();
    int  c=t.toInt();

    if(t!=NULL)
       {

            QString tr=debut_todocontact_deux_dates->text();
            date1=(((date1.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));
            tr=fin_todocontact_deux_dates->text();
            date2=(((date2.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));
            std::list<todo> lt;
            lt.clear();
            emit sigRechercheTodoCont(c , date1 , date2 , lt);
            QString texte;
            QString Tache;
            Tache+="idTodo    | ";
            Tache+="idIntera  | ";
            Tache+=" ContenuTodo | ";
            Tache+="  dateTodo\n\n";
            ui->textTodo->insertPlainText(Tache);
            for(auto &t:lt)
            {
                texte+=QString::number(t.getIid_todo())+ "\t";
                texte+=QString::number(t.getId_interation())+"\t";
                texte+=QString::fromStdString(t.conversiondateToString(t.getDate()))+ "\t";
                texte+=QString::fromStdString(t.getcontenu())+"\n";

            }

            ui->textTodo->insertPlainText(texte);

       }

   else
       {
            QMessageBox::warning(this,"Todo entre deux dates ",
            "Impossible de faire la récherche sans voir la liste des contacts");
       }

    dialogListTodo->close();
}

//les boutons
void CRMGA::afficheListeContacts()
{
    std::list<contact> lst;
    ui->CentreText->clear();//raffraichier le textEdit
    emit sigListcontact(lst);//envoi du signal qu'on liera dans le main avec la BD
   /* for (auto &co: lst) {
       ui->CentreText->insertPlainText(QString::fromStdString(co.getNom()));}*/
    ComboModif->clear();//on efface tous les id contenues au paravant
    ComboSupp->clear();
    ComboInteraction->clear();
    ComboBoxListeInteraction->clear();
    Combo_RechInterContact->clear();
    ComboBoxListeTodo->clear();
    QString resultat, entete;
    entete = "id_contact \t";
    entete +="Nom \t";
    entete += "Prenom \t";
    entete +="Email \t";
    entete += "entreprise \t";
    entete +="Téléphone \t";
    entete +="Photo \t";
    entete +="Date\n\n";
      ui->CentreText->insertPlainText(entete);
    //on affiche la liste des contacts recuperée
    for (auto &co: lst) {contact c;
        resultat+=QString::number(co.getIdentifiantC()) +"\t";
        resultat+=QString::fromStdString(co.getNom())+"\t";
        resultat+=QString::fromStdString(co.getPrenom())+"\t";
        resultat+=QString::fromStdString(co.getEmail())+"\t";
        resultat+=QString::fromStdString(co.getNomEntreprise())+"\t";
        resultat+=QString::fromStdString(co.getTelephone())+"\t";
        resultat+=QString::fromStdString(co.getPhoto())+"\t";
        resultat+=QString::fromStdString(co.conversiondateToString(co.getdateContct())) +"\n";
        ComboModif->addItem(QString::number(co.getIdentifiantC()));//on remet les nouvelles id
        ComboSupp->addItem(QString::number(co.getIdentifiantC()));//
        ComboInteraction->addItem(QString::number(co.getIdentifiantC()));
        ComboBoxListeInteraction->addItem(QString::number(co.getIdentifiantC()));
        Combo_RechInterContact->addItem(QString::number((co.getIdentifiantC())));
        ComboBoxListeTodo->addItem(QString::number((co.getIdentifiantC())));
    }
    ui->CentreText->insertPlainText(resultat);
    qDebug()<<"tout va bien";
}

void CRMGA::affichListeInteraction()
{
    ui->textInteraction->clear();
    std::list<interaction> li;
    li.clear();
    ComboBoxListeTodo->clear();
    emit sigListeInteractions(li);

    QString texte;
    QString inter;

    inter+="id_Interaction |";
    inter+="id_contact |";

    inter+="dateInter |   ";
    inter+=" Contenu |\n\n ";

    ui->textInteraction->insertPlainText(inter);
    for(auto &p:li)
    {

         texte+=QString::number(p.getIdInteraction())+ " \t| ";
         texte+=QString::number(p.getIdInteraction())+ " \t| ";
         texte+=QString::fromStdString(p.conversiondateToStringI(p.getDateInteraction()))+ " \t| ";
        texte+=QString::fromStdString(p.getCommentaire())+" \t \n";

        ComboBoxListeTodo->addItem(QString::number(p.getIdInteraction()));

    }
    ListeTodos();
    ui->textInteraction->insertPlainText(texte);
}

void CRMGA::ListeTodos()
{
    std::list<todo> li;
    li.clear();
    emit  sigListeTodos(li);
    ui->textTodo->clear();
    QString texte;
    QString daTeInverse;//variable qui inverse la valeur
    int position;
    QString Tache;
    //Tach+="idTodo    | ";
   Tache+="idIntera  | ";
   Tache+=" ContenuTodo | ";
    Tache+="  dateTodo\n\n";
    ui->textTodo->insertPlainText(Tache);
    for(auto &p:li)
     {
        position=p.getcontenu().find("à faire maintenant");// verifier si la tache est urgente ou pas avec la fonction find */
        daTeInverse=QString::fromStdString(p.conversiondateToString(p.getDate()));
       // texte+=QString::number(p.getIdtodo())+ "\t";
        texte+=QString::number(p.getId_interation())+"\t";

    if(position>0)
     {
        texte+=" @todo "+QString::fromStdString(p.getcontenu())+"\n"; // pour pouvoir faire le tag avec @todo*/
     }
    else{
            //recuperer la  date du todo en chaine de caractere
         QString date="";
         QString sep="/";
         date=(((date.append(daTeInverse.mid(8,2)).append(sep)).append(daTeInverse.mid(5,2)).append(sep)).append(daTeInverse.mid(0,4)));/*!< Inversion de la date de jj/mm/aaaa vers aaaa-mm-jj afin de pouvoir l'insérer dans la base */
         texte+=" @todo "+QString::fromStdString(p.getcontenu())+" @date "+date+"\n";// pour pouvoir faire le tag avec @date*/

        }

    }
        ui->textTodo->insertPlainText(texte);
}


void CRMGA::apropos()
{
    QMessageBox::information(this, "Apropos de notre Projet CDAA",
                             " On a developpé cette applilcation QT (c++) en faisant \n"
                             "  dialoguer l'application et une base de donnée SQL .\n"
                             " Ce projet est fait  par  \n"
                             " ALMOUNTASSIR ABDEL-AZIZ \n"
                             "&\n"
                             " MAMADOU GACKOU \n"
                             "du Groupe G !\n\n"
                             "Professeur: Monsieur Raffin Romain \n"
                             "Professeur chargé de TP: Monsieur Mohammed Lalou .");

}






void CRMGA::Jsoncontact()
{
    std::list<contact> lp;//Déclaration d'une liste
    bd.slotAfficheListeContact(lp);//on récupère la liste de contact dans la base de donnée .
    QJsonArray table;//on crée une table

 int ret=QMessageBox::information(0,"Exporter en Json","Voulez vous exporter les contacts en fichier "
                                                     "Json ",QMessageBox::Cancel | QMessageBox::Ok);

if(ret==QMessageBox::Ok)
 {
   for(auto &p:lp)
    {
         QJsonObject obj ;
         obj.insert("Nom",QString::fromStdString(p.getNom()));
         obj.insert("Prenom",QString::fromStdString(p.getPrenom()));
         obj.insert("Entreprise",QString::fromStdString(p.getNomEntreprise()));
         obj.insert("Telephone",QString::fromStdString(p.getTelephone()));
         obj.insert("Mail",QString::fromStdString(p.getEmail()));
         obj.insert("Photo ",QString::fromStdString(p.getPhoto()));
         obj.insert("Date de création",QString::fromStdString(p.conversiondateToString(p.getdateContct())));
         table.append(obj);//ajout de l'objet dans la table

     }
    QJsonDocument document(table);
    QByteArray bytes=document.toJson();

    QFile file("C:/Users/almou/Desktop/CDAA/CRM1/contact.json");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text ))
       return;
    QTextStream out(&file);
    out.setCodec("UTF-8");
        out<<bytes;

 }
}

void  CRMGA::JsonInteraction()
{
    std::list<interaction> inter;//Déclaration d'une liste
    interbd.slotListeInteraction(inter);//on récupère la liste de contact dans la base de donnée .
    QJsonArray table;//on crée une table

 int ret=QMessageBox::information(0,"Exporter en Json","Voulez vous exporter les intéractions en fichier "
                                                     "Json ",QMessageBox::Cancel | QMessageBox::Ok);

if(ret==QMessageBox::Ok)
 {
   for(auto &p:inter)
    {
        QJsonObject obj ;
        obj.insert("Date de création",QString::fromStdString(p.conversiondateToStringI(p.getDateInteraction())));
        obj.insert("Contenu",QString::fromStdString(p.getCommentaire()));
        table.append(obj);//ajout de l'objet dans la table
   }
    QJsonDocument document(table);
    QByteArray bytes=document.toJson();

    QFile file("C:/Users/almou/Desktop/CDAA/CRM1/Interaction.json");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text ))
       return;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<bytes;

 }

}
