#include "commande.h"
#include "produit.h"
#include <QObject>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
commande::commande()
{
    reference=0;
    ddate=0;
    horaire=0;
    adresse="";
    prix=0;
}

commande::commande(int reference,int ddate,int horaire,QString adresse,int prix)
{   this->reference=reference;
    this->ddate=ddate;
    this->horaire=horaire;
    this->adresse=adresse;
    this->prix=prix;
}
commande::commande(int ddate,int horaire,QString adresse,int prix)
{
    this->ddate=ddate;
    this->horaire=horaire;
    this->adresse=adresse;
    this->prix=prix;
}

bool commande::ajouter()
    {
        QSqlQuery query;
        QString reference_string = QString::number(reference);
        QString ddate_string = QString::number(ddate);
        QString horaire_string = QString::number(horaire);
        QString prix_string = QString::number(prix);

        qDebug() << "Adding a new command to the database:";
        qDebug() << "REFERENCE:" << reference_string;
        qDebug() << "DDATE:" << ddate_string;
        qDebug() << "HORAIRE:" << horaire_string;
        qDebug() << "ADRESSE:" << adresse;
        qDebug() << "PRIX:" << prix_string;

        query.prepare("INSERT INTO COMMANDE(REFERENCE,DDATE,HORAIRE,ADRESSE,PRIX)"
                      "VALUES(:REFERENCE,:DDATE,:HORAIRE,:ADRESSE,:PRIX)");
        query.bindValue(":REFERENCE", reference_string);
        query.bindValue(":DDATE", ddate_string);
        query.bindValue(":HORAIRE", horaire_string);
        query.bindValue(":ADRESSE", adresse);
        query.bindValue(":PRIX", prix_string);

        bool queryResult = query.exec();

        if (queryResult) {
            qDebug() << "Command added successfully!";
        } else {
            qDebug() << "Error adding command to the database:";
            qDebug() << "Query error:" << query.lastError().text();
        }

        return queryResult;
    }
QSqlQueryModel * commande::afficher()
{class QSqlQueryModel* model=new class QSqlQueryModel();
    model->setQuery("SELECT * FROM COMMANDE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DDATE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("HORAIRE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}

bool commande::supprimer(int reference)
{
    QSqlQuery query;
         query.prepare("SELECT * FROM COMMANDE WHERE reference = :REFERENCE");
         query.bindValue(":REFERENCE", reference);
         if (!query.exec()) {
             qDebug() << "Erreur lors de l'exécution de la requête SELECT.";
             return false;
         }

         if (query.next()) {
             query.prepare("DELETE FROM COMMANDE WHERE reference=:REFERENCE");
             query.bindValue(":REFERENCE", reference);
             if (query.exec()) {
                 return true;
             } else {
                 qDebug() << "Erreur lors de l'exécution de la requête DELETE.";
                 return false;
             }
         } else {

             QMessageBox msgBox;
             msgBox.setText("Commande non trouvée.");
             msgBox.exec();
             return false;
         }
  }

int commande::getreference(){return reference;}
int commande::getddate(){return ddate;}
int commande::gethoraire(){return horaire;}
QString commande::getadresse(){return adresse;}
int commande::getprix(){return prix;}
void commande::setreference(int reference){this->reference=reference;}
void commande::setddate(int ddate){this->ddate=ddate;}
void commande::sethoraire(int horaire){this->horaire=horaire;}
void commande::setadresse(QString adresse){this->adresse=adresse;}
void commande::setprix(int prix){this->prix=prix;}

bool commande::modifier(int reference)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM COMMANDE WHERE reference = :REFERENCE");

    query.bindValue(":REFERENCE", reference);
    if (!query.exec())
    {
        qDebug()<<"ERREUR LORS EXECUTION REQUETE SELECT.";
        return false;
      }
    if(query.next()){
        QString reference_string = QString::number(reference);
        QString ddate_string = QString::number(ddate);
        QString horaire_string = QString::number(horaire);
        QString prix_string = QString::number(prix);
            QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE COMMANDE SET reference=:REFERENCE, ddate=:DDATE, horaire=:HORAIRE, adresse=:ADRESSE, prix=:PRIX)"
                      "WHERE reference = :REFERENCE");
        updateQuery.bindValue(":REFERENCE", reference_string);
        updateQuery.bindValue(":DDATE", ddate_string);
        updateQuery.bindValue(":HORAIRE", horaire_string);
        updateQuery.bindValue(":ADRESSE", adresse);
        updateQuery.bindValue(":PRIX", prix_string);
        if (updateQuery.exec()) {
                     return true;
                 } else {
                     // Gérer l'erreur d'exécution de la requête UPDATE
                     qDebug() << "Erreur lors de l'exécution de la requête Mise à Jour." << updateQuery.lastError().text();
                     return false;
                 }
             } else {
                 QMessageBox msgBox;
                 msgBox.setText("Reference non trouvé pour la modification.");
                 msgBox.exec();
                 return false; // Arrêter le processus ici si la référence n'est pas trouvée pour la modification
    }
}

QSqlQueryModel *commande::tri_ddate(int tri_ddate)
{
    class QSqlQueryModel *model = new class QSqlQueryModel();
    QString queryStr;

    if (tri_ddate == 1) { // Sort by date ascending
        queryStr = "SELECT * FROM COMMANDE ORDER BY DDATE ASC";
    } else { // Sort by date descending
        queryStr = "SELECT * FROM COMMANDE ORDER BY DDATE DESC";
    }

    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DDATE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("HORAIRE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}


QSqlQueryModel *commande::trier_horaire(int trier_horaire)
{

    class QSqlQueryModel *model = new class QSqlQueryModel();
    QString queryStr;
    if (trier_horaire == 1) { // Sort by horaire ascending
        queryStr = "SELECT * FROM COMMANDE ORDER BY HORAIRE ASC";
    } else { // Sort by horaire descending
        queryStr = "SELECT * FROM COMMANDE ORDER BY HORAIRE DESC";
    }
    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DDATE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("HORAIRE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}




QVector<commande> *commande::ObtenirTousCommandes() {
    // Exécutez une requête SQL pour récupérer tous les commandes de la base de données
    QSqlQuery query;
    query.prepare("SELECT * FROM COMMANDE");
    if (query.exec()) {
        // Créez un objet QVector<commande> pour stocker les résultats de la requête
        QVector<commande> commandes;

        // Parcourez les résultats de la requête et ajoutez chaque commande au tableau
        while (query.next()) {
            commande c1;
            c1.setreference(query.value(":REFERENCE").toInt());
            c1.setddate(query.value("DDATE").toInt());
            c1.sethoraire(query.value(":HORAIRE").toInt());
            c1.setadresse(query.value(":ADRESSE").toString());
            c1.setprix(query.value(":PRIX").toInt());

            commandes.append(c1);
        }

        // Créez un pointeur vers l'objet QVector<commande>
        QVector<commande> *pcommandes = new QVector<commande>(commandes);

        // Retournez le pointeur
        return pcommandes;
    }

    return nullptr;
}
bool commande::rechercher_ref(int reference)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM COMMANDE WHERE reference = :REFERENCE");
    query.bindValue(":REFERENCE", reference);

    if (query.exec() && query.next()) {
        setreference(query.value("REFERENCE").toInt());
        sethoraire(query.value("HORAIRE").toInt());
        setddate(query.value("DDATE").toInt());
        setadresse(query.value("ADRESSE").toString());
        setprix(query.value("PRIX").toInt());
        return true;
    }
    return false;
}

