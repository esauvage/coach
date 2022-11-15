#include "formgestiontodo.h"
#include "ui_formgestiontodo.h"

#include "coachapplication.h"
#include "dbmanager.h"

#include <QSortFilterProxyModel>

#include "treemodel.h"
#include "taskdelegate.h"
#include "taskdonedelegate.h"

FormGestionTodo::FormGestionTodo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FormGestionTodo)
{
	ui->setupUi(this);
    const QStringList headers({tr("Description"), tr(""), tr("Date")});

    TreeModel *model = new TreeModel(headers);
	const auto regExp = QRegularExpression("^$");

	auto proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(model);
	proxyModel->setFilterRegularExpression(regExp);
	proxyModel->setFilterKeyColumn(2);
	ui->treeTodo->setModel(proxyModel);
	ui->treeTodo->hideColumn(2);
	const auto regExpDone = QRegularExpression(".+");
	auto proxyDoneModel = new QSortFilterProxyModel(this);
	proxyDoneModel->setSourceModel(model);
	proxyDoneModel->setFilterRegularExpression(regExpDone);
	proxyDoneModel->setFilterKeyColumn(2);
	ui->treeDone->setModel(proxyDoneModel);
//    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QList<int>)),
//            this, SLOT(onTodoChanged(QModelIndex,QModelIndex,QList<int>)));

//	TaskDelegate *delegate = new TaskDelegate();
//	ui->treeTodo->setItemDelegate(delegate);
//    TaskDoneDelegate *taskDoneDelegate = new TaskDoneDelegate();
//    ui->treeDone->setItemDelegate(taskDoneDelegate);
    ui->treeDone->hideColumn(1);
}

FormGestionTodo::~FormGestionTodo()
{
	delete ui;
}

void FormGestionTodo::setPersonneId(int id)
{
//	_personneId = id;
    TreeModel *model = static_cast<TreeModel*>(static_cast<QSortFilterProxyModel * >(ui->treeTodo->model())->sourceModel());
    model->populate(id);
	populate();
}

void FormGestionTodo::on_btnAjout_clicked()
{
	QAbstractItemModel *model = ui->treeTodo->model();
    model->insertRow(0);
}

void FormGestionTodo::populate()
{
    QAbstractItemModel *model = ui->treeTodo->model();
    for (int column = 0; column < model->columnCount(); ++column)
    {
        ui->treeTodo->resizeColumnToContents(column);
        ui->treeDone->resizeColumnToContents(column);
    }
}
