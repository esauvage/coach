#include "formgestionseances.h"
#include "ui_formgestionseances.h"

FormGestionSeances::FormGestionSeances(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGestionSeances)
{
    ui->setupUi(this);
}

FormGestionSeances::~FormGestionSeances()
{
    delete ui;
}
