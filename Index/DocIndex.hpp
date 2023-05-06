#ifndef DOCINDEX_HPP
#define DOCINDEX_HPP

#include "Country.hpp"
#include <QList>
#include <QString>

class DocIndex
{
  public:
    static DocIndex* instance();
    static void release();

    void newCountry(Country* country) { Countries.append(country); }

    // Validators
    bool validateNewCountryName(QString name) const;
    bool validateExistingCountryName(Country* country, QString name) const;

    // Predicates
    bool hasCountry() const { return !Countries.isEmpty(); }
    bool hasCustomer() const;
    bool hasLine() const;

    // Accessors
    QList<Country*> countryList() const { return Countries; }

  private:
    DocIndex();
    ~DocIndex();

    static DocIndex* docindex;
    QList<Country*> Countries;
};

#endif // DOCINDEX_HPP
