#include "formgestiontodo.h"
#include "ui_formgestiontodo.h"

#include "treemodel.h"
//#include "taskdelegate.h"
#include "taskdonedelegate.h"
#include "mysortfilterproxymodel.h"

FormGestionTodo::FormGestionTodo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FormGestionTodo)
  , _personneId(-1)
{
	ui->setupUi(this);
    const QStringList headers({tr("Description"), tr(""), tr("Date"), tr("Récurrence")});

    model = new TreeModel(headers);
    auto proxyModel = new MySortFilterProxyModel(this, true);
    proxyModel->setExcludeDates(true);
    proxyModel->setSourceModel(model);
	proxyModel->setFilterKeyColumn(2);
	ui->treeTodo->setModel(proxyModel);
    ui->treeTodo->hideColumn(2);
    auto proxyDoneModel = new MySortFilterProxyModel(this, false);
    proxyDoneModel->setExcludeDates(false);
    proxyDoneModel->setSourceModel(model);
	proxyDoneModel->setFilterKeyColumn(2);
	ui->treeDone->setModel(proxyDoneModel);

    TaskDoneDelegate *taskDoneDelegate = new TaskDoneDelegate();
    ui->treeDone->setItemDelegate(taskDoneDelegate);
    ui->treeDone->hideColumn(1);
}

FormGestionTodo::~FormGestionTodo()
{
	delete ui;
    delete model;
}

void FormGestionTodo::setPersonneId(int id)
{
    _personneId = id;
    model->populate(id);
}

void FormGestionTodo::on_btnAjout_clicked()
{
	QAbstractItemModel *model = ui->treeTodo->model();
    model->insertRow(0);
}
