#include "Country.hpp"
#include <QMessageBox>

Country::Country(QString name)
    : Name(name)
{
}

QString Country::name() const
{
    return this->Name;
}
