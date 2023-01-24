#ifndef FORMEDITSEANCE_H
#define FORMEDITSEANCE_H

#include <QWidget>

#include "seance.h"
#include "dbmanager.h"

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
//    void activiteChanged();
private slots:
    void on_edtDate_editingFinished();

    void on_edtDebut_editingFinished();

    void on_edtFin_editingFinished();

    void activiteChanged();

private:
    Ui::FormEditSeance *ui;
    Seance & _seance;
    DbManager *_dbManager = nullptr;
};

#endif // FORMEDITSEANCE_H
