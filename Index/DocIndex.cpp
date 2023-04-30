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

bool DocIndex::validateNewCountryName(QString name) const
{
    // Don't validate the name if the country already exists
    for (int i = 0; i < Countries.size(); i++) {
        if (Countries.at(i)->name() == name) {
            return false;
        }
    }

    // The country doesn't exist yet, validate the name if it's not empty
    return !name.isEmpty();
}

void DocIndex::newCountry(Country* country)
{
    this->Countries.append(country);
}
