#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

#include "personne.h"
#include "seance.h"
#include "treetask.h"

class DbManager
{
public:
    DbManager(const QString& path);
	QList<QPair <QString, int> > getNomPersonnes() const;
    void addPersonne(const Personne & v) const;
    void modifPersonne(const Personne & v) const;
	void changePassword(int personneId, const QString& nPasswd) const;
	Personne getPersonne(const int id, const QString &password) const;
	void supprimePersonne(int id) const;
	QList<Seance> getSeances() const;
	void addSeance(const Seance &v) const;
	void modifSeance(const Seance &v) const;
	void supprimeSeance(const Seance &v) const;
	Seance getSeance(const int id) const;
	QList<TreeTask> getTodos(int personneId) const;
	void modifTodo(int id, const QString &nom) const;
	int addTodo(const QString &nom, int personneId) const;
	void supprimeTodo(int id) const;
	int addDone(const QString &nom, const QDateTime &date, int personneId) const;
	void supprimeDone(int id) const;
	QList<TreeTask> getDones(int personneId) const;
private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
