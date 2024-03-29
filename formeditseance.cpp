#include "formeditseance.h"
#include "ui_formeditseance.h"

#include "coachapplication.h"
#include <QLineEdit>

FormEditSeance::FormEditSeance(Seance & seance, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEditSeance),
    _seance(seance)
{
    ui->setupUi(this);
    ui->edtDate->setDateTime(QDateTime::currentDateTime());
    ui->edtDebut->setDateTime(QDateTime::currentDateTime());
    ui->edtFin->setDateTime(QDateTime::currentDateTime());
    connect(ui->cbxActivite->lineEdit(), &QLineEdit::editingFinished, this, &FormEditSeance::activiteChanged);
    _dbManager = static_cast<CoachApplication *>(QApplication::instance())->dbManager();
    for (auto activite : _dbManager->getActivites())
    {
        ui->cbxActivite->addItem(activite.first, activite.second);
    }
}

FormEditSeance::~FormEditSeance()
{
    delete ui;
}

Seance &FormEditSeance::seance() const
{
    _seance.setDate(ui->edtDate->date());
    _seance.setDebut(ui->edtDebut->time());
    _seance.setFin(ui->edtFin->time());
	_seance.setActiviteId(ui->cbxActivite->currentData().toInt());
    return _seance;
}

void FormEditSeance::setSeance(const Seance &seance)
{
    ui->edtDate->setDate(seance.date());
    ui->edtDebut->setTime(seance.debut());
    ui->edtFin->setTime(seance.fin());
	ui->cbxActivite->setCurrentIndex(ui->cbxActivite->findData(seance.activiteId()));
    _seance = seance;
}

void FormEditSeance::on_edtDate_editingFinished()
{
    emit changed();
}

void FormEditSeance::on_edtDebut_editingFinished()
{
    on_edtDate_editingFinished();
}

void FormEditSeance::on_edtFin_editingFinished()
{
    on_edtDate_editingFinished();
}


void FormEditSeance::activiteChanged()
{
    if (ui->cbxActivite->currentData().toInt()<1)
    {
        _dbManager->addActivite(ui->cbxActivite->currentText());
    }
}
