#include "dbmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/*
CREATE TABLE PERSONNES (
	ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, NOM TEXT NOT NULL, PERE_BIO INTEGER, MERE_BIO INTEGER, DATE_NAISSANCE DATETIME, DATE_DECES DATETIME, PASSWORD TEXT);
;
CREATE TABLE SEANCES (
	"ID"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	"DATE"	DATE NOT NULL,
	"DEBUT"	 TIME NOT NULL,
	"FIN"	 TIME NOT NULL,
	"PERSONNE_ID" INTEGER NOT NULL,
	FOREIGN KEY ("PERSONNE_ID") REFERENCES "PERSONNES"("ID")
);
*/
DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database failed";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

QList<QPair <QString, int> > DbManager::getNomPersonnes() const
{
	QList<QPair <QString, int> > r;
	QSqlQuery query("SELECT ID, NOM FROM PERSONNES");
    while (query.next()) {
		QPair<QString, int> p;
		p.second = query.value(0).toInt();
		p.first = query.value(1).toString();
        r << p;
    }
    return r;
}

void DbManager::addPersonne(const Personne &v) const
{
    QSqlQuery insert;
    insert.prepare("INSERT INTO PERSONNES (NOM, DATE_NAISSANCE, DATE_DECES) VALUES (:nom, :naissance, :deces)");
    insert.bindValue(":nom", v.nom());
    insert.bindValue(":naissance", v.dateNaissance());
    insert.bindValue(":deces", v.dateDeces());
    qDebug() << insert.lastQuery();
    insert.exec();
    qDebug() << insert.executedQuery();
    qDebug() << insert.lastError();
}

void DbManager::modifPersonne(const Personne &v) const
{
    QSqlQuery update;
    update.prepare("UPDATE PERSONNES SET NOM = :nom, DATE_NAISSANCE = :naissance, DATE_DECES = :deces WHERE ID = :id");
    update.bindValue(":nom", v.nom());
    update.bindValue(":naissance", v.dateNaissance());
    update.bindValue(":deces", v.dateDeces());
    update.bindValue(":id", v.id());
    qDebug() << update.lastQuery();
    update.exec();
	if (update.lastError().type() != QSqlError::NoError)
	{
		qDebug() << update.executedQuery();
		qDebug() << update.lastError();
	}
}

void DbManager::changePassword(int personneId, const QString& nPasswd) const
{
	QSqlQuery update;
	update.prepare("UPDATE PERSONNES SET PASSWORD = :passwd WHERE ID = :id");
	update.bindValue(":passwd", nPasswd);
	update.bindValue(":id", personneId);
	qDebug() << update.lastQuery();
	update.exec();
	if (update.lastError().type() != QSqlError::NoError)
	{
		qDebug() << update.executedQuery();
		qDebug() << update.lastError();
	}
}

Personne DbManager::getPersonne(const int id, const QString &password) const
{
    Personne r;
    QSqlQuery query;
	query.prepare("SELECT PASSWORD FROM PERSONNES WHERE ID = :id");
	query.bindValue(":id", id);
	query.exec();
	if (!query.next()) return r;
	const QString refPass = query.value(0).toString();
	if (refPass != password)
		return r;
	query.prepare("SELECT ID, NOM, DATE_NAISSANCE, DATE_DECES FROM PERSONNES WHERE ID = :id");
    query.bindValue(":id", id);
    query.exec();
    if (query.next()) {
        r.setId(query.value(0).toInt());
        r.setNom(query.value(1).toString());
        r.setDateNaissance(query.value(2).toDateTime());
        r.setDateDeces(query.value(3).toDateTime());
    }
    return r;
}

void DbManager::supprimePersonne(int id) const
{
	QSqlQuery suppr;
	suppr.prepare("DELETE FROM PERSONNES WHERE ID = :id");
	suppr.bindValue(":id", id);
	suppr.exec();
	if (suppr.lastError().type() != QSqlError::NoError)
	{
		qDebug() << suppr.lastQuery();
		qDebug() << suppr.lastError();
	}
}

