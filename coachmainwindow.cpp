#include "coachmainwindow.h"
#include "ui_coachmainwindow.h"

#include "formeditpersonne.h"

CoachMainWindow::CoachMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CoachMainWindow)
{
    ui->setupUi(this);
    _personnes << Personne();
    FormEditPersonne * f = new FormEditPersonne(_personnes.first());
    ui->centralwidget->layout()->addWidget(f);
}

CoachMainWindow::~CoachMainWindow()
{
    delete ui;
}

