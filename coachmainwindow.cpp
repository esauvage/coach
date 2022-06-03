#include "coachmainwindow.h"
#include "ui_coachmainwindow.h"

#include "formeditpersonne.h"
#include "formgestionpersonnes.h"
#include "formgestionseances.h"

CoachMainWindow::CoachMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CoachMainWindow)
{
    ui->setupUi(this);
    _accueil = ui->centralwidget;
}

CoachMainWindow::~CoachMainWindow()
{
    delete ui;
}


void CoachMainWindow::on_btnPersonnes_clicked()
{
    FormGestionPersonnes * gestionPers = new FormGestionPersonnes();
    setCentralWidget(gestionPers);
}

void CoachMainWindow::on_btnSeance_clicked()
{
    FormGestionSeances * gestionSeance = new FormGestionSeances();
    setCentralWidget(gestionSeance);
}
