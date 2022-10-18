#ifndef FORMGESTIONPERSONNES_H
#define FORMGESTIONPERSONNES_H

#include <QWidget>

#include "personne.h"

namespace Ui {
class FormGestionPersonnes;
}

class FormEditPersonne;
class QDialogButtonBox;
class DbManager;

class FormGestionPersonnes : public QWidget
{
    Q_OBJECT

public:
    explicit FormGestionPersonnes(QWidget *parent = nullptr);
    ~FormGestionPersonnes();

signals:
	void editPersonneRequested(Personne &personne);
	void curUserChanged();

private slots:
    void on_btnAjout_clicked();
    void ajoutAnnule();
    void ajoutValide();
    void modifValide();

    void on_comboBox_currentIndexChanged(int index);
	void on_btnEdit_clicked();
	void on_edtPassword_editingFinished();

private:
	void populateComboBox();

	Ui::FormGestionPersonnes *ui;
    FormEditPersonne * _formEdtPers = nullptr;
    QDialogButtonBox * _hlayout = nullptr;
	DbManager * _dbManager = nullptr;
	Personne personne;
};

#endif // FORMGESTIONPERSONNES_H
