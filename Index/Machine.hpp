#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "Document.hpp"
#include <QList>
#include <QString>

class Machine
{
  public:
    Machine();

  private:
    QString name;
    QList<Document*> Documents;
    // Machine description: DevStep, S/N, etc...
};

#endif // MACHINE_HPP
