#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QString qsID,QWidget *parent = 0);
    ~MainWindow();
    QString m_qsID;
    void loadEmployer();
    void loadRayon();
    void loadPdv();
    void loadVisite();
    QString GetRandomString() const;
private slots:

    void on_butAdd_clicked();

    void on_butDel_clicked();

    void on_listWidgetPersonnels_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_butUpdate_clicked();

    void on_listWidgetRayon_itemClicked(QListWidgetItem *item);

    void on_listWidgetProduit_itemClicked(QListWidgetItem *item);

    void on_listWidgetCategorie_itemClicked(QListWidgetItem *item);

    void on_pushButtonAddRayon_clicked();

    void on_listWidgetPdvValide_itemClicked(QListWidgetItem *item);

    void on_butAdd_2_clicked();

    void on_listWidgetPdvNonValide_itemClicked(QListWidgetItem *item);

    void on_butDel_2_clicked();

    void on_pushButtonAddPdv_clicked();

    void on_pushButtonDeleteRayon_clicked();

    void on_pushButtonUpdateRayon_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButtonMajCat_clicked();

    void on_pushButtonSupprProduit_clicked();

    void on_pushButtonAddProduit_clicked();

    void on_butUpdate_2_clicked();

    void on_butUpdate_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
