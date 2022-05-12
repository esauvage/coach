#ifndef FORMGESTIONPERSONNES_H
#define FORMGESTIONPERSONNES_H

#include <QWidget>

#include "personne.h"

namespace Ui {
class FormGestionPersonnes;
}

class FormEditPersonne;
class QDialogButtonBox;

class FormGestionPersonnes : public QWidget
{
    Q_OBJECT

public:
    explicit FormGestionPersonnes(QWidget *parent = nullptr);
    ~FormGestionPersonnes();

private slots:
    void on_btnAjout_clicked();
    void ajoutAnnule();
    void ajoutValide();

private:
    Ui::FormGestionPersonnes *ui;
    FormEditPersonne * _formEdtPers = nullptr;
    QDialogButtonBox * _hlayout = nullptr;
    Personne personne;
};

#endif // FORMGESTIONPERSONNES_H
