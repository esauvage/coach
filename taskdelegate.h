#ifndef TASKDELEGATE_H
#define TASKDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class TaskDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit TaskDelegate(QObject *parent = nullptr);
};
#endif // TASKDELEGATE_H
