#include "taskdelegate.h"

#include <QApplication>

TaskDelegate::TaskDelegate(QObject *parent)
	: QStyledItemDelegate{parent}
{

}

bool TaskDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
