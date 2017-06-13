#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QTime>
#include <QDate>
#include <QListWidget>
#include <QMessageBox>

MainWindow::MainWindow(QString qsID,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_qsID = qsID;
    loadEmployer();
    loadRayon();
    loadPdv();
    loadVisite();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadEmployer()
{
    qDebug()<<"MainWindow::loadEmployer()"<<endl;

    QSqlQuery reqLoadEmployer("SELECT nom,prenom,username FROM Personnel WHERE supprime <> 1");
    ui->listWidgetPersonnels->clear();

    while(reqLoadEmployer.next())
    {

        QString qsNom = reqLoadEmployer.value(0).toString();
        QString qsPrenom = reqLoadEmployer.value(1).toString();
        QString qsLogin = reqLoadEmployer.value(2).toString();
        QListWidgetItem *Item = new QListWidgetItem(qsNom + " " + qsPrenom);
        Item->setData(32,qsLogin);
        //qDebug()<<Item->data(32).toString()<<endl;

        ui->listWidgetPersonnels->addItem(Item);

    }


}

void MainWindow::loadPdv()
{
    qDebug()<<"MainWindow::loadPdv()"<<endl;

    QSqlQuery reqLoadPdvV("SELECT no_pdv,nom FROM pointdevente WHERE valide = 1");
    QSqlQuery reqLoadPdvNV("SELECT no_pdv,nom FROM pointdevente WHERE valide = 0");
    ui->listWidgetPdvNonValide->clear();
    ui->listWidgetPdvValide->clear();

    while(reqLoadPdvV.next())
    {

        QString qsId = reqLoadPdvV.value(0).toString();
        QString qsNom = reqLoadPdvV.value(1).toString();
        QListWidgetItem *Item = new QListWidgetItem(qsNom);
        Item->setData(32,qsId);
        //qDebug()<<Item->data(32).toString()<<endl;

        ui->listWidgetPdvValide->addItem(Item);

    }
    while(reqLoadPdvNV.next())
    {

        QString qsId = reqLoadPdvNV.value(0).toString();
        QString qsNom = reqLoadPdvNV.value(1).toString();
        QListWidgetItem *Item = new QListWidgetItem(qsNom);
        Item->setData(32,qsId);
        //qDebug()<<Item->data(32).toString()<<endl;

        ui->listWidgetPdvNonValide->addItem(Item);

    }


}

void MainWindow::loadVisite()
{
    qDebug()<<"MainWindow::loadVisite()"<<endl;

    QSqlQuery reqLoadControleur("SELECT numeroPersonnel,nom,prenom FROM Personnel WHERE typePersonnel = 'Controleur'");
    QSqlQuery reqLoadPdv("SELECT identifiant,pseudo FROM utilisateur WHERE id_typeUtilisateur = 2 OR id_typeUtilisateur = 3");
    ui->listWidgetAffectationC->clear();
    ui->listWidgetPdvC->clear();

    while(reqLoadControleur.next())
    {

        QString qsId = reqLoadControleur.value(0).toString();
        QString qsNom = reqLoadControleur.value(1).toString();
        QString qsPrenom = reqLoadControleur.value(2).toString();
        QListWidgetItem *Item = new QListWidgetItem(qsNom + " " + qsPrenom);
        Item->setData(32,qsId);
        //qDebug()<<Item->data(32).toString()<<endl;

        ui->listWidgetAffectationC->addItem(Item);

    }
    while(reqLoadPdv.next())
    {

        QString qsId = reqLoadPdv.value(0).toString();
        QString qsNom = reqLoadPdv.value(1).toString();
        QListWidgetItem *Item = new QListWidgetItem(qsNom);
        Item->setData(32,qsId);
        //qDebug()<<Item->data(32).toString()<<endl;

        ui->listWidgetPdvC->addItem(Item);

    }


}

void MainWindow::loadRayon()
{
    qDebug()<<"MainWindow::loadRayon()"<<endl;

    QSqlQuery reqLoadRayon("SELECT no_rayon,libelle FROM rayon");
    ui->listWidgetRayon->clear();

    while(reqLoadRayon.next())
    {

        QString qsNoRayon = reqLoadRayon.value(0).toString();
        QString qsNom = reqLoadRayon.value(1).toString();
        QListWidgetItem *Item = new QListWidgetItem(qsNom);
        Item->setData(32,qsNoRayon);
        //qDebug()<<Item->data(32).toString()<<endl;

        ui->listWidgetRayon->addItem(Item);

    }


}

void MainWindow::on_butAdd_clicked()
{
    qDebug()<<"void MainWindow::on_butAdd_clicked()"<<endl;

    QDate dateInscription;
    QString qsDateInscription = dateInscription.currentDate().toString("yyyy-MM-dd");
    QString qsPseudo = ui->lineEditPseudo->text();
    QString qsNom = ui->lineEditNom->text();
    QString qsMDP = GetRandomString();
    QString qsPrenom = ui->lineEditPrenom->text();
    QString qsTelFixe = ui->lineEditTelFixe->text();
    QString qsTelPort = ui->lineEditTelPort->text();
    QString qsMail = ui->lineEditMail->text();
    QString qsAdresse = ui->lineEditAdresse->text();
    QString qsCP = ui->lineEditCP->text();
    QString qsVille = ui->lineEditVille->text();
    QString qsIban = ui->lineEditIban->text();
    QString qsTypeUser;
    QString qsEtatValidation = "1";

    QString qsIdPersonnel("SELECT MAX(numeroPersonnel)+1 FROM Personnel");
    QSqlQuery reqRecupID(qsIdPersonnel);
    QString noPersonnelId;

    if(reqRecupID.first())
    {
        qDebug()<<"C'est OK"<<endl;
        noPersonnelId = reqRecupID.value(0).toString();
        qDebug()<<noPersonnelId<<endl;
    } else {
        qDebug()<<"C'est pas OK"<<endl;
        noPersonnelId = "1";
    }

    if(ui->radioButtonController->isChecked())
    {
        qsTypeUser = "Controleur";
    }

    if(ui->radioButtonManager->isChecked())
    {
        qsTypeUser = "Gestionnaire";
    }

    QString qsReqInsert("INSERT INTO Personnel(numeroPersonnel,username,mdp,nom,prenom,tel_fixe,tel_portable,email,adresse,code_postal,ville,typePersonnel,iban,valide,date_Embauche) VALUES ('");
    qsReqInsert += noPersonnelId +"', '";
    qsReqInsert += qsPseudo +"', '";
    qsReqInsert += qsMDP +"', '";
    qsReqInsert += qsNom +"', '";
    qsReqInsert += qsPrenom +"', '";
    qsReqInsert += qsTelFixe +"', '";
    qsReqInsert += qsTelPort +"', '";
    qsReqInsert += qsMail +"', '";
    qsReqInsert += qsAdresse +"', '";
    qsReqInsert += qsCP +"', '";
    qsReqInsert += qsVille +"', '";
    qsReqInsert += qsTypeUser +"', '";
    qsReqInsert += qsIban +"', '";
    qsReqInsert += qsEtatValidation +"', '";
    qsReqInsert += qsDateInscription +"')";

    QSqlQuery reqInsert(qsReqInsert);

    if(reqInsert.exec())
    {
        qDebug()<<"Ajout à la base"<<endl;
    }
    else
    {
        //qDebug()<<qsReqInsert<<endl;
        statusBar()->showMessage("Erreur : Le contact n'a pas été ajouté !");
    }


    loadEmployer();

}

QString MainWindow::GetRandomString() const
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int randomStringLength = 12;

    QTime time;
    qsrand(time.currentTime().msec());
    QString randomString;
    for(int i=0; i<randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

void MainWindow::on_butDel_clicked()
{
    qDebug()<<"void MainWindow::on_butDel_clicked()"<<endl;

    if(ui->listWidgetPersonnels->currentItem())
    {
        QString qsPseudo = ui->listWidgetPersonnels->currentItem()->data(32).toString();
        QString qsReqDel("UPDATE Personnel SET supprime = 1 WHERE username = '" +qsPseudo+ "'");

        int ret = QMessageBox::question(this,tr("GestContact"),tr("Souhaitez vous supprimer ce membre du personnel ?"),
                                        QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            QSqlQuery reqDel(qsReqDel);
        }

        loadEmployer();
    }

}

void MainWindow::on_listWidgetPersonnels_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"MainWindow::on_listWidgetPersonnels_currentRowChanged(int currentRow)"<<endl;


    QString qsEmployer = ui->listWidgetPersonnels->currentItem()->text();
    QStringList list = qsEmployer.split(" ");
    QString qsPrenom = list.value(1);
    QString qsNom = list.value(0);
    QString qsLogin = ui->listWidgetPersonnels->currentItem()->data(32).toString();

    QString qsReq("SELECT username, nom, prenom, tel_fixe, tel_portable, email, adresse, code_postal, ville, typePersonnel, iban FROM Personnel WHERE nom = '" + qsNom + "' AND prenom = '" + qsPrenom + "' AND username = '" + qsLogin +"'");
    QSqlQuery reqLoadInfo(qsReq);

    //qDebug()<<qsReq<<endl<<qsLogin<<endl;

    if(reqLoadInfo.first())
    {
        ui->lineEditPseudo->setText(reqLoadInfo.value(0).toString());
        ui->lineEditNom->setText(reqLoadInfo.value(1).toString());
        ui->lineEditPrenom->setText(reqLoadInfo.value(2).toString());
        ui->lineEditTelFixe->setText(reqLoadInfo.value(3).toString());
        ui->lineEditTelPort->setText(reqLoadInfo.value(4).toString());
        ui->lineEditMail->setText(reqLoadInfo.value(5).toString());
        ui->lineEditAdresse->setText(reqLoadInfo.value(6).toString());
        ui->lineEditCP->setText(reqLoadInfo.value(7).toString());
        ui->lineEditVille->setText(reqLoadInfo.value(8).toString());
        ui->lineEditIban->setText(reqLoadInfo.value(10).toString());

        if(reqLoadInfo.value(9).toString() == "controleur")
        {
            ui->radioButtonController->setChecked(true);
        }
        else if(reqLoadInfo.value(9).toString() == "gestionnaire")
        {
            ui->radioButtonManager->setChecked(true);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_clicked() ResetPassword"<<endl;

    if(ui->listWidgetPersonnels->currentItem())
    {
        QString qsLogin = ui->listWidgetPersonnels->currentItem()->data(32).toString();
        QString qsReqInfo = "select nom, prenom from employer where login ='" + qsLogin + "'";
        QSqlQuery reqInfo = qsReqInfo;
        QString qsNom;
        QString qsPrenom;
        //qDebug()<<qsReqInfo<<endl;
        if(reqInfo.first())
        {
            qsNom = reqInfo.value(0).toString();
            qsPrenom = reqInfo.value(1).toString();

        }

        int ret = QMessageBox::question(this,"GestContact","Souhaitez vous modifier le mot de passe de "+ qsNom +" " + qsPrenom + " ? ",
                                        QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            QString qsMdp = GetRandomString();
            QString qsReqMdp = "UPDATE Personnel SET mdp = '" + qsMdp + "' WHERE username = '" + qsLogin +"'";

            //qDebug()<<qsReqMdp<<endl;
            QSqlQuery reqMdp = qsReqMdp;

            if(reqMdp.exec())
            {
                statusBar()->showMessage("Le mot de passe de "+ qsNom + " " +qsPrenom + " à été modifié !" );
            }

        }

    }
}

void MainWindow::on_butUpdate_clicked()
{
    if(ui->listWidgetPersonnels->currentItem())
    {
        QString qsId = ui->listWidgetPersonnels->currentItem()->data(32).toString();

        QString qsPseudo = ui->lineEditPseudo->text();
        QString qsNom = ui->lineEditNom->text();
        QString qsPrenom = ui->lineEditPrenom->text();
        QString qsTelFixe = ui->lineEditTelFixe->text();
        QString qsTelPort = ui->lineEditTelPort->text();
        QString qsMail = ui->lineEditMail->text();
        QString qsAdresse = ui->lineEditAdresse->text();
        QString qsCP = ui->lineEditCP->text();
        QString qsVille = ui->lineEditVille->text();
        QString qsTypeUser;
        QString qsIban = ui->lineEditIban->text();

        if(ui->radioButtonController->isChecked())
        {
            qsTypeUser = "Controleur";
        }

        if(ui->radioButtonManager->isChecked())
        {
            qsTypeUser = "Gestionnaire";
        }
        int ret = QMessageBox::question(this,"Personnel","Vous allez modifié : "+ qsNom +" " + qsPrenom,
                                        QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            QString qsReqMAJ = "UPDATE Personnel SET username = '" + qsPseudo + "', nom = '"+ qsNom +"', prenom = '"+ qsPrenom +"', tel_fixe = '"+qsTelFixe+"', tel_portable = '"+qsTelPort+"', email = '"+qsMail+"', adresse = '"+qsAdresse+"', code_postal = '"+qsCP+"', ville = '"+qsVille+"', typePersonnel = '"+qsTypeUser+"', iban = '"+qsIban+"'" +" WHERE numeroPersonnel = '" + qsId +"'";
            QSqlQuery reqMaj(qsReqMAJ);


            if(reqMaj.exec())
            {
                statusBar()->showMessage("Personnel : "+ qsNom + " " +qsPrenom + " à été modifié !" );
            }

        }
        loadEmployer();
    }
}

void MainWindow::on_listWidgetRayon_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"MainWindow::on_listWidgetRayon_itemClicked(QListWidgetItem *item)"<<endl;

    QString qsNumero = ui->listWidgetRayon->currentItem()->data(32).toString();

    QString qsReq("SELECT libelle FROM rayon WHERE no_rayon = " + qsNumero);
    QSqlQuery reqLoadInfo(qsReq);

    //qDebug()<<qsReq<<endl<<qsLogin<<endl;

    if(reqLoadInfo.first())
    {
        ui->lineEditNomRayon->setText(reqLoadInfo.value(0).toString());
    }

    qDebug()<<"Chargement de la liste : Catégorie"<<endl;

    QSqlQuery reqLoadCategorie("SELECT no_categorie,libelle FROM categorie WHERE no_rayon = " + qsNumero);
    ui->listWidgetCategorie->clear();
    ui->listWidgetProduit->clear();
    ui->lineEditNomProduit->clear();
    while(reqLoadCategorie.next())
    {

        QString qsNoCategorie = reqLoadCategorie.value(0).toString();
        QString qsNomCategorie = reqLoadCategorie.value(1).toString();
        QListWidgetItem *Item = new QListWidgetItem(qsNomCategorie);
        Item->setData(32,qsNoCategorie);

        ui->listWidgetCategorie->addItem(Item);

    }
}

void MainWindow::on_listWidgetProduit_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"MainWindow::on_listWidgetProduit_itemClicked(QListWidgetItem *item)"<<endl;

    QString qsNumeroProduit = ui->listWidgetProduit->currentItem()->data(32).toString();

    QString qsReqProduit("SELECT libelle FROM produit WHERE numero = " + qsNumeroProduit);
    QSqlQuery reqLoadInfoProduit(qsReqProduit);

    //qDebug()<<qsReq<<endl<<qsLogin<<endl;

    if(reqLoadInfoProduit.first())
    {
        ui->lineEditNomProduit->setText(reqLoadInfoProduit.value(0).toString());
    }
}

void MainWindow::on_listWidgetCategorie_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"MainWindow::on_listWidgetCategorie_itemClicked(QListWidgetItem *item)"<<endl;

    QString qsNumero = ui->listWidgetCategorie->currentItem()->data(32).toString();

    QString qsReq("SELECT libelle FROM categorie WHERE no_categorie = " + qsNumero);
    QSqlQuery reqLoadInfo(qsReq);

    //qDebug()<<qsReq<<endl<<qsLogin<<endl;

    if(reqLoadInfo.first())
    {
        ui->lineEditNomCategorie->setText(reqLoadInfo.value(0).toString());
    }

    qDebug()<<"Chargement de la liste : Produit"<<endl;

    QSqlQuery reqLoadProduit("SELECT numero,libelle FROM produit WHERE no_categorie = " + qsNumero);
    ui->listWidgetProduit->clear();

    while(reqLoadProduit.next())
    {

        QString qsNoProduit = reqLoadProduit.value(0).toString();
        QString qsNomProduit = reqLoadProduit.value(1).toString();
        QListWidgetItem *Item = new QListWidgetItem(qsNomProduit);
        Item->setData(32,qsNoProduit);

        ui->listWidgetProduit->addItem(Item);

    }
}

