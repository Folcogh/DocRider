#include "DocIndex.hpp"

DocIndex* DocIndex::docindex = nullptr;

DocIndex::DocIndex()
{}

DocIndex::~DocIndex()
{}

DocIndex* DocIndex::instance()
{
    if (docindex == nullptr) {
        docindex = new DocIndex;
    }
    return docindex;
}

void DocIndex::release()
{
    if (docindex != nullptr) {
        delete docindex;
        docindex = nullptr;
    }
}

//
// Predicates
//

bool DocIndex::hasCustomer() const
{
    for (int i = 0; i < this->Countries.size(); i++) {
        if (this->Countries.at(i)->hasCustomer()) {
            return true;
        }
    }
    return false;
}

bool DocIndex::hasLine() const
{
    for (int i = 0; i < this->Countries.size(); i++) {
        if (this->Countries.at(i)->hasLine()) {
            return true;
        }
    }
    return false;
}

//
// Validators
//

bool DocIndex::validateNewCountryName(QString name) const
{
    // Don't validate the name if the country already exists
    for (int i = 0; i < this->Countries.size(); i++) {
        if (this->Countries.at(i)->name() == name) {
            return false;
        }
    }

    // The country doesn't exist yet, validate the name if it's not empty
    return !name.isEmpty();
}

bool DocIndex::validateExistingCountryName(Country* country, QString name) const
{
    for (int i = 0; i < this->Countries.size(); i++) {
        // Allow a name that has not really changed
        if (this->Countries.at(i) == country) {
            continue;
        }

        // Forbid a name of another country
        if (this->Countries.at(i)->name() == name) {
            return false;
        }
    }
    return true;
}
