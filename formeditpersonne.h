#ifndef FORMEDITPERSONNE_H
#define FORMEDITPERSONNE_H

#include <QWidget>
#include <QLineEdit>

#include "personne.h"

namespace Ui {
class FormEditPersonne;
}

class DbManager;

class FormEditPersonne : public QWidget
{
    Q_OBJECT

public:
    explicit FormEditPersonne(Personne & personne, QWidget *parent = nullptr);
    ~FormEditPersonne();
    void setPersonne(Personne &personne);

    Personne &personne() const;

signals:
	void finished();

private slots:
    void on_edtNom_editingFinished();
    void prenomsEdited();
    void on_edtNaissance_editingFinished();
    void on_edtDeces_editingFinished();
	void on_btnChangePasswd_clicked();
	void on_btnChangePerson_clicked();
	void on_pushButton_2_clicked();
	void on_btnSuppr_clicked();
	void on_btnAnnuler_clicked();

private:
    Ui::FormEditPersonne *ui;
    Personne & _personne;
    QList <QLineEdit *>_edtPrenoms;
	DbManager * _dbManager;
};

#endif // FORMEDITPERSONNE_H
