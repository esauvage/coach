#include "coachmainwindow.h"
#include "ui_coachmainwindow.h"

#include "formeditpersonne.h"
#include "formgestionpersonnes.h"

CoachMainWindow::CoachMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CoachMainWindow)
{
    ui->setupUi(this);
}

CoachMainWindow::~CoachMainWindow()
{
    delete ui;
}


void CoachMainWindow::on_pushButton_clicked()
{
    _accueil = ui->centralwidget;
    FormGestionPersonnes * gestionPers = new FormGestionPersonnes();
    setCentralWidget(gestionPers);
}
