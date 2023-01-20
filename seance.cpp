#include "seance.h"

Seance::Seance()
    :_activiteId(-1)
{
}

QDate Seance::date() const
{
    return _date;
}

void Seance::setDate(const QDate &date)
{
    _date = date;
}

QTime Seance::debut() const
{
    return _debut;
}

void Seance::setDebut(const QTime &debut)
{
    _debut = debut;
}

QTime Seance::fin() const
{
    return _fin;
}

void Seance::setFin(const QTime &fin)
{
    _fin = fin;
}

int Seance::id() const
{
    return _id;
}

void Seance::setId(int id)
{
    _id = id;
}

int Seance::personneId() const
{
    return _personneId;
}

void Seance::setPersonneId(int personneId)
{
    _personneId = personneId;
}

int Seance::activiteId() const
{
    return _activiteId;
}

void Seance::setActiviteId(int newActiviteId)
{
    _activiteId = newActiviteId;
}
