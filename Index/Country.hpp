#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include "Customer.hpp"
#include <QList>
#include <QString>

class Country
{
  public:
    Country(QString name);
    QString name() const;

  private:
    QString Name;
    QList<Customer*> Customers;
};

#endif // COUNTRY_HPP
