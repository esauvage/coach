#include "dbmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/*CREATE TABLE PERSONNES (
	"ID"	INTEGER NOT NULL,
	"NOM"	TEXT NOT NULL,
	"PERE_BIO"	 INTEGER,
	"MERE_BIO"	 INTEGER,
	"DATE_NAISSANCE" DATETIME,
	"DATE_DECES" DATETIME,
	PRIMARY KEY ("ID" AUTOINCREMENT)
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
    qDebug() << update.executedQuery();
    qDebug() << update.lastError();
}

void DbManager::changePassword(int personneId, const QString& nPasswd) const
{
	QSqlQuery update;
	update.prepare("UPDATE PERSONNES SET PASSWORD = :passwd WHERE ID = :id");
	update.bindValue(":passwd", nPasswd);
	update.bindValue(":id", personneId);
	qDebug() << update.lastQuery();
	update.exec();
	qDebug() << update.executedQuery();
	qDebug() << update.lastError();
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
