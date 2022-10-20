#ifndef TASKDELEGATE_H
#define TASKDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class TaskDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit TaskDelegate(QObject *parent = nullptr);
protected:
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};
#endif // TASKDELEGATE_H
