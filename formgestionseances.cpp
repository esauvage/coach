#include "formgestionseances.h"
#include "ui_formgestionseances.h"

#include <QDialogButtonBox>

#include "formeditseance.h"
#include "coachapplication.h"
#include "dbmanager.h"

FormGestionSeances::FormGestionSeances(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGestionSeances),
    _formEdtSeance(new FormEditSeance(_seance))

{
    ui->setupUi(this);
    _dbManager = static_cast<CoachApplication *>(QApplication::instance())->dbManager();
    ui->verticalLayout->addWidget(_formEdtSeance);
    connect(_formEdtSeance, &FormEditSeance::changed, this, &FormGestionSeances::onChanged);
}

FormGestionSeances::~FormGestionSeances()
{
    delete ui;
    delete _formEdtSeance;
}


void FormGestionSeances::setPersonneId(int id)
{
	_personneId = id;
    _seance.setPersonneId(id);
    ui->cbxSeances->clear();
    auto seances = _dbManager->getSeances(id);
    for (auto i : seances)
    {
        ui->cbxSeances->addItem(QString("Le %1 de %2 à %3").arg(i.date().toString()).arg(i.debut().toString()).arg(i.fin().toString()),i.id());
    }
}

void FormGestionSeances::on_btnAjout_clicked()
{
    ui->btnAjout->hide();
    _seance=Seance();
    _seance.setDate(QDate::currentDate());
    _seance.setFin(QTime::currentTime());
    _seance.setDebut(_seance.fin().addSecs(-15*60));
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
    _seance = _dbManager->getSeance(ui->cbxSeances->currentData().toInt());
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
    setPersonneId(_seance.personneId());
}

void FormGestionSeances::on_cbxSeances_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if (ui->cbxSeances->count() < 1) return;
    if (ui->cbxSeances->currentData().toInt() > 0)
        _formEdtSeance->setSeance(_dbManager->getSeance(ui->cbxSeances->currentData().toInt()));
}

void FormGestionSeances::onChanged()
{
    const Seance & seance = _formEdtSeance->seance();
    _dbManager->modifSeance(seance);
    ui->cbxSeances->setItemText(ui->cbxSeances->currentIndex(), QString("Le %1 de %2 à %3").arg(seance.date().toString())
                                .arg(seance.debut().toString()).arg(seance.fin().toString()));
}

