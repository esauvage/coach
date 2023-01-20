#include "coachmainwindow.h"
#include "ui_coachmainwindow.h"

#include "formeditpersonne.h"
#include "formgestiontodo.h"
#include "formgestionseances.h"

#include <QGridLayout>

CoachMainWindow::CoachMainWindow(QWidget *parent)
    : QMainWindow(parent)
	, ui(new Ui::CoachMainWindow)
	, _formEditPersonne(nullptr)
	, _formGestTodo(nullptr)
	, _formGestSeances(nullptr)
{
    ui->setupUi(this);
    ui->tabWidget->hide();
    connect(ui->login, SIGNAL(curUserChanged()),
			this, SLOT(onCurUserChanged()));
	connect(ui->login, SIGNAL(editPersonneRequested(Personne&)),
			this, SLOT(onEditPersonneRequested(Personne&)));
}

CoachMainWindow::~CoachMainWindow()
{
    delete ui;
}

void CoachMainWindow::onEditPersonneRequested(Personne & p)
{
	if (_formGestTodo)
	{
		delete _formGestTodo;
		_formGestTodo = nullptr;
	}
	if (_formGestSeances)
	{
		delete _formGestSeances;
		_formGestSeances = nullptr;
	}
	if (!_formEditPersonne)
	{
		_formEditPersonne = new FormEditPersonne(p);
		connect(_formEditPersonne, SIGNAL(finished()), this, SLOT(onEditPersonFinished()));
		QGridLayout * l = dynamic_cast<QGridLayout *>(centralWidget()->layout());
		l->addWidget(_formEditPersonne, 1, 0);
	}
	else
	{
		_formEditPersonne->setPersonne(p);
	}
}

void CoachMainWindow::onCurUserChanged()
{
	delete _formEditPersonne;
	_formEditPersonne = nullptr;
	if (_formGestTodo) delete _formGestTodo;
	_formGestTodo = nullptr;
	if (_formGestSeances) delete _formGestSeances;
	_formGestSeances = nullptr;
    if (ui->login->curPersonId() <= 0)
    {
        ui->tabWidget->hide();
        return;
    }
    ui->tabWidget->show();
	_formGestTodo = new FormGestionTodo();
	QGridLayout * l = dynamic_cast<QGridLayout *>(ui->tabTodo->layout());
	if (!l)
	{
		l = new QGridLayout(ui->tabTodo);
	}
	l->addWidget(_formGestTodo, 1, 0);
	_formGestTodo->setPersonneId(ui->login->curPersonId());
	_formGestSeances = new FormGestionSeances();
	l = dynamic_cast<QGridLayout *>(ui->tabSeances->layout());
	if (!l)
	{
		l = new QGridLayout(ui->tabSeances);
	}
	l->addWidget(_formGestSeances, 1, 0);
	_formGestSeances->setPersonneId(ui->login->curPersonId());
}

void CoachMainWindow::onEditPersonFinished()
{
	ui->login->reload();
	onCurUserChanged();
}
