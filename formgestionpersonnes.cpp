#include "formgestionpersonnes.h"
#include "ui_formgestionpersonnes.h"

#include <QDialogButtonBox>
#include <QSettings>

#include "formeditpersonne.h"
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
}

FormGestionPersonnes::~FormGestionPersonnes()
{
	QSettings settings;
	settings.setValue("lastUser", personne.id());
	delete ui;
}

void FormGestionPersonnes::on_btnAjout_clicked()
{
//    if (!_formEdtPers)
//    {
//        _formEdtPers = new FormEditPersonne(personne);
//    }
//    ui->verticalLayout->addWidget(_formEdtPers);
//    if (!_hlayout)
//    {
//        QPushButton * btnValider = new QPushButton("Valider");
//        QPushButton * btnAnnuler = new QPushButton("Annuler");
//        connect(btnValider, SIGNAL(clicked()), this, SLOT(ajoutValide()));
//        connect(btnAnnuler, SIGNAL(clicked()), this, SLOT(ajoutAnnule()));
//        _hlayout = new QDialogButtonBox();
//        _hlayout->addButton(btnValider, QDialogButtonBox::ActionRole);
//        _hlayout->addButton(btnAnnuler, QDialogButtonBox::ActionRole);
//    }
//    ui->verticalLayout->addWidget(_hlayout);
}

void FormGestionPersonnes::ajoutAnnule()
{
//    ui->verticalLayout->removeWidget(_formEdtPers);
//    delete _formEdtPers;
//    _formEdtPers = nullptr;
//    ui->verticalLayout->removeWidget(_hlayout);
//    delete _hlayout;
//    _hlayout = nullptr;
    update();
}

void FormGestionPersonnes::ajoutValide()
{
    _dbManager->addPersonne(_formEdtPers->personne());
//    ui->btnAjout->show();
//    ui->verticalLayout->removeWidget(_formEdtPers);
//    delete _formEdtPers;
//    _formEdtPers = nullptr;
//    ui->verticalLayout->removeWidget(_hlayout);
//    delete _hlayout;
//    _hlayout = nullptr;
    populateComboBox();
    update();
}

void FormGestionPersonnes::modifValide()
{
    _dbManager->modifPersonne(_formEdtPers->personne());
//    ui->btnAjout->show();
//    ui->verticalLayout->removeWidget(_formEdtPers);
//    delete _formEdtPers;
//    _formEdtPers = nullptr;
//    ui->verticalLayout->removeWidget(_hlayout);
//    delete _hlayout;
//    _hlayout = nullptr;
    populateComboBox();
    update();
}

void FormGestionPersonnes::populateComboBox()
{
	ui->comboBox->clear();
	QList<QPair<QString, int> > personnes = _dbManager->getNomPersonnes();
    for (auto &p : personnes)
	{
		ui->comboBox->addItem(p.first, p.second);
	}
	ui->comboBox->addItem("Ajouter...", -1);
	ui->comboBox->setCurrentIndex(-1);
}

void FormGestionPersonnes::on_comboBox_currentIndexChanged(int index)
{
	Q_UNUSED(index);
	personne.setId(-1);
	if (ui->comboBox->currentData().toInt() < 0) return;
	ui->edtPassword->show();
	ui->edtPassword->setFocus();
	emit curUserChanged();
}

void FormGestionPersonnes::on_btnEdit_clicked()
{
	if (personne.id() <= 0)
		return;
	emit editPersonneRequested(personne);
}

void FormGestionPersonnes::on_edtPassword_editingFinished()
{
	personne = _dbManager->getPersonne(ui->comboBox->currentData().toInt(), ui->edtPassword->text());
//    ui->verticalLayout->addWidget(_formEdtPers);
//    if (!_hlayout)
//    {
//        QPushButton * btnValider = new QPushButton("Modifier");
//        QPushButton * btnAnnuler = new QPushButton("Annuler");
//        connect(btnValider, SIGNAL(clicked()), this, SLOT(modifValide()));
//        connect(btnAnnuler, SIGNAL(clicked()), this, SLOT(ajoutAnnule()));
//        _hlayout = new QDialogButtonBox();
//        _hlayout->addButton(btnValider, QDialogButtonBox::ActionRole);
//        _hlayout->addButton(btnAnnuler, QDialogButtonBox::ActionRole);
//    }
//    ui->verticalLayout->addWidget(_hlayout);
}

