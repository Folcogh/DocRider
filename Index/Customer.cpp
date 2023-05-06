#include "Customer.hpp"

Customer::Customer(Country* country, QString name)
    : ParentCountry(country)
    , Name(name)
{
}

bool Customer::validateNewLineName(QString name) const
{
    for (int i = 0; i < this->Lines.count(); i++) {
        if (this->Lines.at(i)->name() == name) {
            return false;
        }
    }
    return true;
}

bool Customer::validateEditLineName(Line* line, QString name)
{
    for (int i = 0; i < this->Lines.count(); i++) {
        // Don't refuse the validation of the same name
        if (this->Lines.at(i) == line) {
            break;
        }

        // Don't validate the name if another line has already the same
        if (this->Lines.at(i)->name() == name) {
            return false;
        }
    }
    return true;
}
