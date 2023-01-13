/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TreeTask_H
#define TreeTask_H

#include <QVariant>
#include <QVector>
#include <QDateTime>

//! [0]
class TreeTask
{
public:
	explicit TreeTask(TreeTask *parent = nullptr);
    TreeTask(const TreeTask &ref);
	~TreeTask();

	TreeTask *child(int number);
    QVector<TreeTask*> childItems() const;
    int childCount() const;
    int columnCount() const;
	QVariant data(int column, int role = Qt::DiffuseDither) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
	TreeTask *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
	bool setData(int column, const QVariant &value, int role = Qt::EditRole);
	bool setId(int v);
	int id() const;
	bool setNom(const QString &v);
	QString nom() const;
	bool setDate(const QDateTime &d);
	QDateTime date() const;
	const QString &recurrence() const;
	void setRecurrence(const QString &newRecurrence);
    void insertChild(const TreeTask &child);
	void setElapsedTime(const qint64 v);
    qint64 elapsed() const;

private:
    QVector<TreeTask*> _childItems;
	TreeTask *parentItem;
	QString _nom;
	QString _recurrence;
	QDateTime _date;
	qint64 _elapsed;
	int _id;
};
//! [0]

#endif // TreeTask_H
