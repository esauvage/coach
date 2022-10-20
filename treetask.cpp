
/*
	TreeTask.cpp

	A container for items of data supplied by the simple tree model.
*/

#include "treetask.h"

//! [0]
TreeTask::TreeTask(const QHash<int, QVector<QVariant> >&data, TreeTask *parent)
	: itemData(data),
	  parentItem(parent)
{}
//! [0]

//! [1]
TreeTask::~TreeTask()
{
	qDeleteAll(childItems);
}
//! [1]

//! [2]
TreeTask *TreeTask::child(int number)
{
	if (number < 0 || number >= childItems.size())
		return nullptr;
	return childItems.at(number);
}
//! [2]

//! [3]
int TreeTask::childCount() const
{
	return childItems.count();
}
//! [3]

//! [4]
int TreeTask::childNumber() const
{
	if (parentItem)
		return parentItem->childItems.indexOf(const_cast<TreeTask*>(this));
	return 0;
}
//! [4]

//! [5]
int TreeTask::columnCount() const
{
	return itemData.count();
}
//! [5]

//! [6]
QVariant TreeTask::data(int column, int role) const
{
	switch (role)
	{
	case Qt::EditRole:
	case Qt::DisplayRole:
		return _nom;
	case Qt::CheckStateRole:
		return _date.isValid();
	default:
		return QVariant();
	}

	if (column < 0 || column >= itemData[Qt::EditRole].size())
		return QVariant();
	if (!itemData.keys().contains(role))
		return QVariant();
	return itemData[role].at(column);
}
//! [6]

//! [7]
bool TreeTask::insertChildren(int position, int count, int columns)
{
	Q_UNUSED(columns);
	if (position < 0 || position > childItems.size())
		return false;

	for (int row = 0; row < count; ++row) {
		QHash<int, QVector<QVariant> > data;
		data[Qt::CheckStateRole] << QVariant();
		data[Qt::EditRole] << QVariant();
		TreeTask *item = new TreeTask(data, this);
		childItems.insert(position, item);
	}

	return true;
}
//! [7]

//! [8]
bool TreeTask::insertColumns(int position, int columns)
{
	if (position < 0 || position > itemData[Qt::EditRole].size())
		return false;

	for (int column = 0; column < columns; ++column)
	{
		itemData[Qt::EditRole].insert(position, QVariant());
		itemData[Qt::CheckStateRole].insert(position, QVariant());
	}
	for (TreeTask *child : qAsConst(childItems))
		child->insertColumns(position, columns);

	return true;
}
//! [8]

//! [9]
TreeTask *TreeTask::parent()
{
	return parentItem;
}
//! [9]

//! [10]
bool TreeTask::removeChildren(int position, int count)
{
	if (position < 0 || position + count > childItems.size())
		return false;

	for (int row = 0; row < count; ++row)
		delete childItems.takeAt(position);

	return true;
}
//! [10]

bool TreeTask::removeColumns(int position, int columns)
{
	if (position < 0 || position + columns > itemData[Qt::EditRole].size())
		return false;

	for (int column = 0; column < columns; ++column)
	{
		itemData[Qt::EditRole].remove(position);
		itemData[Qt::CheckStateRole].remove(position);
	}
	for (TreeTask *child : qAsConst(childItems))
		child->removeColumns(position, columns);

	return true;
}

//! [11]
bool TreeTask::setData(int column, const QVariant &value, int role)
{
	switch (role)
	{
	case Qt::EditRole:
	case Qt::DisplayRole:
		setNom(value.toString());
		break;
	case Qt::CheckStateRole:
		setDate(value.toInt() == Qt::Checked ? QDateTime::currentDateTime() : QDateTime());
		break;
	default:
		return false;
	}
	return true;
	if (column < 0 || column >= itemData[role].size())
		return false;

	itemData[role][column] = value;
	return true;
}
//! [11]

//! [12]

bool TreeTask::setId(int v)
{
	_id = v;
	return true;
}

int TreeTask::id() const
{
	return _id;
}

bool TreeTask::setNom(const QString &v)
{
	_nom = v;
	return true;
}

QString TreeTask::nom() const
{
	return _nom;
}

bool TreeTask::setDate(const QDateTime &d)
{
	_date = d;
	return true;
}

QDateTime TreeTask::date() const
{
	return _date;
}

const QString &TreeTask::recurrence() const
{
	return _recurrence;
}

void TreeTask::setRecurrence(const QString &newRecurrence)
{
	_recurrence = newRecurrence;
}
//! [12]
