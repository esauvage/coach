#ifndef TASKDELEGATE_H
#define TASKDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class TaskDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit TaskDelegate(QObject *parent = nullptr);
	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const override;

//	QSize sizeHint(const QStyleOptionViewItem &option,
	//				   const QModelIndex &index) const override;
protected:
	virtual bool editorEvent(QEvent *event, QAbstractItemModel *model,
							 const QStyleOptionViewItem &option,
							 const QModelIndex &index) override;
};
#endif // TASKDELEGATE_H
