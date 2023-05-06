#include "Country.hpp"
#include <QMessageBox>

Country::Country(QString name)
    : Name(name)
{
}

bool Country::hasLine() const
{
    for (int i = 0; i < this->Customers.size(); i++) {
        if (this->Customers.at(i)->hasLine()) {
            return true;
        }
    }
    return false;
}

bool Country::validateNewCustomerName(QString customer)
{
    for (int i = 0; i < this->Customers.size(); i++) {
        if (this->Customers.at(i)->name() == customer) {
            return false;
        }
    }
    return true;
}

bool Country::validateEditedCustomerName(Customer* customer, QString CustomerName)
{
    for (int i = 0; i < this->Customers.size(); i++) {
        if (this->Customers.at(i) == customer) {
            continue;
        }
        if (this->Customers.at(i)->name() == CustomerName) {
            return false;
        }
    }
    return true;
}
