#ifndef MAINWINDOWC_H
#define MAINWINDOWC_H

#include <QMainWindow>
#include <QListWidget>
namespace Ui {
class MainWindowC;
}

class MainWindowC : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowC(QString qsID, QWidget *parent = 0);
    ~MainWindowC();
    QString m_qsID;
    void loadVisite();

private slots:
    void on_listWidgetVisiteFaire_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::MainWindowC *ui;
};

#endif // MAINWINDOWC_H
