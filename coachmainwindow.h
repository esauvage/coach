#ifndef COACHMAINWINDOW_H
#define COACHMAINWINDOW_H

#include <QMainWindow>

#include <QList>

#include "personne.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CoachMainWindow; }
QT_END_NAMESPACE

class CoachMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CoachMainWindow(QWidget *parent = nullptr);
    ~CoachMainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CoachMainWindow *ui;
    QList <Personne> _personnes;
    QWidget * _accueil;
};
#endif // COACHMAINWINDOW_H
