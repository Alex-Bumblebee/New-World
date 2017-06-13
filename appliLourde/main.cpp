#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include "dlgConnexion.h"
#include "mainwindow.h"
#include "mainwindowc.h"
#include <QTranslator>
#include <QLibraryInfo>
#include <QSqlQuery>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase maBase=QSqlDatabase::addDatabase("QMYSQL");
    maBase.setHostName("localhost");
    maBase.setDatabaseName("dbnewworld");
    maBase.setUserName("root");
    maBase.setPassword("130797");

    if(maBase.open())
    {
        DlgConnexion login;

        while(login.exec()==QDialog::Accepted)
        {
            QString qsTypeUser = login.getTypeUser();
            QString qsIdUser = login.getID();

            if(qsTypeUser == "Gestionnaire")
            {
                MainWindow w(qsIdUser);
                w.show();
                return a.exec();
            }
            else if(qsTypeUser == "Controleur")
            {
                MainWindowC w(qsIdUser);
                w.show();
                return a.exec();
            }
            else
            {
                qDebug()<<"Pas les droits"<<endl;
            }

        }
    }
}
