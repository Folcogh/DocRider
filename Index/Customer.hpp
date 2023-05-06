#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "Line.hpp"
#include <QList>
#include <QObject>
#include <QString>

class Country; // Forward declaration

class Customer: public QObject
{
    Q_OBJECT

  public:
    Customer(Country* country, QString name);

    QString  name() const { return Name; }                // Return the name of the customer
    Country* country() const { return ParentCountry; }    // Return the parent country
    bool     hasLine() const { return !Lines.isEmpty(); } // Return true if the customer has at least one line

  private:
    Country*     ParentCountry;
    QString      Name;
    QList<Line*> Lines;
};

Q_DECLARE_METATYPE(Customer*)

#endif // CUSTOMER_HPP
