#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

#include "personne.h"
#include "seance.h"

class DbManager
{
public:
    DbManager(const QString& path);
    QList<Personne> getPersonnes() const;
    void addPersonne(const Personne & v) const;
    void modifPersonne(const Personne & v) const;
    void supprimePersonne(const Personne & v) const;
    Personne getPersonne(const int id) const;
    QList<Seance> getSeances() const;
    void addSeance(const Seance & v) const;
    void modifSeance(const Seance & v) const;
    void supprimeSeance(const Seance & v) const;
    Seance getSeance(const int id) const;
private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
