/****************************************************************************
**
**
****************************************************************************/

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "dbmanager.h"

class TreeTask;

//! [0]
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
	TreeModel(const QStringList &headers,
              QObject *parent = nullptr);
    ~TreeModel();
//! [0] //! [1]

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
//! [1]

//! [2]
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
	void populate(int personneId);

private slots:
	void onTimeout();

private:
	void setupModelData(const QStringList &lines, TreeTask *parent);
	TreeTask *getItem(const QModelIndex &index) const;
	void setDones(const QList<TreeTask> &dones);

	TreeTask *rootItem;
	DbManager * _dbManager = nullptr;
    int _personneId = -1;
};
//! [2]

#endif // TREEMODEL_H
