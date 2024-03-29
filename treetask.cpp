
/*
	TreeTask.cpp

	A container for items of data supplied by the simple tree model.
*/

#include "treetask.h"

//! [0]
TreeTask::TreeTask(TreeTask *parent)
    :parentItem(parent),
      _date(QDateTime()), _elapsed(-1)
{}

TreeTask::TreeTask(const TreeTask &ref)
    :_childItems(ref.childItems()),
        parentItem(ref.parentItem),
      _nom(ref.nom()),
      _recurrence(ref.recurrence()),
      _date(ref.date()),
      _elapsed(ref.elapsed()),
      _id(ref.id())
{}
//! [0]

//! [1]
TreeTask::~TreeTask()
{
    qDeleteAll(_childItems);
}
//! [1]

//! [2]
TreeTask *TreeTask::child(int number)
{
    if (number < 0 || number >= _childItems.size())
		return nullptr;
    return _childItems.at(number);
}

QVector<TreeTask *> TreeTask::childItems() const
{
    return _childItems;
}
//! [2]

//! [3]
int TreeTask::childCount() const
{
    return _childItems.count();
}
//! [3]

//! [4]
int TreeTask::childNumber() const
{
	if (parentItem)
        return parentItem->childItems().indexOf(const_cast<TreeTask*>(this));
	return 0;
}
//! [4]

//! [5]
int TreeTask::columnCount() const
{
	return 4;
}
//! [5]

//! [6]
QVariant TreeTask::data(int column, int role) const
{
    if (column > columnCount()) return QVariant();
	switch (role)
	{
	case Qt::EditRole:
	case Qt::DisplayRole:
        switch (column)
        {
        case 0:
            return _nom;
        case 1:
            return _recurrence;
		case 2:
			return _date;
		case 3:
			return _elapsed;
		}
    case Qt::CheckStateRole:
        return column ? QVariant() : (_date.isValid() ? Qt::Checked : Qt::Unchecked);
    case Qt::UserRole:
        return _id;
    default:
		return QVariant();
	}
}
//! [6]

//! [7]
bool TreeTask::insertChildren(int position, int count, int columns)
{
	Q_UNUSED(columns);
    if (position < 0 || position > _childItems.size())
		return false;

	for (int row = 0; row < count; ++row) {
        TreeTask *item = new TreeTask(this);
        _childItems.insert(position, item);
	}
	return true;
}
//! [7]

//! [8]
bool TreeTask::insertColumns(int position, int columns)
{
    if (position < 0 || position > columnCount())
        return false;

    for (TreeTask *child : qAsConst(_childItems))
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
    if (position < 0 || position + count > _childItems.size())
		return false;

	for (int row = 0; row < count; ++row)
        delete _childItems.takeAt(position);

	return true;
}
//! [10]

bool TreeTask::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > columnCount())
        return false;

    for (TreeTask *child : qAsConst(_childItems))
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
        switch (column)
        {
        case 0 : setNom(value.toString()); break;
        case 1: setRecurrence(value.toString()); break;
        case 2: setDate(value.toDateTime()); break;
        }
		break;
	case Qt::CheckStateRole:
        if (column) return false;
        if (value.typeId()==QMetaType::QDateTime)
        {
            setDate(value.toDateTime());
            break;
        }
		setDate(value.toInt() == Qt::Checked ? QDateTime::currentDateTime() : QDateTime());
		break;
    case Qt::UserRole:
        setId(value.toInt());
        break;
	default:
		return false;
	}
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

void TreeTask::setElapsedTime(const qint64 v)
{
	if (_date.isValid())
	{
		_elapsed = v;
    }
}

qint64 TreeTask::elapsed() const
{
    return _elapsed;
}

void TreeTask::insertChild(const TreeTask &child)
{
    TreeTask * n = new TreeTask(child);
    _childItems << n;
}
//! [12]
