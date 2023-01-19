
#include "treemodel.h"
#include "treetask.h"

#include "coachapplication.h"

#include <QtWidgets>

//! [0]
TreeModel::TreeModel(const QStringList &headers, QObject *parent)
	: QAbstractItemModel(parent),
	  _personneId(-1)
{
    Q_UNUSED(headers);
	_dbManager = static_cast<CoachApplication *>(QApplication::instance())->dbManager();
	rootItem = new TreeTask();
    auto i = 0;
    for (auto header : headers)
    {
        setHeaderData(i++, Qt::Horizontal, header);
    }
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &TreeModel::onTimeout);
    timer->start(1000);
}
//! [0]

//! [1]
TreeModel::~TreeModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}
//! [2]

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
	TreeTask *item = getItem(index);
	return item->data(index.column(), role);
}

//! [3]
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (index.column())
    {
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }
    else {
        return Qt::ItemIsUserCheckable | Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }
}
//! [3]

//! [4]
TreeTask *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
		TreeTask *item = static_cast<TreeTask*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
//! [4]

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//! [5]
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
    {
        return QModelIndex();
    }
//! [5]

//! [6]
	TreeTask *parentItem = getItem(parent);
    if (!parentItem)
    {
        return QModelIndex();
    }

	TreeTask *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}
//! [6]

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	TreeTask *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

	TreeTask *childItem = getItem(index);
	TreeTask *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    if (!rows) return true;
    TreeTask * parentItem = getItem(QModelIndex());
    if (!parentItem)
        return false;
    beginRemoveRows(parent, position, position + rows - 1);
    for (auto i = position; i < position + rows; ++i)
    {
        TreeTask *item = getItem(index(i, 0));
        if (!item)
            continue;
        _dbManager->supprimeTodo(item->id());
    }
    bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();
    emit dataChanged(parent, parent.sibling(position+rows, parentItem->columnCount()-1), {Qt::DisplayRole});
    return success;
}

void TreeModel::populate(int personneId)
{
	_personneId = personneId;
	removeRows(0, rowCount());
	if (_personneId <= 0) return;
    setDones(_dbManager->getTodos(_personneId));
    setDones(_dbManager->getDones(_personneId));
    emit dataChanged(index(0, 0), index(rowCount()-1, columnCount()-1), {Qt::DisplayRole});
}

void TreeModel::onTimeout()
{
	for (auto row = 0 ; row < rowCount(); ++row)
	{
		TreeTask * task = getItem(index(row, 0));
		task->setElapsedTime(task->date().secsTo(QDateTime::currentDateTime()));
	}
}

//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{
	const TreeTask *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}
//! [8]

bool TreeModel::setData(const QModelIndex &current, const QVariant &value, int role)
{
    if (role != Qt::EditRole && role != Qt::CheckStateRole && role != Qt::UserRole)
    {
        return false;
    }

	TreeTask *item = getItem(current);
	bool result = item->setData(current.column(), value, role);

    if (result)
	{
		if (role == Qt::CheckStateRole)
		{
            if (value != Qt::CheckState::Checked)
			{
				_dbManager->supprimeDone(item->id());
				if (item->recurrence().isEmpty())
				{
					item->setId(_dbManager->addTodo(item->nom(),
									_personneId));
				}
			}
			else
			{
				item->setDate(QDateTime::currentDateTime());
				if (item->recurrence().isEmpty())
				{
					_dbManager->supprimeTodo(item->id());
				}
				item->setId(_dbManager->addDone(item->nom(),
									item->date(),
									_personneId));
			}
		}
		else
		{
			if (item->id() <= 0)
			{
				item->setId(_dbManager->addTodo(item->nom(),
									_personneId));
			}
			if (!item->date().isValid())
			{
				_dbManager->modifTodo(*item);
			}
		}
		emit dataChanged(current, current, {Qt::DisplayRole, role});
	}
    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void TreeModel::setDones(const QList<TreeTask> &dones)
{
    TreeTask *parentItem = getItem(QModelIndex());
    if (!parentItem)
        return;
    beginInsertRows(QModelIndex(), 0, dones.size());
    for (auto &s : dones)
    {
        parentItem->insertChild(s);
    }
    endInsertRows();
}

TreeTask * TreeModel::getLastDoneItem(const QString &nom) const
{
	TreeTask * r = nullptr;
	for (auto i : rootItem->childItems())
	{
		if ((i->nom() == nom) && i->date().isValid())
		{
			if (!r)
			{
				r = i;
				continue;
			}
			if (i->date() > r->date())
			{
				r = i;
			}
		}
	}
	return r;
}
