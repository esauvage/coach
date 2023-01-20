#include "formgestionpersonnes.h"
#include "ui_formgestionpersonnes.h"

#include <QDialogButtonBox>
#include <QSettings>

#include "coachapplication.h"
#include "dbmanager.h"

FormGestionPersonnes::FormGestionPersonnes(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::FormGestionPersonnes),
	_dbManager(nullptr)
{
    ui->setupUi(this);
	_dbManager = static_cast<CoachApplication *>(QApplication::instance())->dbManager();
	populateComboBox();
	QSettings settings;
	const int lastUser = settings.value("lastUser", -1).toInt();
	const int index = ui->comboBox->findData(lastUser);
	if (index >= 0)
		ui->comboBox->setCurrentIndex(index);
    ui->btnEdit->hide();
}

FormGestionPersonnes::~FormGestionPersonnes()
{
	QSettings settings;
	settings.setValue("lastUser", personne.id());
	delete ui;
}

int FormGestionPersonnes::curPersonId() const
{
	return personne.id();
}

void FormGestionPersonnes::reload()
{
	ui->comboBox->clear();
	populateComboBox();
}

void FormGestionPersonnes::populateComboBox()
{
	ui->comboBox->clear();
	QList<QPair<QString, int> > personnes = _dbManager->getNomPersonnes();
    for (auto &p : personnes)
	{
		ui->comboBox->addItem(p.first, p.second);
	}
	ui->comboBox->addItem("Ajouter...", 0);
	ui->comboBox->setCurrentIndex(-1);
	ui->lblPasswd->hide();
	ui->edtPassword->hide();
}

void FormGestionPersonnes::on_comboBox_currentIndexChanged(int index)
{
	Q_UNUSED(index);
	personne.setId(-1);
    ui->btnEdit->hide();
	if (ui->comboBox->currentData().toInt() < 0) return;
	emit curUserChanged();
	if (ui->comboBox->currentData().toInt())
	{
		ui->lblPasswd->show();
		ui->edtPassword->show();
		ui->edtPassword->setFocus();
	}
	else
	{
		personne.setId(0);
		personne.setNom("");
		personne.setDateNaissance(QDateTime());
		personne.setDateDeces(QDateTime());
		personne.setPrenom("");
		on_btnEdit_clicked();
	}
}

void FormGestionPersonnes::on_btnEdit_clicked()
{
	if (personne.id() < 0)
		return;
	emit editPersonneRequested(personne);
}

void FormGestionPersonnes::on_edtPassword_editingFinished()
{
	personne = _dbManager->getPersonne(ui->comboBox->currentData().toInt(), ui->edtPassword->text());
	if (personne.isValid())
	{
		ui->lblPasswd->hide();
		ui->edtPassword->hide();
        ui->btnEdit->show();
        emit curUserChanged();
	}
}
