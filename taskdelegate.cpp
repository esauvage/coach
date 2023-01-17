#include "taskdelegate.h"

#include <QKeyEvent>

TaskDelegate::TaskDelegate(QObject *parent)
	: QStyledItemDelegate{parent}
{

}

bool TaskDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::KeyRelease)
    {
        emit keyReleased(static_cast<QKeyEvent *>(event));
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