QList<Seance> DbManager::getSeances(int personneId) const
{
	QList <Seance> r;
    QSqlQuery query;
	query.prepare("SELECT ID, DATE, DEBUT, FIN, ACTIVITE_ID FROM SEANCES WHERE PERSONNE_ID = :personneId ORDER BY DATE, DEBUT DESC");
    query.bindValue(":personneId", personneId);
    query.exec();
    while (query.next()) {
		Seance p;
		p.setId(query.value(0).toInt());
		p.setDate(query.value(1).toDate());
		p.setDebut(query.value(2).toTime());
		p.setFin(query.value(3).toTime());
        p.setActiviteId(query.value(4).toInt());
		r << p;
	}
	return r;
}

void DbManager::addSeance(const Seance &v) const
{
	QSqlQuery insert;
    insert.prepare("INSERT INTO SEANCES (DATE, DEBUT, FIN, ACTIVITE_ID, PERSONNE_ID) VALUES (:date, :debut, :fin, :activite, :personneId)");
	insert.bindValue(":date", v.date());
	insert.bindValue(":debut", v.debut());
	insert.bindValue(":fin", v.fin());
    insert.bindValue(":activite", v.activiteId());
    insert.bindValue(":personneId", v.personneId());
    qDebug() << insert.lastQuery();
	insert.exec();
	qDebug() << insert.executedQuery();
	qDebug() << insert.lastError();
}

void DbManager::modifSeance(const Seance &v) const
{
	QSqlQuery update;
    update.prepare("UPDATE SEANCES SET DATE = :date, DEBUT = :debut, FIN = :fin, ACTIVITE_ID = :activite WHERE ID = :id");
	update.bindValue(":date", v.date());
	update.bindValue(":debut", v.debut());
    update.bindValue(":fin", v.fin());
    update.bindValue(":activite", v.activiteId());
    update.bindValue(":id", v.id());
	qDebug() << update.lastQuery();
	update.exec();
	qDebug() << update.executedQuery();
	qDebug() << update.lastError();
}

void DbManager::supprimeSeance(const Seance &v) const
{
	QSqlQuery update;
	update.prepare("DELETE FROM SEANCES WHERE DATE = :date AND DEBUT = :debut AND FIN = :fin AND ID = :id");
	update.bindValue(":date", v.date());
	update.bindValue(":debut", v.debut());
	update.bindValue(":fin", v.fin());
	update.bindValue(":id", v.id());
	qDebug() << update.lastQuery();
	update.exec();
	qDebug() << update.executedQuery();
	qDebug() << update.lastError();
}

Seance DbManager::getSeance(const int id) const
{
	Seance r;
	QSqlQuery query;
    query.prepare("SELECT ID, DATE, DEBUT, FIN, PERSONNE_ID, ACTIVITE_ID FROM SEANCES WHERE ID = :id");
	query.bindValue(":id", id);
	query.exec();
	if (query.next()) {
		r.setId(query.value(0).toInt());
		r.setDate(query.value(1).toDate());
		r.setDebut(query.value(2).toTime());
        r.setFin(query.value(3).toTime());
        r.setPersonneId(query.value(4).toInt());
        r.setActiviteId(query.value(5).toInt());
    }
	return r;
}

QList<TreeTask> DbManager::getTodos(int personneId) const
{
	QList<TreeTask> r;
	QSqlQuery query;
	query.prepare("SELECT ID, NOM, RECURRENCE FROM TODO WHERE PERSONNE_ID = :id");
	query.bindValue(":id", personneId);
	query.exec();
	while (query.next()) {
		TreeTask v;
		v.setId(query.value(0).toInt());
		v.setNom(query.value(1).toString());
		v.setRecurrence(query.value(2).toString());
		r << v;
	}
	return r;
}

void DbManager::modifTodo(const TreeTask &v) const
{
	QSqlQuery update;
	update.prepare("UPDATE TODO SET NOM = :nom, RECURRENCE = :recurrence WHERE ID = :id");
	update.bindValue(":nom", v.nom());
	update.bindValue(":recurrence", v.recurrence());
	update.bindValue(":id", v.id());
	qDebug() << update.lastQuery();
	update.exec();
	qDebug() << update.executedQuery();
	qDebug() << update.lastError();
}

