#include "personne.h"

Personne::Personne()
	:_id(-1)
{

}

bool Personne::isValid()
{
	return _id > 0;
}

QString Personne::nom() const
{
    return _nom;
}

void Personne::setNom(const QString &nom)
{
    _nom = nom;
}

QString Personne::prenom() const
{
    return _prenom;
}

void Personne::setPrenom(const QString &prenom)
{
    _prenom = prenom;
}

QDateTime Personne::dateNaissance() const
{
    return _dateNaissance;
}

void Personne::setDateNaissance(const QDateTime &dateNaissance)
{
    _dateNaissance = dateNaissance;
}

QDateTime Personne::dateDeces() const
{
    return _dateDeces;
}

void Personne::setDateDeces(const QDateTime &dateDeces)
{
    _dateDeces = dateDeces;
}

Personne *Personne::pereBiologique() const
{
    return _pereBiologique;
}

void Personne::setPereBiologique(Personne *pereBiologique)
{
    _pereBiologique = pereBiologique;
}

Personne *Personne::mereBiologique() const
{
    return _mereBiologique;
}

void Personne::setMereBiologique(Personne *mereBiologique)
{
    _mereBiologique = mereBiologique;
}

int Personne::id() const
{
    return _id;
}

void Personne::setId(int id)
{
    _id = id;
}
