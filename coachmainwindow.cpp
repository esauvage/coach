#include "coachmainwindow.h"
#include "ui_coachmainwindow.h"

#include "formeditpersonne.h"
#include "formgestiontodo.h"

#include <QGridLayout>

CoachMainWindow::CoachMainWindow(QWidget *parent)
    : QMainWindow(parent)
	, ui(new Ui::CoachMainWindow)
	, _formEditPersonne(nullptr)
	, _formGestTodo(nullptr)
{
    ui->setupUi(this);
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
	if (ui->login->curPersonId() <= 0) return;
	_formGestTodo = new FormGestionTodo();
	QGridLayout * l = dynamic_cast<QGridLayout *>(centralWidget()->layout());
	l->addWidget(_formGestTodo, 1, 0);
	_formGestTodo->setPersonneId(ui->login->curPersonId());
}

void CoachMainWindow::onEditPersonFinished()
{
	ui->login->reload();
	onCurUserChanged();
}
