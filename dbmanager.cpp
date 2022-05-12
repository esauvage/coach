#include "dbmanager.h"

#include <QSqlQuery>
#include <QDebug>

/*CREATE TABLE "PERSONNES" (
    "ID"	INTEGER NOT NULL,
    "NOM"	TEXT NOT NULL,
    "PERE_BIO"	INTEGER,
    "MERE_BIO"	INTEGER,
    "DATE_NAISSANCE"	REAL,
    "DATE_DECES"	REAL,
    PRIMARY KEY("ID" AUTOINCREMENT)
);*/
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
    QSqlQuery query("SELECT NOM FROM PERSONNES");
    while (query.next()) {
        Personne p;
        p.setNom(query.value(0).toString());
        r << p;
    }
    return r;
}

void DbManager::addPersonne(const Personne &v) const
{
    QSqlQuery insert;
    insert.prepare("INSERT INTO PERSONNES (NOM) VALUES (:nom)");
    insert.bindValue(":nom", v.nom());
    insert.exec();
}
