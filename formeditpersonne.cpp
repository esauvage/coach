#include "formeditpersonne.h"
#include "ui_formeditpersonne.h"

#include "dbmanager.h"
#include "coachapplication.h"

FormEditPersonne::FormEditPersonne(Personne &personne, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEditPersonne),
	_personne(personne),
	_dbManager(nullptr)
{
    ui->setupUi(this);
	ui->groupBox->hide();
    ui->widget->setLayout(new QVBoxLayout());
	setPersonne(_personne);
	_dbManager = static_cast<CoachApplication *>(QApplication::instance())->dbManager();
}

FormEditPersonne::~FormEditPersonne()
{
    delete ui;
}

void FormEditPersonne::setPersonne(Personne &personne)
{
	_edtPrenoms.clear();
    _personne = personne;
    ui->edtNom->setText(personne.nom());
    _edtPrenoms << new QLineEdit();
    ui->widget->layout()->addWidget(_edtPrenoms.last());
    connect(_edtPrenoms.last(), SIGNAL(editingFinished()), this, SLOT(prenomsEdited()));
    ui->edtNaissance->setDateTime(personne.dateNaissance());
    ui->edtDeces->setDateTime(personne.dateDeces());
}

void FormEditPersonne::on_edtNom_editingFinished()
{
    _personne.setNom(ui->edtNom->text());
}

void FormEditPersonne::prenomsEdited()
{
    QStringList prenoms;
    for (auto x : _edtPrenoms)
    {
        if ((x->text().isEmpty()) && (x != _edtPrenoms.last()))
        {
            ui->widget->layout()->removeWidget(x);
            delete x;
            continue;
        }
        prenoms << x->text();
    }
    if (prenoms.last().isEmpty())
    {
        prenoms.takeLast();
    }
    else
    {
        _edtPrenoms << new QLineEdit();
        ui->widget->layout()->addWidget(_edtPrenoms.last());
        connect(_edtPrenoms.last(), SIGNAL(editingFinished()), this, SLOT(prenomsEdited()));
    }
    _personne.setPrenom(prenoms.join(", "));
}

void FormEditPersonne::on_edtNaissance_editingFinished()
{
    _personne.setDateNaissance(ui->edtNaissance->dateTime());
}

void FormEditPersonne::on_edtDeces_editingFinished()
{
    _personne.setDateDeces(ui->edtDeces->dateTime());
}

Personne &FormEditPersonne::personne() const
{
    return _personne;
}

void FormEditPersonne::on_btnChangePasswd_clicked()
{
	_dbManager->changePassword(_personne.id(), ui->edtPasswd->text());
}

void FormEditPersonne::on_btnChangePerson_clicked()
{
	if (!_personne.isValid()) _dbManager->addPersonne(_personne);
	else _dbManager->modifPersonne(_personne);
	emit finished();
}

void FormEditPersonne::on_pushButton_2_clicked()
{
	emit finished();
}

void FormEditPersonne::on_btnSuppr_clicked()
{
	if (_personne.isValid()) _dbManager->supprimePersonne(_personne.id());
	emit finished();
}


void FormEditPersonne::on_btnAnnuler_clicked()
{
	ui->groupBox->setHidden(!ui->groupBox->isHidden());
}