void MainWindow::on_pushButtonAddRayon_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonAddRayon_clicked()"<<endl;

    QString qsNomRayon = ui->lineEditNomRayon->text();

    QString qsIdRayon("SELECT MAX(no_rayon)+1 FROM rayon");
    QSqlQuery reqRecupID(qsIdRayon);
    QString noRayonId;

    if(reqRecupID.first())
    {
        qDebug()<<"C'est OK"<<endl;
        noRayonId = reqRecupID.value(0).toString();
        qDebug()<<noRayonId<<endl;
    } else {
        qDebug()<<"C'est pas OK"<<endl;
        noRayonId = "1";
    }

    QString qsReqInsertRayon("INSERT INTO rayon(no_rayon,libelle) VALUES ('");
    qsReqInsertRayon += noRayonId +"', '";
    qsReqInsertRayon += qsNomRayon +"')";

    QSqlQuery reqInsertRayon(qsReqInsertRayon);

    if(reqInsertRayon.exec())
    {
        qDebug()<<"Ajout à la base"<<endl;
    }
    else
    {
        //qDebug()<<qsReqInsert<<endl;
        statusBar()->showMessage("Erreur : Le rayon n'a pas été ajouté !");
    }


    loadRayon();
}

void MainWindow::on_listWidgetPdvValide_itemClicked(QListWidgetItem *item)
{


    qDebug()<<"MainWindow::on_listWidgetPdvValide_itemClicked(int currentRow)"<<endl;


    QString qsPdvV = ui->listWidgetPdvValide->currentItem()->text();
    QString qsId = ui->listWidgetPdvValide->currentItem()->data(32).toString();

    QString qsReq("SELECT  nom, adresse, codePostal, activite, ville, tel, responsable, valide FROM pointdevente WHERE nom = '" + qsPdvV + "' AND no_pdv = '" + qsId +"'");
    QSqlQuery reqLoadInfo(qsReq);

    if(reqLoadInfo.first())
    {
        ui->lineEditPdvNom->setText(reqLoadInfo.value(0).toString());
        ui->lineEditPdvAdresse->setText(reqLoadInfo.value(1).toString());
        ui->lineEditPdvCP->setText(reqLoadInfo.value(2).toString());
        ui->lineEditPdvActivite->setText(reqLoadInfo.value(3).toString());
        ui->lineEditPdvVille->setText(reqLoadInfo.value(4).toString());
        ui->lineEditPdvTel->setText(reqLoadInfo.value(5).toString());

        if(reqLoadInfo.value(7).toString() == "0")
        {
            ui->radioButtonValideNon->setChecked(true);
        }
        else if(reqLoadInfo.value(7).toString() == "1")
        {
            ui->radioButtonValideOui->setChecked(true);
        }
    }
}

