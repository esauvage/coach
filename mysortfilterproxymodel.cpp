/****************************************************************************
**
**
****************************************************************************/

#include "mysortfilterproxymodel.h"

#include "treemodel.h"

//! [0]
MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent, bool excludeDates)
    : QSortFilterProxyModel(parent),
	  _recurrenceTokens("(\\d+)([msj])"),
      _excludeDates(excludeDates)
{
}
//! [0]

//! [1]
bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
	QModelIndex index0 = sourceModel()->index(sourceRow, 2, sourceParent);
	TreeTask * item = static_cast<TreeModel *>(sourceModel())->getItem(index0);
	const bool hasDate = _excludeDates ^ item->date().isValid();
    TreeTask * lastDoneItem = static_cast<TreeModel *>(sourceModel())->getLastDoneItem(item->nom());
    if (!lastDoneItem)
        return hasDate;
    QRegularExpressionMatch match = _recurrenceTokens.match(item->recurrence());
    QHash<QString, int> recurrence;
	while (match.hasMatch())
	{
        recurrence[match.captured(2)] = match.captured(1).toInt();
		qDebug() << match.captured();
        match = _recurrenceTokens.match(item->recurrence(), match.capturedEnd()-1);
	}
    QDateTime nextRecurrence = lastDoneItem->date();
    for (QHash<QString, int>::iterator i = recurrence.begin(); i != recurrence.end(); ++i)
    {
        if (i.key() == "m")
        {
            nextRecurrence = nextRecurrence.addMonths(i.value());
            continue;
        }
        if (i.key() == "s")
        {
            nextRecurrence = nextRecurrence.addDays(i.value() * 7);
            continue;
        }
        if (i.key() == "j")
        {
            nextRecurrence = nextRecurrence.addDays(i.value());
            continue;
        }
    }
    if (QDateTime::currentDateTime() < nextRecurrence)
    {
        return false;
    }
    return hasDate;
}
//! [1]

//! [2]
bool MySortFilterProxyModel::excludeDates() const
{
    return _excludeDates;
}

void MySortFilterProxyModel::setExcludeDates(bool newExcludeDates)
{
    _excludeDates = newExcludeDates;
    invalidateFilter();
}
//! [2]
