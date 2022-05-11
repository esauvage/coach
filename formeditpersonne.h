#ifndef FORMEDITPERSONNE_H
#define FORMEDITPERSONNE_H

#include <QWidget>
#include <QLineEdit>

#include "personne.h"

namespace Ui {
class FormEditPersonne;
}

class FormEditPersonne : public QWidget
{
    Q_OBJECT

public:
    explicit FormEditPersonne(Personne & personne, QWidget *parent = nullptr);
    ~FormEditPersonne();
    void setPersonne(Personne &personne);

private slots:
    void on_edtNom_editingFinished();

    void prenomsEdited();

    void on_edtNaissance_editingFinished();

    void on_edtDeces_editingFinished();

private:
    Ui::FormEditPersonne *ui;
    Personne & _personne;
    QList <QLineEdit *>_edtPrenoms;
};

#endif // FORMEDITPERSONNE_H
