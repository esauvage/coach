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
  , _dbManager(nullptr)
  , _personneId(-1)
{
	ui->setupUi(this);
	_dbManager = static_cast<CoachApplication *>(QApplication::instance())->dbManager();
	populate();
	connect(ui->lstTodo->itemDelegate(), SIGNAL(commitData(QWidget*)),
			this, SLOT(onCommitData(QWidget*)));
	const QStringList headers({tr("Description")});

	TreeModel *model = new TreeModel(headers, "");
	const auto regExp = QRegularExpression("^$");

	auto proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(model);
	proxyModel->setFilterRegularExpression(regExp);
	proxyModel->setFilterKeyColumn(2);
	ui->treeTodo->setModel(proxyModel);
	const auto regExpDone = QRegularExpression(".+");
	auto proxyDoneModel = new QSortFilterProxyModel(this);
	proxyDoneModel->setSourceModel(model);
	proxyDoneModel->setFilterRegularExpression(regExpDone);
	proxyDoneModel->setFilterKeyColumn(2);
	ui->treeDone->setModel(proxyDoneModel);

	TaskDelegate *delegate = new TaskDelegate();
	ui->treeTodo->setItemDelegate(delegate);
    connect(ui->treeTodo->itemDelegate(), SIGNAL(commitData(QWidget*)),
            this, SLOT(onCommitData(QWidget*)));
    TaskDoneDelegate *taskDoneDelegate = new TaskDoneDelegate();
    ui->treeDone->setItemDelegate(taskDoneDelegate);
    ui->treeDone->hideColumn(1);
}

FormGestionTodo::~FormGestionTodo()
{
	delete ui;
}

void FormGestionTodo::setTodos(const QList<QPair<int, QString> > &todos)
{
	QAbstractItemModel *model = ui->treeTodo->model();
//	model->removeRows(0, model->rowCount());
	ui->lstTodo->clear();
	for (auto &s : todos)
	{
		QListWidgetItem * todo = new QListWidgetItem(s.second);
		todo->setData(Qt::UserRole, s.first);
		todo->setFlags(Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
		todo->setCheckState(Qt::Unchecked);
		ui->lstTodo->addItem(todo);
        model->insertRow(0);
        const QModelIndex child = model->index(0, 0);
		model->setData(child, s.second, Qt::EditRole);
		model->setData(child, Qt::Unchecked, Qt::CheckStateRole);
	}
	for (int column = 0; column < model->columnCount(); ++column)
	{
		ui->treeTodo->resizeColumnToContents(column);
		ui->treeDone->resizeColumnToContents(column);
	}
}

void FormGestionTodo::setDones(const QList<DoneTask> &dones)
{
	QAbstractItemModel *model = ui->treeTodo->model();
	ui->lstDone->clear();
	for (auto &s : dones)
	{
		QListWidgetItem * done = new QListWidgetItem(s.nom);
		done->setData(Qt::UserRole, s.id);
		done->setData(Qt::UserRole + 1, s.date);
		done->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
		done->setCheckState(Qt::Checked);
		ui->lstDone->addItem(done);
		model->insertRow(0);
		QModelIndex child = model->index(0, 0);
		model->setData(child, s.nom, Qt::EditRole);
		child = model->index(0, 2);
		model->setData(child, s.date, Qt::EditRole);
	}
}

void FormGestionTodo::setPersonneId(int id)
{
	_personneId = id;
	populate();
}

void FormGestionTodo::on_btnAjout_clicked()
{
	QListWidgetItem * todo = new QListWidgetItem("");
	todo->setFlags(Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
	todo->setCheckState(Qt::Unchecked);
	todo->setData(Qt::UserRole, 0);
	ui->lstTodo->addItem(todo);
	ui->lstTodo->setEditTriggers(ui->lstTodo->editTriggers()|QAbstractItemView::CurrentChanged);
	ui->lstTodo->setCurrentItem(todo);
	ui->lstTodo->setEditTriggers(ui->lstTodo->editTriggers()&~QAbstractItemView::CurrentChanged);
	QAbstractItemModel *model = ui->treeTodo->model();
    model->insertRow(0);
}

void FormGestionTodo::onCommitData( QWidget* editor )
{
	Q_UNUSED(editor);
    TaskDelegate * s = dynamic_cast<TaskDelegate *>(sender());
    if (s)
    {
        return;
    }
	for (auto &s : ui->lstTodo->findItems("", Qt::MatchContains))
	{
		if (s->data(Qt::UserRole).toInt()>0) _dbManager->modifTodo(s->data(Qt::UserRole).toInt(),
														 s->text());
		else
		{
			s->setData(Qt::UserRole, _dbManager->addTodo(s->text(), _personneId));
		}
	}
}

void FormGestionTodo::populate()
{
	ui->lstTodo->clear();
	if (_personneId <= 0) return;
	auto todos = _dbManager->getTodos(_personneId);
	setTodos(todos);
	setDones(_dbManager->getDones(_personneId));
}

void FormGestionTodo::on_lstTodo_itemChanged(QListWidgetItem *item)
{
	if (item->checkState() != Qt::Checked) return;
	ui->lstTodo->takeItem(ui->lstTodo->row(item));
	_dbManager->supprimeTodo(item->data(Qt::UserRole).toInt());
	item->setData(Qt::UserRole+1, QDateTime::currentDateTime());
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui->lstDone->addItem(item);
	item->setData(Qt::UserRole, _dbManager->addDone(item->text(), item->data(Qt::UserRole + 1).toDateTime(),
						_personneId));
	QAbstractItemModel *model = ui->treeTodo->model();
	QModelIndexList items = model->match(
				model->index(0, 0),
				Qt::DisplayRole,
				item->text(),
				1,
				Qt::MatchRecursive);
	if (items.isEmpty()) return;
	const QModelIndex index = items.first();
	model->removeRow(index.row());
}

void FormGestionTodo::on_lstDone_itemChanged(QListWidgetItem *item)
{
	if (item->checkState() != Qt::Unchecked) return;
	ui->lstDone->takeItem(ui->lstDone->row(item));
	_dbManager->supprimeDone(item->data(Qt::UserRole).toInt());
	item->setFlags(item->flags()|Qt::ItemIsEditable);
	ui->lstTodo->addItem(item);
	item->setData(Qt::UserRole, _dbManager->addTodo(item->text(),
						_personneId));
	QAbstractItemModel *model = ui->treeTodo->model();
    model->insertRow(0);
    const QModelIndex child = model->index(0, 0);
	model->setData(child, item->text(), Qt::EditRole);
	model->setData(child, Qt::Unchecked, Qt::CheckStateRole);
}