void MainWindow::on_butAdd_2_clicked()
{
    if(ui->listWidgetPdvValide->currentItem())
    {
        QString qsIdCurrent = ui->listWidgetPdvValide->currentItem()->data(32).toString();
        QString qsValide;
        QString qsNom = ui->lineEditPdvNom->text();
        QString qsAdresse = ui->lineEditPdvAdresse->text();
        QString qsCodePostal = ui->lineEditPdvCP->text();
        QString qsTel = ui->lineEditPdvTel->text();
        QString qsActivite = ui->lineEditPdvActivite->text();
        QString qsVille = ui->lineEditPdvVille->text();


        if(ui->radioButtonValideOui->isChecked())
        {
            qsValide = "1";
        }

        if(ui->radioButtonValideNon->isChecked())
        {
            qsValide = "0";
        }
        // suite ici pour la prochaine fois
        //QString qsReqUP = "update employer set login = '" + qsPseudo + "'"+ " mdp = '"+ +"' nom = '"+ +"' prenom = '"+ +"'" +" where login = '" + qsLoginCurrent +"'";

    }
}

void MainWindow::on_listWidgetPdvNonValide_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"MainWindow::on_listWidgetPdvNonValide_itemClicked(int currentRow)"<<endl;


    QString qsPdvV = ui->listWidgetPdvNonValide->currentItem()->text();
    QString qsId = ui->listWidgetPdvNonValide->currentItem()->data(32).toString();

    QString qsReq("SELECT  nom, adresse, codePostal, activite, ville, tel, responsable, valide FROM pointdevente WHERE nom = '" + qsPdvV + "' AND no_pdv = '" + qsId +"'");
    QSqlQuery reqLoadInfo(qsReq);

    if(reqLoadInfo.first())
    {
        ui->lineEditPdvNom_3->setText(reqLoadInfo.value(0).toString());
        ui->lineEditPdvAdresse_3->setText(reqLoadInfo.value(1).toString());
        ui->lineEditPdvCP_3->setText(reqLoadInfo.value(2).toString());
        ui->lineEditPdvActivite_3->setText(reqLoadInfo.value(3).toString());
        ui->lineEditPdvVille_3->setText(reqLoadInfo.value(4).toString());
        ui->lineEditPdvTel_3->setText(reqLoadInfo.value(5).toString());

        if(reqLoadInfo.value(7).toString() == "0")
        {
            ui->radioButtonValideNon_3->setChecked(true);
        }
        else if(reqLoadInfo.value(7).toString() == "1")
        {
            ui->radioButtonValideOui_3->setChecked(true);
        }
    }
}

