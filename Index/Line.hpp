#ifndef LINE_HPP
#define LINE_HPP

#include "Machine.hpp"
#include <QList>
#include <QString>

class Customer;

class Line
{
  public:
    Line(QString name);
    Customer* customer() const { return ParentCustomer; }
    QString   name() const { return Name; }

  private:
    Customer*       ParentCustomer;
    QString         Name;
    QList<Machine*> Machines;
};

#endif // LINE_HPP
