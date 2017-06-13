#include "mainwindowc.h"
#include "ui_mainwindowc.h"
#include <QDebug>
#include <QSqlQuery>
#include <QTime>
#include <QDate>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>

MainWindowC::MainWindowC(QString qsID,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowC)
{
    ui->setupUi(this);
    m_qsID = qsID;
    loadVisite();
}

MainWindowC::~MainWindowC()
{
    delete ui;
}


void MainWindowC::loadVisite()
{
    qDebug()<<"MainWindowC::loadVisite()"<<endl;

    QSqlQuery reqLoadVisite("SELECT numerovisite,libellevisite FROM visite WHERE Controleur = " + m_qsID);
    ui->listWidgetVisiteFaire->clear();

    while(reqLoadVisite.next())
    {

        QString qsID = reqLoadVisite.value(0).toString();
        QString qsNom = reqLoadVisite.value(1).toString();
        QListWidgetItem *Item = new QListWidgetItem(qsNom);
        Item->setData(32,qsID);

        ui->listWidgetVisiteFaire->addItem(Item);

    }


}

void MainWindowC::on_listWidgetVisiteFaire_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"MainWindow::on_listWidgetVisiteFaire_itemClicked(QListWidgetItem *item)"<<endl;

    QString qsVisiteFaireID = ui->listWidgetVisiteFaire->currentItem()->data(32).toString();

    QString qsReq("SELECT libellevisite,dateVisite FROM visite WHERE numerovisite = " + qsVisiteFaireID);
    QSqlQuery reqLoadInfo(qsReq);

    if(reqLoadInfo.first())
    {
        ui->labelDateVisite->setText(reqLoadInfo.value(1).toString());
    }
}

void MainWindowC::on_pushButton_clicked()
{
    qDebug()<<"void MainWindow::on_pushButton_5_clicked() Add Produit"<<endl;

    QString qsMotif = ui->textEditMotif->toPlainText();
    QString qsDebut = ui->timeEditDebut->text();
    QString etat = "1";
    QString qsConcluant;
    if(ui->radioButtonOui->isChecked())
    {
        qsConcluant = "1";
    }

    if(ui->radioButtonNon->isChecked())
    {
        qsConcluant = "0";
    }

    if(ui->listWidgetVisiteFaire->currentItem()){
        QString qsId2 = ui->listWidgetVisiteFaire->currentItem()->data(32).toString();
        QString qsReqInsert("INSERT INTO controleproducteur(visiteConcluante,heureDebutControle,etat,numerovisite,identifiant,motifRejet) VALUES ('");
        qsReqInsert += qsConcluant +"', '";
        qsReqInsert += qsDebut +"', '";
        qsReqInsert += etat +"', '";
        qsReqInsert += qsId2 +"', '";
        qsReqInsert += m_qsID +"', '";
        qsReqInsert += qsMotif +"')";

        QSqlQuery reqInsert(qsReqInsert);

        if(reqInsert.exec())
        {
            qDebug()<<"Ajout à la base"<<endl;
        }
        else
        {
            qDebug()<<qsReqInsert<<endl;
            statusBar()->showMessage("Erreur : La visite n'a pas été ajouté !");
        }
        loadVisite();
    } else {

    }
}
