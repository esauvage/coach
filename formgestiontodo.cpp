#include "formgestiontodo.h"
#include "ui_formgestiontodo.h"

#include "coachapplication.h"
#include "dbmanager.h"

#include <QSortFilterProxyModel>

#include "treemodel.h"
#include "taskdelegate.h"
#include "taskdonedelegate.h"
#include "mysortfilterproxymodel.h"

FormGestionTodo::FormGestionTodo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FormGestionTodo)
  , _dbManager(nullptr)
  , _personneId(-1)
  , _initialized(false)
{
	ui->setupUi(this);
	_dbManager = static_cast<CoachApplication *>(QApplication::instance())->dbManager();
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
    auto proxyDoneModel = new MySortFilterProxyModel(this);
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
    populate();
    ui->treeDone->update();
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
	_initialized = false;
	if (_personneId <= 0) return;
//    QAbstractItemModel *model = ui->treeTodo->model();
//    for (int column = 0; column < model->columnCount(); ++column)
//    {
//        ui->treeTodo->resizeColumnToContents(column);
//        ui->treeDone->resizeColumnToContents(column);
//    }
    _initialized = true;
}

void FormGestionTodo::onTodoChanged(QModelIndex topLeft, QModelIndex bottomRight,
                                    QList<int> roles)
{
    Q_UNUSED(roles);
    Q_UNUSED(bottomRight);
    if (!_initialized) return;
	auto index = topLeft;
//	for(auto index = topLeft; index <= bottomRight; index = index.sibling(index.row()+1, 0))
	{
		if (index.data(Qt::CheckStateRole) == Qt::Unchecked)
		{
            _dbManager->supprimeDone(index.data(Qt::UserRole).toInt());
            auto id = _dbManager->addTodo(index.data(Qt::EditRole).toString(),
								_personneId);

//            QAbstractItemModel *model = ui->treeDone->model();
//            QModelIndexList items = model->match(
//                        model->index(0, 0),
//                        Qt::UserRole,
//                        index.data(Qt::UserRole).toInt(),
//                        1,
//                        Qt::MatchRecursive);
//            if (items.isEmpty()) return;
//            auto index1 = items.first();
//            model->setData(index1, id, Qt::UserRole);
		}
		else
		{
			_dbManager->supprimeTodo(index.data(Qt::UserRole).toInt());
            QDateTime date = QDateTime::currentDateTime();
            auto id = _dbManager->addDone(index.data(Qt::EditRole).toString(),
                                date,
								_personneId);
//            QAbstractItemModel *model = ui->treeTodo->model();
//            QModelIndexList items = model->match(
//                        model->index(0, 0),
//                        Qt::UserRole,
//                        index.data(Qt::UserRole).toInt(),
//                        1,
//                        Qt::MatchRecursive);
//            if (items.isEmpty()) return;
//            auto index1 = items.first();
//            model->setData(index1, id, Qt::UserRole);
//            model->setData(index1.siblingAtColumn(2), date, Qt::DisplayRole);
//            for (int column = 0; column < model->columnCount(); ++column)
//            {
//                ui->treeDone->resizeColumnToContents(column);
//            }
        }
	}
}
