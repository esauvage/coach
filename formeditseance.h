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

private:
    Ui::FormEditSeance *ui;
    Seance & _seance;
};

#endif // FORMEDITSEANCE_H
