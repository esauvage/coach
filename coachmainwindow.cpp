#include "coachmainwindow.h"
#include "ui_coachmainwindow.h"

#include "formeditpersonne.h"

#include <QGridLayout>

CoachMainWindow::CoachMainWindow(QWidget *parent)
    : QMainWindow(parent)
	, ui(new Ui::CoachMainWindow)
	, _formEditPersonne(nullptr)
{
    ui->setupUi(this);
	connect(ui->login, SIGNAL(curUserChanged()),
			this, SLOT(onCurUserChanged()));
	connect(ui->login, SIGNAL(editPersonneRequested(Personne &)),
			this, SLOT(onEditPersonneRequested(Personne &)));
}

CoachMainWindow::~CoachMainWindow()
{
    delete ui;
}

void CoachMainWindow::onEditPersonneRequested(Personne & p)
{
	if (!_formEditPersonne)
	{
		_formEditPersonne = new FormEditPersonne(p);
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
}
