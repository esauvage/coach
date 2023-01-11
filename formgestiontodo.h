#ifndef FORMGESTIONTODO_H
#define FORMGESTIONTODO_H

#include <QWidget>
#include <QModelIndex>

#include "dbmanager.h"

namespace Ui {
class FormGestionTodo;
}

class QListWidgetItem;
class DbManager;

class FormGestionTodo : public QWidget
{
	Q_OBJECT

public:
	explicit FormGestionTodo(QWidget *parent = nullptr);
	~FormGestionTodo();
	void setPersonneId(int id);

private slots:
	void on_btnAjout_clicked();

private:
	void populate();

	Ui::FormGestionTodo *ui;
	int _personneId;
    DbManager *_dbManager;
    bool _initialized;
};

#endif // FORMGESTIONTODO_H
