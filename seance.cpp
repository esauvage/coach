#include "seance.h"

#include "personne.h"

Seance::Seance()
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

Personne *Seance::personne() const
{
    return _personne;
}

void Seance::setPersonne(Personne *personne)
{
    _personne = personne;
}
