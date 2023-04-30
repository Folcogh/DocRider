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

  public:
    DocIndex();
    ~DocIndex();
    bool validateNewCountryName(QString name) const;
    void newCountry(Country* country);

    static DocIndex* docindex;
    QList<Country*> Countries;
};

#endif // DOCINDEX_HPP
