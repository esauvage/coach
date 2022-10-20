#include "taskdonedelegate.h"

#include <QApplication>

TaskDoneDelegate::TaskDoneDelegate(QObject *parent)
	: QStyledItemDelegate{parent}
{

}

void TaskDoneDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 1) return;
    QStyleOptionViewItem newOption = option;
    newOption.checkState = newOption.checkState== Qt::Checked ? Qt::Unchecked : Qt::Checked;
    QStyledItemDelegate::paint(painter, newOption, index);
}

bool TaskDoneDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
