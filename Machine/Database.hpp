#ifndef DATABASE_HPP
  #define DATABASE_HPP

#include "Machine.hpp"
#include <QList>
#include <QString>

class Database
{
  public:
    static Database* instance(); // singleton
    static void      release();  // singleton
    bool requestNewMachine(QString type,
                           int serial1,
                           int serial2,
                           int devstep,
                           QString country,
                           QString customer,
                           QString line);

    // Accessors
    QList<QString> countryList() const;
    QList<QString> typeList() const;

    // Machine list iteration
    void startMachineIteration() { MachineIterator = 0; }
    Machine* nextMachine();

private:
    // Singleton stuff
    Database();
    ~Database();
    static Database* database;

    QList<Machine*> MachineList;
    int             MachineIterator;
};

#endif // DATABASE_HPP
