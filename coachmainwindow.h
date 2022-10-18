#ifndef COACHMAINWINDOW_H
#define COACHMAINWINDOW_H

#include <QMainWindow>

class Personne;
class FormEditPersonne;

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

private:
    Ui::CoachMainWindow *ui;
	FormEditPersonne *_formEditPersonne;
};
#endif // COACHMAINWINDOW_H
