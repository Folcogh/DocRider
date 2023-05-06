#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include "Customer.hpp"
#include <QList>
#include <QObject>
#include <QString>

class Country: public QObject
{
    Q_OBJECT

  public:
    Country(QString name);
    QString name() const { return Name; }                        // Return the name of the country
    bool    hasCustomer() const { return !Customers.isEmpty(); } // Return true if the country has at least one customer
    bool    hasLine() const;                                     // Return true if at least one customer has at least one line
    bool    validateNewCustomerName(QString customer);
    bool    validateEditedCustomerName(Customer* customer, QString CustomerName);
    void    addCustomer(Customer* customer) { Customers.append(customer); }

  private:
    QString          Name;
    QList<Customer*> Customers;
};

Q_DECLARE_METATYPE(Country*)

#endif // COUNTRY_HPP
