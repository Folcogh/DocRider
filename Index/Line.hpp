#ifndef LINE_HPP
#define LINE_HPP

#include "Machine.hpp"
#include <QList>
#include <QString>

class Line
{
  public:
    Line(QString name);

  private:
    QString Name;
    QList<Machine*> Machines;
};

#endif // LINE_HPP
