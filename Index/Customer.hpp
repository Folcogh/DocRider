#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "Line.hpp"
#include <QList>
#include <QString>

class Customer
{
  public:
    Customer();

  private:
    QString Name;
    QList<Line*> Lines;
};

#endif // CUSTOMER_HPP
