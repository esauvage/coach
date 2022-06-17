#ifndef SEANCE_H
#define SEANCE_H

#include <QDateTime>

class Personne;

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

    Personne *personne() const;
    void setPersonne(Personne *personne);

private:
    QDate _date;
    QTime _debut;
    QTime _fin;
    int _id;//On a besoin d'un identifiant
    Personne * _personne = nullptr;
};

#endif // SEANCE_H
