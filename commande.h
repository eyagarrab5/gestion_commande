// COMMANDE_H
#ifndef COMMANDE_H
#define COMMANDE_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDebug>
#include <QSqlError>

class commande
{

public:
    commande(); 
    commande(int,int,int,QString,int);
    int getreference();
    int getddate();
    int gethoraire();
    QString getadresse();
    int getprix();
    void setreference(int);
    void setddate(int);
    void sethoraire(int);
    void setadresse(QString);
    void setprix(int);
    bool ajouter();
    int calcul_type_stat(QString);
    QSqlQueryModel *afficher();
    QSqlQueryModel *afficher1();
    commande(int,int,QString,int);
    bool supprimer(int reference);
    bool modifier(int);
    bool rechercher_ref(int);
    QVector<commande> * ObtenirTousCommandes();
    QSqlQueryModel * recherche(int);
    QSqlQueryModel * trier_horaire(int);
    QSqlQueryModel * tri_ddate(int);


    void getDatabaseValue(int reference);
private:
    int reference,ddate,horaire,prix;
    QString adresse;
};

#endif // COMMANDE_H