void MainWindow::on_butDel_2_clicked()
{

}

void MainWindow::on_pushButtonAddPdv_clicked()
{
    if(ui->listWidgetAffectationC->currentItem()){
        if(ui->listWidgetPdvC->currentItem()){
            QString qsIdAffectation = ui->listWidgetAffectationC->currentItem()->data(32).toString();
            QString qsIdP= ui->listWidgetPdvC->currentItem()->data(32).toString();
            QString qsLibelle = ui->lineEditPdvLibelle->text();
            QString qsDate = ui->dateEditPdvDate->date().toString("yyyy-MM-dd");

            QString qsIdVisite("SELECT MAX(numerovisite)+1 FROM visite");
            QSqlQuery reqRecupID(qsIdVisite);
            QString noVisiteId;
            if(reqRecupID.first())
            {
                qDebug()<<"C'est OK"<<endl;
                noVisiteId = reqRecupID.value(0).toString();
                qDebug()<<noVisiteId<<endl;
            } else {
                qDebug()<<"C'est pas OK"<<endl;
                noVisiteId = "1";
            }
            QString qsReqInsertVisite("INSERT INTO visite(numerovisite,libellevisite,dateVisite,identifiant,Controleur) VALUES ('");
            qsReqInsertVisite += noVisiteId +"', '";
            qsReqInsertVisite += qsLibelle +"', '";
            qsReqInsertVisite += qsIdP +"', '";
            qsReqInsertVisite += qsDate +"', '";
            qsReqInsertVisite += qsIdAffectation +"')";

            qDebug()<<qsReqInsertVisite<<endl;

            QSqlQuery reqInsertVisite;

            if(reqInsertVisite.exec(qsReqInsertVisite))
            {
                qDebug()<<"Ajout à la base"<<endl;
                statusBar()->showMessage("Succès : La visite à été ajouté !");
            }
            else
            {
                //qDebug()<<qsReqInsert<<endl;
                statusBar()->showMessage("Erreur : La visite n'a pas été ajouté !");
            }

        } else {
            statusBar()->showMessage("Erreur : Vous n'avez pas sélectionnez de producteur !");
        }
    } else {
        statusBar()->showMessage("Erreur : Vous n'avez pas sélectionnez de controleur !");
    }

}