int DbManager::addTodo(const QString &nom, int personneId) const
{
	QSqlQuery insert;
	insert.prepare("INSERT INTO TODO (PERSONNE_ID, NOM) VALUES (:personneId, :nom)");
	insert.bindValue(":nom", nom);
	insert.bindValue(":personneId", personneId);
	qDebug() << insert.lastQuery();
	insert.exec();
	if (insert.lastError().type() != QSqlError::NoError)
	{
		qDebug() << insert.executedQuery();
		qDebug() << insert.lastError();
	}
	insert.prepare("SELECT LAST_INSERT_ROWID();");
	insert.exec();
	if (insert.next()) {
		return insert.value(0).toInt();
	}
	return -1;
}

void DbManager::supprimeTodo(int id) const
{
	QSqlQuery suppr;
	suppr.prepare("DELETE FROM TODO WHERE ID = :id");
	suppr.bindValue(":id", id);
	suppr.exec();
	if (suppr.lastError().type() != QSqlError::NoError)
	{
		qDebug() << suppr.lastError();
    }
}

void DbManager::modifDone(const TreeTask &v) const
{
    QSqlQuery update;
    update.prepare("UPDATE DONE SET NOM = :nom, DATE = :date WHERE ID = :id");
    update.bindValue(":nom", v.nom());
    update.bindValue(":date", v.date());
    update.bindValue(":id", v.id());
    qDebug() << update.lastQuery();
    update.exec();
    qDebug() << update.executedQuery();
    qDebug() << update.lastError();
}

int DbManager::addDone(const QString &nom, const QDateTime &date, int personneId) const
{
	QSqlQuery insert;
	insert.prepare("INSERT INTO DONE (PERSONNE_ID, NOM, DATE) VALUES (:personneId, :nom, :date)");
	insert.bindValue(":nom", nom);
	insert.bindValue(":date", date);
	insert.bindValue(":personneId", personneId);
	qDebug() << insert.lastQuery();
	insert.exec();
	if (insert.lastError().type() != QSqlError::NoError)
	{
		qDebug() << insert.executedQuery();
		qDebug() << insert.lastError();
	}
	insert.prepare("SELECT LAST_INSERT_ROWID();");
	insert.exec();
	if (insert.next()) {
		return insert.value(0).toInt();
	}
	return -1;
}

void DbManager::supprimeDone(int id) const
{
	QSqlQuery suppr;
	suppr.prepare("DELETE FROM DONE WHERE ID = :id");
	suppr.bindValue(":id", id);
	suppr.exec();
	if (suppr.lastError().type() != QSqlError::NoError)
	{
		qDebug() << suppr.lastError();
	}
}

QList<TreeTask> DbManager::getDones(int personneId) const
{
	QList<TreeTask> r;
	QSqlQuery query;
	query.prepare("SELECT ID, NOM, DATE FROM DONE WHERE PERSONNE_ID = :id ORDER BY DATE DESC");
	query.bindValue(":id", personneId);
	query.exec();
	while (query.next()) {
		TreeTask v;
		v.setId(query.value(0).toInt());
		v.setNom(query.value(1).toString());
		v.setDate(query.value(2).toDateTime());
		r << v;
	}
    return r;
}

QList<QPair<QString, int> > DbManager::getActivites() const
{
    QList<QPair<QString, int> > r;
    QSqlQuery query;
    query.prepare("SELECT ID, NOM FROM ACTIVITES");
    query.exec();
    while (query.next()) {
        QPair<QString, int> v;
        v.first = query.value(1).toString();
        v.second = query.value(0).toInt();
        r << v;
    }
    return r;
}

int DbManager::addActivite(const QString &nom) const
{
    QSqlQuery insert;
    insert.prepare("INSERT INTO ACTIVITES (NOM) VALUES (:nom)");
    insert.bindValue(":nom", nom);
    qDebug() << insert.lastQuery();
    insert.exec();
    if (insert.lastError().type() != QSqlError::NoError)
    {
        qDebug() << insert.executedQuery();
        qDebug() << insert.lastError();
    }
    insert.prepare("SELECT LAST_INSERT_ROWID();");
    insert.exec();
    if (insert.next()) {
        return insert.value(0).toInt();
    }
    return -1;
}
