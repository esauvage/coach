#ifndef TASKDONEDELEGATE_H
#define TASKDONEDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class TaskDoneDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
    explicit TaskDoneDelegate(QObject *parent = nullptr);
    // painting
    virtual void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const override;
protected:
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};
#endif // TASKDELEGATE_H
