#include "formgestionseances.h"
#include "ui_formgestionseances.h"

#include <QDialogButtonBox>

#include "formeditseance.h"
#include "dbmanager.h"


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

void FormGestionSeances::on_btnAjout_clicked()
{
    ui->btnAjout->hide();
    if (!_formEdtSeance)
    {
        _formEdtSeance = new FormEditSeance(_seance);
    }
    ui->verticalLayout->addWidget(_formEdtSeance);
    if (!_hlayout)
    {
        QPushButton * btnValider = new QPushButton("Valider");
        QPushButton * btnAnnuler = new QPushButton("Annuler");
        connect(btnValider, SIGNAL(clicked()), this, SLOT(ajoutValide()));
        connect(btnAnnuler, SIGNAL(clicked()), this, SLOT(ajoutAnnule()));
        _hlayout = new QDialogButtonBox();
        _hlayout->addButton(btnValider, QDialogButtonBox::ActionRole);
        _hlayout->addButton(btnAnnuler, QDialogButtonBox::ActionRole);
    }
    ui->verticalLayout->addWidget(_hlayout);
}

void FormGestionSeances::ajoutAnnule()
{
    ui->btnAjout->show();
    ui->verticalLayout->removeWidget(_formEdtSeance);
    delete _formEdtSeance;
    _formEdtSeance = nullptr;
    ui->verticalLayout->removeWidget(_hlayout);
    delete _hlayout;
    _hlayout = nullptr;
    update();
}

void FormGestionSeances::ajoutValide()
{
    _dbManager->addSeance(_formEdtSeance->seance());
    ui->btnAjout->show();
    ui->verticalLayout->removeWidget(_formEdtSeance);
    delete _formEdtSeance;
    _formEdtSeance = nullptr;
    ui->verticalLayout->removeWidget(_hlayout);
    delete _hlayout;
    _hlayout = nullptr;
    update();
}
