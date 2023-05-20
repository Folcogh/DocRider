#include "Database.hpp"

//
//  Singleton stuff
//

Database* Database::database = nullptr;

Database::Database()
{
    // Open the db file, populate the list of machines etc...
}

Database::~Database()
{
    while (!this->MachineList.isEmpty()) {
        delete this->MachineList.takeLast();
    }
}

Database* Database::instance()
{
    if (database == nullptr) {
        database = new Database;
    }
    return database;
}

void Database::release()
{
    if (database != nullptr) {
        delete database;
    }
    database = nullptr;
}

Machine* Database::nextMachine()
{
    return this->MachineIterator == this->MachineList.size()
               ? nullptr
               : this->MachineList.at(this->MachineIterator++);
}

bool Database::requestNewMachine(QString type,
                                 int serial1,
                                 int serial2,
                                 int devstep,
                                 QString country,
                                 QString customer,
                                 QString line)
{
    // Check if the machine already exists
    for (int i = 0; i < this->MachineList.size(); i++) {
        if ((this->MachineList.at(i)->serialNumber1() == serial1)
            && (this->MachineList.at(i)->serialNumber2() == serial2)) {
            return false;
        }
    }
    return true;
}

QList<QString> Database::countryList() const
{
    QList<QString> Countries;
    for (int i = 0; i < this->MachineList.size(); i++) {
        Countries << this->MachineList.at(i)->country();
    }
    Countries.removeDuplicates();
    Countries.sort();
    return Countries;
}

QList<QString> Database::typeList() const
{
    QList<QString> Types;
    for (int i = 0; i < this->MachineList.size(); i++) {
        Types << this->MachineList.at(i)->type();
    }
    Types.removeDuplicates();
    Types.sort();
    return Types;
}
