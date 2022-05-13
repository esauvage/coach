#include "formgestionpersonnes.h"
#include "ui_formgestionpersonnes.h"

#include <QPushButton>
#include <QDialogButtonBox>

#include "coachapplication.h"
#include "formeditpersonne.h"
#include "dbmanager.h"

FormGestionPersonnes::FormGestionPersonnes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGestionPersonnes)
{
    ui->setupUi(this);
    CoachApplication * app = dynamic_cast<CoachApplication *>(QApplication::instance());
	populateComboBox();
}

FormGestionPersonnes::~FormGestionPersonnes()
{
    delete ui;
}

void FormGestionPersonnes::on_btnAjout_clicked()
{
    ui->btnAjout->hide();
    if (!_formEdtPers)
    {
        _formEdtPers = new FormEditPersonne(personne);
    }
    ui->verticalLayout->addWidget(_formEdtPers);
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

void FormGestionPersonnes::ajoutAnnule()
{
    ui->btnAjout->show();
    ui->verticalLayout->removeWidget(_formEdtPers);
    delete _formEdtPers;
    _formEdtPers = nullptr;
    ui->verticalLayout->removeWidget(_hlayout);
    delete _hlayout;
    _hlayout = nullptr;
    update();
}

void FormGestionPersonnes::ajoutValide()
{
    _dbManager->addPersonne(_formEdtPers->personne());
    ui->btnAjout->show();
    ui->verticalLayout->removeWidget(_formEdtPers);
    delete _formEdtPers;
    _formEdtPers = nullptr;
    ui->verticalLayout->removeWidget(_hlayout);
    delete _hlayout;
    _hlayout = nullptr;
    populateComboBox();
    update();
}

void FormGestionPersonnes::modifValide()
{
    _dbManager->modifPersonne(_formEdtPers->personne());
    ui->btnAjout->show();
    ui->verticalLayout->removeWidget(_formEdtPers);
    delete _formEdtPers;
    _formEdtPers = nullptr;
    ui->verticalLayout->removeWidget(_hlayout);
    delete _hlayout;
    _hlayout = nullptr;
    populateComboBox();
    update();
}

void FormGestionPersonnes::populateComboBox()
{
	ui->comboBox->clear();
    ui->comboBox->addItem("", -1);
	QList<Personne> personnes = _dbManager->getPersonnes();
    for (auto &p : personnes)
	{
        ui->comboBox->addItem(p.nom(), p.id());
	}
}

void FormGestionPersonnes::on_comboBox_currentIndexChanged(int index)
{
    if (ui->comboBox->currentData().toInt() < 0)
        return;
    personne = _dbManager->getPersonne(ui->comboBox->currentData().toInt());
    ui->btnAjout->hide();
    if (!_formEdtPers)
    {
        _formEdtPers = new FormEditPersonne(personne);
    }
    ui->verticalLayout->addWidget(_formEdtPers);
    if (!_hlayout)
    {
        QPushButton * btnValider = new QPushButton("Modifier");
        QPushButton * btnAnnuler = new QPushButton("Annuler");
        connect(btnValider, SIGNAL(clicked()), this, SLOT(modifValide()));
        connect(btnAnnuler, SIGNAL(clicked()), this, SLOT(ajoutAnnule()));
        _hlayout = new QDialogButtonBox();
        _hlayout->addButton(btnValider, QDialogButtonBox::ActionRole);
        _hlayout->addButton(btnAnnuler, QDialogButtonBox::ActionRole);
    }
    ui->verticalLayout->addWidget(_hlayout);
}
