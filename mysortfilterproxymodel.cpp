/****************************************************************************
**
**
****************************************************************************/

#include "mysortfilterproxymodel.h"

#include "treemodel.h"

//#include <QtWidgets>

//! [0]
MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent, bool excludeDates)
    : QSortFilterProxyModel(parent),
	  _recurrenceTokens("(\\d+)([msj])"),
      _excludeDates(excludeDates)
{
}
//! [0]

//! [3]
bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
	QModelIndex index0 = sourceModel()->index(sourceRow, 2, sourceParent);
	TreeTask * item = static_cast<TreeModel *>(sourceModel())->getItem(index0);
	const bool hasDate = _excludeDates ^ item->date().isValid();
	QRegularExpression recurrenceTokens ("(\\d+)([msj])");
	QRegularExpressionMatch match = recurrenceTokens.match(item->recurrence());
	while (match.hasMatch())
	{
		TreeTask * lastDoneItem = static_cast<TreeModel *>(sourceModel())->getLastDoneItem(item->nom());
		if (!lastDoneItem)
			break;
		qDebug() << match.captured();
		if (QDateTime::currentDateTime().addMonths(match.captured(1).toInt())>lastDoneItem->date())
			return false;
		match = recurrenceTokens.match(item->recurrence(), match.capturedEnd()-1);
	}
	return hasDate;
}
//! [3]

bool MySortFilterProxyModel::excludeDates() const
{
    return _excludeDates;
}

void MySortFilterProxyModel::setExcludeDates(bool newExcludeDates)
{
    _excludeDates = newExcludeDates;
    invalidateFilter();
}
//! [7]
