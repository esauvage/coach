#ifndef FORMGESTIONSEANCES_H
#define FORMGESTIONSEANCES_H

#include <QWidget>

namespace Ui {
class FormGestionSeances;
}

class FormGestionSeances : public QWidget
{
    Q_OBJECT

public:
    explicit FormGestionSeances(QWidget *parent = nullptr);
    ~FormGestionSeances();

private:
    Ui::FormGestionSeances *ui;
};

#endif // FORMGESTIONSEANCES_H
