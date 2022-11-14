
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
	TreeTask *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

	return success;
}

void TreeModel::populate(int personneId)
{
	_personneId = personneId;
	removeRows(0, rowCount());
	if (_personneId <= 0) return;
    setTodos(_dbManager->getTodos(_personneId));
    setDones(_dbManager->getDones(_personneId));
	emit dataChanged(index(0, 0), index(rowCount()-1, columnCount()-1), {Qt::DisplayRole});
}

//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{
	const TreeTask *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}
//! [8]

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole && role != Qt::CheckStateRole && role != Qt::UserRole)
    {
        return false;
    }

	TreeTask *item = getItem(index);
	bool result = item->setData(index.column(), value, role);

    if (result)
	{
		if (role == Qt::CheckStateRole)
		{
			if (index.data(Qt::CheckStateRole) == Qt::Unchecked)
			{
				_dbManager->supprimeDone(item->id());
				item->setId(_dbManager->addTodo(item->nom(),
									_personneId));
			}
			else
			{
				_dbManager->supprimeTodo(item->id());
				item->setDate(QDateTime::currentDateTime());
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
				_dbManager->modifTodo(item->id(), item->nom());
			}
		}
		emit dataChanged(index, index, {Qt::DisplayRole, role});
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

void TreeModel::setTodos(const QList<TreeTask> &todos)
{
    for (auto &s : todos)
    {
        insertRow(rowCount());

        const QModelIndex child = index(rowCount()-1, 0);
        TreeTask *item = getItem(child);
		item->setId(s.id());
		item->setNom(s.nom());
    }
}

void TreeModel::setDones(const QList<TreeTask> &dones)
{
    for (auto &s : dones)
    {
        insertRow(rowCount());
		const QModelIndex child = index(rowCount()-1, 0);
		TreeTask *item = getItem(child);
		item->setId(s.id());
		item->setNom(s.nom());
		item->setDate(s.date());
	 }
}
