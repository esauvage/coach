#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

#include "personne.h"

class DbManager
{
public:
    DbManager(const QString& path);
	QList<QPair <QString, int> > getNomPersonnes() const;
    void addPersonne(const Personne & v) const;
    void modifPersonne(const Personne & v) const;
	void changePassword(int personneId, const QString& nPasswd) const;
	Personne getPersonne(const int id, const QString &password) const;
private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
