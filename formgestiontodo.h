#ifndef FORMGESTIONTODO_H
#define FORMGESTIONTODO_H

#include <QWidget>

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
	void onCommitData(QWidget *editor);
	void on_lstTodo_itemChanged(QListWidgetItem *item);
	void on_lstDone_itemChanged(QListWidgetItem *item);

private:
	void setTodos(const QList<QPair<int, QString> >  &todos);
	void setDones(const QList<DoneTask> &dones);
	void populate();

	Ui::FormGestionTodo *ui;
	DbManager * _dbManager = nullptr;
	int _personneId;
};

#endif // FORMGESTIONTODO_H
