#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_Ajouter_clicked();

    void on_btn_supprimer_clicked();

    void on_modifier_clicked();

    void on_trier_horaire_clicked();

    void on_tri_ddate_clicked();

    void on_recherche_ref_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
