#ifndef PERSONNE_H
#define PERSONNE_H

#include <QString>
#include <QDateTime>

class Personne
{
public:
    Personne();
    QString nom() const;
    void setNom(const QString &nom);

    QString prenom() const;
    void setPrenom(const QString &prenom);

    QDateTime dateNaissance() const;
    void setDateNaissance(const QDateTime &dateNaissance);

    QDateTime dateDeces() const;
    void setDateDeces(const QDateTime &dateDeces);

    Personne *pereBiologique() const;
    void setPereBiologique(Personne *pereBiologique);

    Personne *mereBiologique() const;
    void setMereBiologique(Personne *mereBiologique);

private:
    QString _nom;
    QString _prenom;
    QDateTime _dateNaissance;
    QDateTime _dateDeces;
    Personne * _pereBiologique = nullptr;
    Personne * _mereBiologique = nullptr;
};

#endif // PERSONNE_H
