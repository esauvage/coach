#ifndef FORMGESTIONTODO_H
#define FORMGESTIONTODO_H

#include <QWidget>
#include <QModelIndex>

#include "treemodel.h"

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
    void supprTodo();

    void onTodoKeyReleased(QKeyEvent *event);
    void on_pushButton_clicked();

private:
	void populate();

	Ui::FormGestionTodo *ui;
	int _personneId;
    TreeModel *model;
    QAction *supprTodoAct;
};

#endif // FORMGESTIONTODO_H
