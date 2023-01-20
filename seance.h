#ifndef SEANCE_H
#define SEANCE_H

#include <QDateTime>

class Seance
{
public:
    Seance();
    QDate date() const;
    void setDate(const QDate &date);

    QTime debut() const;
    void setDebut(const QTime &debut);

    QTime fin() const;
    void setFin(const QTime &fin);

    int id() const;
    void setId(int id);

    int personneId() const;
    void setPersonneId(int personneId);
    int activiteId() const;
    void setActiviteId(int newActiviteId);

private:
    QDate _date;
    QTime _debut;
    QTime _fin;
    int _id;//On a besoin d'un identifiant
    int _personneId;
    int _activiteId;
};

#endif // SEANCE_H
