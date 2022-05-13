#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

#include "personne.h"

class DbManager
{
public:
    DbManager(const QString& path);
    QList<Personne> getPersonnes() const;
    void addPersonne(const Personne & v) const;
    void modifPersonne(const Personne & v) const;
    Personne getPersonne(const int id) const;
private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
