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
CREATE TABLE SEANCES (
    "ID"	INTEGER NOT NULL,
    "DATE"	DATE NOT NULL,
    "DEBUT"	 TIME NOT NULL,
    "FIN"	 TIME NOT NULL,
    "PERSONNE_ID" INTEGER NOT NULL,
    PRIMARY KEY ("ID" AUTOINCREMENT),
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

QList<Personne> DbManager::getPersonnes() const
{
    QList <Personne> r;
    QSqlQuery query("SELECT ID, NOM, DATE_NAISSANCE, DATE_DECES FROM PERSONNES");
    while (query.next()) {
        Personne p;
        p.setId(query.value(0).toInt());
        p.setNom(query.value(1).toString());
        p.setDateNaissance(query.value(2).toDateTime());
        p.setDateDeces(query.value(3).toDateTime());
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

void DbManager::supprimePersonne(const Personne &v) const
{
    QSqlQuery update;
    update.prepare("DELETE FROM PERSONNES WHERE NOM = :nom AND DATE_NAISSANCE = :naissance AND DATE_DECES = :deces AND ID = :id");
    update.bindValue(":nom", v.nom());
    update.bindValue(":naissance", v.dateNaissance());
    update.bindValue(":deces", v.dateDeces());
    update.bindValue(":id", v.id());
    qDebug() << update.lastQuery();
    update.exec();
    qDebug() << update.executedQuery();
    qDebug() << update.lastError();
}

Personne DbManager::getPersonne(const int id) const
{
    Personne r;
    QSqlQuery query;
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

QList<Seance> DbManager::getSeances() const
{
    QList <Seance> r;
    QSqlQuery query("SELECT ID, DATE, DEBUT, FIN, PERSONNE_ID FROM PERSONNES");
    while (query.next()) {
        Seance p;
        p.setId(query.value(0).toInt());
        p.setDate(query.value(1).toDate());
        p.setDebut(query.value(2).toTime());
        p.setFin(query.value(3).toTime());
        r << p;
    }
    return r;
}

void DbManager::addSeance(const Seance &v) const
{
    QSqlQuery insert;
    insert.prepare("INSERT INTO SEANCES (DATE, DEBUT, FIN, PERSONNE_ID) VALUES (:date, :debut, :fin, :personneId)");
    insert.bindValue(":date", v.date());
    insert.bindValue(":debut", v.debut());
    insert.bindValue(":fin", v.fin());
    insert.bindValue(":personneId", v.personne()->id());
    qDebug() << insert.lastQuery();
    insert.exec();
    qDebug() << insert.executedQuery();
    qDebug() << insert.lastError();
}

void DbManager::modifSeance(const Seance &v) const
{
    QSqlQuery update;
    update.prepare("UPDATE SEANCES SET DATE = :date, DEBUT = :debut, FIN = :deces WHERE ID = :id");
    update.bindValue(":date", v.date());
    update.bindValue(":debut", v.debut());
    update.bindValue(":fin", v.fin());
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
    query.prepare("SELECT ID, DATE, DEBUT, FIN FROM SEANCES WHERE ID = :id");
    query.bindValue(":id", id);
    query.exec();
    if (query.next()) {
        r.setId(query.value(0).toInt());
        r.setDate(query.value(1).toDate());
        r.setDebut(query.value(2).toTime());
        r.setFin(query.value(3).toTime());
    }
    return r;
}
