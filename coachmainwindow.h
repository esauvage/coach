#ifndef COACHMAINWINDOW_H
#define COACHMAINWINDOW_H

#include <QMainWindow>

class Personne;
class FormEditPersonne;
class FormGestionTodo;
class FormGestionSeances;

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
	void onEditPersonneRequested(Personne & p);
	void onCurUserChanged();
	void onEditPersonFinished();

private:
    Ui::CoachMainWindow *ui;
	FormEditPersonne *_formEditPersonne;
	FormGestionTodo * _formGestTodo;
	FormGestionSeances * _formGestSeances;
};
#endif // COACHMAINWINDOW_H
