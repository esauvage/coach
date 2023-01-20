#ifndef FORMGESTIONSEANCES_H
#define FORMGESTIONSEANCES_H

#include <QWidget>

#include "seance.h"

namespace Ui {
class FormGestionSeances;
}

class FormEditSeance;
class QDialogButtonBox;
class DbManager;

class FormGestionSeances : public QWidget
{
    Q_OBJECT

public:
    explicit FormGestionSeances(QWidget *parent = nullptr);
    ~FormGestionSeances();
	void setPersonneId(int id);

private slots:
    void on_btnAjout_clicked();
    void ajoutAnnule();
    void ajoutValide();

private:
    Ui::FormGestionSeances *ui;
    FormEditSeance * _formEdtSeance = nullptr;
    QDialogButtonBox * _hlayout = nullptr;
    DbManager * _dbManager = nullptr;
	int _personneId;
	Seance _seance;
};

#endif // FORMGESTIONSEANCES_H