void MainWindow::on_pushButtonDeleteRayon_clicked()
{
    qDebug()<<"void MainWindow::on_butDel_clicked()"<<endl;

    if(ui->listWidgetRayon->currentItem())
    {
        QString qsId = ui->listWidgetRayon->currentItem()->data(32).toString();
        QString qsReqDel("DELETE FROM rayon WHERE no_rayon = '" +qsId+ "'");

        int ret = QMessageBox::question(this,tr("Rayon"),tr("Souhaitez vous supprimer ce rayon ?"),
                                        QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            QSqlQuery reqDel(qsReqDel);
        }

        loadRayon();
    }
}

void MainWindow::on_pushButtonUpdateRayon_clicked()
{
    if(ui->listWidgetRayon->currentItem())
    {
        QString qsId = ui->listWidgetRayon->currentItem()->data(32).toString();

        QString qsNomRayon = ui->lineEditNomRayon->text();

        int ret = QMessageBox::question(this,"Rayon","Vous allez modifié un rayon ! ",
                                        QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            QString qsReqMAJ = "UPDATE rayon SET libelle = '" + qsNomRayon + "' WHERE no_rayon = '" + qsId +"'";
            QSqlQuery reqMaj(qsReqMAJ);


            if(reqMaj.exec())
            {
                statusBar()->showMessage("Rayon : Rayon modifié !" );
            }

        }
        loadRayon();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_5_clicked() Add Categorie"<<endl;

    QString qsNom = ui->lineEditNomCategorie->text();

    QString qsId("SELECT MAX(no_categorie)+1 FROM categorie ");
    QSqlQuery reqRecupID(qsId);
    QString noId;

    if(reqRecupID.first())
    {
        qDebug()<<"C'est OK"<<endl;
        noId = reqRecupID.value(0).toString();
        qDebug()<<noId<<endl;
    } else {
        qDebug()<<"C'est pas OK"<<endl;
        noId = "1";
    }
    if(ui->listWidgetRayon->currentItem()){
        QString qsId2 = ui->listWidgetRayon->currentItem()->data(32).toString();
        QString qsReqInsert("INSERT INTO categorie(no_categorie,no_rayon,libelle) VALUES ('");
        qsReqInsert += noId +"', '";
        qsReqInsert += qsId2 +"', '";
        qsReqInsert += qsNom +"')";

        QSqlQuery reqInsert(qsReqInsert);

        if(reqInsert.exec())
        {
            qDebug()<<"Ajout à la base"<<endl;
        }
        else
        {
            //qDebug()<<qsReqInsert<<endl;
            statusBar()->showMessage("Erreur : La catégorie n'a pas été ajouté !");
        }
        qDebug()<<"Chargement de la liste : Catégorie"<<endl;
        QString qsNumero = ui->listWidgetRayon->currentItem()->data(32).toString();
        QSqlQuery reqLoadCategorie("SELECT no_categorie,libelle FROM categorie WHERE no_rayon = " + qsNumero);
        ui->listWidgetCategorie->clear();
        ui->listWidgetProduit->clear();
        ui->lineEditNomProduit->clear();
        while(reqLoadCategorie.next())
        {

            QString qsNoCategorie = reqLoadCategorie.value(0).toString();
            QString qsNomCategorie = reqLoadCategorie.value(1).toString();
            QListWidgetItem *Item = new QListWidgetItem(qsNomCategorie);
            Item->setData(32,qsNoCategorie);

            ui->listWidgetCategorie->addItem(Item);

        }

        loadRayon();
    } else {
        statusBar()->showMessage("Erreur : Un rayon n'a pas été sélectionné !");
    }

}

void MainWindow::on_pushButton_7_clicked()
{
    qDebug()<<"void MainWindow::on_butDel_clicked()"<<endl;

    if(ui->listWidgetCategorie->currentItem())
    {
        QString qsId = ui->listWidgetCategorie->currentItem()->data(32).toString();
        QString qsReqDel("DELETE FROM categorie WHERE no_categorie = '" + qsId + "'");

        int ret = QMessageBox::question(this,tr("Categorie"),tr("Souhaitez vous supprimer ce rayon ?"),
                                        QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            QSqlQuery reqDel(qsReqDel);
            reqDel.exec();

            qDebug()<<"Chargement de la liste : Catégorie"<<endl;
            QString qsNumero = ui->listWidgetRayon->currentItem()->data(32).toString();
            QSqlQuery reqLoadCategorie("SELECT no_categorie,libelle FROM categorie WHERE no_rayon = " + qsNumero);
            ui->listWidgetCategorie->clear();
            ui->listWidgetProduit->clear();
            ui->lineEditNomProduit->clear();
            while(reqLoadCategorie.next())
            {

                QString qsNoCategorie = reqLoadCategorie.value(0).toString();
                QString qsNomCategorie = reqLoadCategorie.value(1).toString();
                QListWidgetItem *Item = new QListWidgetItem(qsNomCategorie);
                Item->setData(32,qsNoCategorie);

                ui->listWidgetCategorie->addItem(Item);

            }
        }

        loadRayon();
    }
}

void MainWindow::on_pushButtonMajCat_clicked()
{
    if(ui->listWidgetCategorie->currentItem())
        {
            QString qsId = ui->listWidgetCategorie->currentItem()->data(32).toString();

            QString qsNom = ui->lineEditNomCategorie->text();

            int ret = QMessageBox::question(this,"Categorie","Vous allez modifié une categorie ! ",
                                            QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
            if(ret == QMessageBox::Yes)
            {
                QString qsReqMAJ = "UPDATE categorie SET libelle = '" + qsNom + "' WHERE no_categorie = '" + qsId +"'";
                QSqlQuery reqMaj(qsReqMAJ);


                if(reqMaj.exec())
                {
                    statusBar()->showMessage("Catégorie : Catégorie modifié !" );
                }
                qDebug()<<"Chargement de la liste : Catégorie"<<endl;
                QString qsNumero = ui->listWidgetRayon->currentItem()->data(32).toString();
                QSqlQuery reqLoadCategorie("SELECT no_categorie,libelle FROM categorie WHERE no_rayon = " + qsNumero);
                ui->listWidgetCategorie->clear();
                ui->listWidgetProduit->clear();
                ui->lineEditNomProduit->clear();
                while(reqLoadCategorie.next())
                {

                    QString qsNoCategorie = reqLoadCategorie.value(0).toString();
                    QString qsNomCategorie = reqLoadCategorie.value(1).toString();
                    QListWidgetItem *Item = new QListWidgetItem(qsNomCategorie);
                    Item->setData(32,qsNoCategorie);

                    ui->listWidgetCategorie->addItem(Item);

                }

            }
        }
}

void MainWindow::on_pushButtonSupprProduit_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonSupprProduit_clicked()"<<endl;

    if(ui->listWidgetProduit->currentItem())
    {
        QString qsId = ui->listWidgetProduit->currentItem()->data(32).toString();
        QString qsReqDel("DELETE FROM produit WHERE numero = '" + qsId + "'");

        int ret = QMessageBox::question(this,tr("Produit"),tr("Souhaitez vous supprimer ce produit ?"),
                                        QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            QSqlQuery reqDel(qsReqDel);
            reqDel.exec();
            qDebug()<<"Chargement de la liste : Produit"<<endl;
            QString qsNumero = ui->listWidgetCategorie->currentItem()->data(32).toString();
            QSqlQuery reqLoadProduit("SELECT numero,libelle FROM produit WHERE no_categorie = " + qsNumero);
            ui->listWidgetProduit->clear();

            while(reqLoadProduit.next())
            {

                QString qsNoProduit = reqLoadProduit.value(0).toString();
                QString qsNomProduit = reqLoadProduit.value(1).toString();
                QListWidgetItem *Item = new QListWidgetItem(qsNomProduit);
                Item->setData(32,qsNoProduit);

                ui->listWidgetProduit->addItem(Item);

            }

        }
    }
}

void MainWindow::on_pushButtonAddProduit_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_5_clicked() Add Produit"<<endl;

    QString qsNom = ui->lineEditNomProduit->text();

    QString qsId("SELECT MAX(numero)+1 FROM produit ");
    QSqlQuery reqRecupID(qsId);
    QString noId;

    if(reqRecupID.first())
    {
        qDebug()<<"C'est OK"<<endl;
        noId = reqRecupID.value(0).toString();
        qDebug()<<noId<<endl;
    } else {
        qDebug()<<"C'est pas OK"<<endl;
        noId = "1";
    }
    if(ui->listWidgetCategorie->currentItem()){
        QString qsId2 = ui->listWidgetCategorie->currentItem()->data(32).toString();
        QString qsReqInsert("INSERT INTO produit(numero,no_categorie,libelle) VALUES ('");
        qsReqInsert += noId +"', '";
        qsReqInsert += qsId2 +"', '";
        qsReqInsert += qsNom +"')";

        QSqlQuery reqInsert(qsReqInsert);

        if(reqInsert.exec())
        {
            qDebug()<<"Ajout à la base"<<endl;
        }
        else
        {
            qDebug()<<qsReqInsert<<endl;
            statusBar()->showMessage("Erreur : Le produit n'a pas été ajouté !");
        }
        qDebug()<<"Chargement de la liste : Catégorie"<<endl;
        QString qsNumero = ui->listWidgetCategorie->currentItem()->data(32).toString();
        QSqlQuery reqLoadProduit("SELECT numero,libelle FROM produit WHERE no_categorie = " + qsNumero);
        ui->listWidgetProduit->clear();
        ui->lineEditNomProduit->clear();
        while(reqLoadProduit.next())
        {

            QString qsNoProduit = reqLoadProduit.value(0).toString();
            QString qsNomProduit = reqLoadProduit.value(1).toString();
            QListWidgetItem *Item = new QListWidgetItem(qsNomProduit);
            Item->setData(32,qsNoProduit);

            ui->listWidgetProduit->addItem(Item);

        }
    } else {
        statusBar()->showMessage("Erreur : Une catégorie n'a pas été sélectionné !");
    }

}

