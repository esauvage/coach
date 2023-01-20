#ifndef FORMEDITSEANCE_H
#define FORMEDITSEANCE_H

#include <QWidget>

#include "seance.h"

namespace Ui {
class FormEditSeance;
}

class FormEditSeance : public QWidget
{
    Q_OBJECT

public:
    explicit FormEditSeance(Seance & seance, QWidget *parent = nullptr);
    ~FormEditSeance();

    Seance &seance() const;
    void setSeance(const Seance &seance);
signals:
    void changed();
    void activiteChanged();
private slots:
    void on_edtDate_editingFinished();

    void on_edtDebut_editingFinished();

    void on_edtFin_editingFinished();

    void on_cbxActivite_editTextChanged(const QString &arg1);

private:
    Ui::FormEditSeance *ui;
    Seance & _seance;
};

#endif // FORMEDITSEANCE_H
