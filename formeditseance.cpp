#include "formeditseance.h"
#include "ui_formeditseance.h"

FormEditSeance::FormEditSeance(Seance & seance, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormEditSeance),
    _seance(seance)
{
    ui->setupUi(this);
}

FormEditSeance::~FormEditSeance()
{
    delete ui;
}

Seance &FormEditSeance::seance() const
{
    return _seance;
}

void FormEditSeance::setSeance(const Seance &seance)
{
    _seance = seance;
}