void MainWindow::on_butUpdate_2_clicked()
{
    if(ui->listWidgetPdvValide->currentItem())
    {
        QString qsId = ui->listWidgetPdvValide->currentItem()->data(32).toString();

        QString qsNom = ui->lineEditPdvNom->text();
        QString qsAdresse = ui->lineEditPdvAdresse->text();
        QString qsCp = ui->lineEditPdvCP->text();
        QString qsActivite = ui->lineEditPdvActivite->text();
        QString qsVille = ui->lineEditPdvVille->text();
        QString qsTel = ui->lineEditPdvTel->text();
        QString qsValide;
        if(ui->radioButtonValideOui->isChecked())
        {
            qsValide = "1";
        }
        if(ui->radioButtonValideNon->isChecked())
        {
            qsValide = "0";
        }
        int ret = QMessageBox::question(this,"PDV","Vous allez modifié un point de vente ! ",
                                        QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            QString qsReqMAJ = "UPDATE pointdevente SET nom = '" + qsNom + "', adresse = '" + qsAdresse + "', codePostal = '" + qsCp + "' , activite = '" + qsActivite + "' , ville = '" + qsVille + "' , tel = '" + qsTel + "'  , valide = '" + qsValide + "' WHERE no_pdv = '" + qsId +"'";
            QSqlQuery reqMaj(qsReqMAJ);


            if(reqMaj.exec())
            {
                statusBar()->showMessage("Point de vente : Point de vente modifié !" );
            } else {
                statusBar()->showMessage("Erreur : Point de vente n'a pas pu être modifié!" );
            }

        }
        loadPdv();
    }
}

