#include "formeditpersonne.h"
#include "ui_formeditpersonne.h"

FormEditPersonne::FormEditPersonne(Personne &personne, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEditPersonne),
    _personne(personne)
{
    ui->setupUi(this);
    ui->widget->setLayout(new QVBoxLayout());
    setPersonne(_personne);
}

FormEditPersonne::~FormEditPersonne()
{
    delete ui;
}

void FormEditPersonne::setPersonne(Personne &personne)
{
    _personne = personne;
    ui->edtNom->setText(personne.nom());
    _edtPrenoms << new QLineEdit();
    ui->widget->layout()->addWidget(_edtPrenoms.last());
    connect(_edtPrenoms.last(), SIGNAL(editingFinished()), this, SLOT(prenomsEdited()));
//    ui->lineEdit_2->setText(personne.prenom());
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
