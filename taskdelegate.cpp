#include "taskdelegate.h"

#include <QApplication>

TaskDelegate::TaskDelegate(QObject *parent)
	: QStyledItemDelegate{parent}
{

}

void TaskDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//	QStyleOptionButton cbOpt;
//	cbOpt.rect = option.rect;
//	bool isChecked = index.data(Qt::CheckStateRole).toBool();
//	if (isChecked)
//	{
//		cbOpt.state |= QStyle::State_On;
//	}
//	else
//	{
//		cbOpt.state |= QStyle::State_Off;
//	}

//	QApplication::style()->drawControl(QStyle::CE_CheckBox, &cbOpt, painter);
	QStyledItemDelegate::paint(painter, option, index);
}

bool TaskDelegate::editorEvent(QEvent *event,
							QAbstractItemModel *model,
							const QStyleOptionViewItem &option,
							const QModelIndex &index)
{
	if (event->type() == QEvent::MouseButtonRelease)
	{
		bool value = index.data(Qt::CheckStateRole).toBool();

		// invert checkbox state
		model->setData(index, !value, Qt::CheckStateRole);

		return true;
	}

	return QStyledItemDelegate::editorEvent(event, model, option, index);
}