void MainWindow::on_butUpdate_5_clicked()
{
    if(ui->listWidgetPdvNonValide->currentItem())
    {
        QString qsId = ui->listWidgetPdvNonValide->currentItem()->data(32).toString();

        QString qsNom = ui->lineEditPdvNom_3->text();
        QString qsAdresse = ui->lineEditPdvAdresse_3->text();
        QString qsCp = ui->lineEditPdvCP_3->text();
        QString qsActivite = ui->lineEditPdvActivite_3->text();
        QString qsVille = ui->lineEditPdvVille_3->text();
        QString qsTel = ui->lineEditPdvTel_3->text();
        QString qsValide;
        if(ui->radioButtonValideOui_3->isChecked())
        {
            qsValide = "1";
        }
        if(ui->radioButtonValideNon_3->isChecked())
        {
            qsValide = "0";
        }
        int ret = QMessageBox::question(this,"PDV","Vous allez modifié un point de vente ! ",
                                        QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            QString qsReqMAJ = "UPDATE pointdevente SET nom = '" + qsNom + "', adresse = '" + qsAdresse + "', codePostal = '" + qsCp + "' , activite = '" + qsActivite + "' , ville = '" + qsVille + "' , tel = '" + qsTel + "'  , valide = '" + qsValide + "' WHERE no_pdv = '" + qsId +"'";
            QSqlQuery reqMaj(qsReqMAJ);


            if(reqMaj.exec())
            {
                statusBar()->showMessage("Point de vente : Point de vente modifié !" );
            } else {
                statusBar()->showMessage("Erreur : Point de vente n'a pas pu être modifié!" );
            }

        }
        loadPdv();
    }
}
