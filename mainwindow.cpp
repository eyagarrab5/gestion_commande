#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)



{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_Ajouter_clicked()
{
    QLocale::setDefault(QLocale::c());
        int reference= ui->ref->text().toInt();
        int ddate=ui->date->text().toInt();
        int horaire=ui->horaire->text().toInt();
        QString adresse=ui->adresse->text();
        int prix=ui->prix->text().toInt();
        commande c(reference, ddate, horaire, adresse, prix);

        bool test=c.ajouter();
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Ajout effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
            ui->table_commandes->setModel(c.afficher());
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Ajout non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        QLocale::setDefault(QLocale());

}

void MainWindow::on_btn_supprimer_clicked()
{
    commande c1;
        c1.setreference(ui->ref->text().toInt());
        bool test=c1.supprimer(c1.getreference());
        if(test)
        {
        ui->table_commandes->setModel(c1.afficher());
        QMessageBox::information(nullptr, QObject::tr("database is open"),
        QObject::tr("Suppression effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);
        bool test=c1.supprimer(c1.getreference());
        if(test)
        {
            ui->table_commandes->setModel(c1.afficher());
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                QObject::tr("Suppression effectué.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
        }
        }
}

void MainWindow::on_modifier_clicked()
{
    int ref=ui->refmodif->text().toInt();
    int ddate=ui->datemodif->text().toInt();
    int horaire=ui->horairemodif->text().toInt();
    QString adresse=ui->adressemodif->text();
    int prix=ui->prixmodif->text().toInt();
    commande c(ddate, horaire, adresse, prix);
    bool test=c.modifier(ref);

               if(test) {
                   ui->table_commandes->setModel(c.afficher());
                   QMessageBox::information(nullptr, QObject::tr("database is open"),
                               QObject::tr("Modification effectuée.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);}
}
void MainWindow::on_tri_ddate_clicked()
{
    commande c1;
    // Utilisez la fonction de tri pour mettre à jour le modèle
    int tri_ddate = atoi("ASC");
    QSqlQueryModel *sortedModel = c1.tri_ddate(tri_ddate);
 // Utilisez votre fonction de tri dans la classe vehicule
    // Mettez à jour la vue
    ui->table_commandes->setModel(sortedModel);
}
void MainWindow::on_trier_horaire_clicked()
{
    commande c1;
    // Utilisez la fonction de tri pour mettre à jour le modèle
    int trier_horaire = atoi("ASC");
    QSqlQueryModel *sortedModel = c1.trier_horaire(trier_horaire);
   // Utilisez votre fonction de tri dans la classe vehicule
    // Mettez à jour la vue
    ui->table_commandes->setModel(sortedModel);
}
void MainWindow::on_recherche_ref_clicked()
{
    int reference = atoi(ui->ref->text().toUtf8().constData());

     commande c1;
     bool test = c1.rechercher_ref(reference);

     QMessageBox msgBox;
     if (test)
     {
         msgBox.setText("commande trouvé.");
         // Affichez les données dans votre tableau ou où vous le souhaitez
         ui->table_commandes->setModel(c1.afficher());
     }
     else
     {
         msgBox.setText("commande introuvable!");
     }
     msgBox.exec();
}

