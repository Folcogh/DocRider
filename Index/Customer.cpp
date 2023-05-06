#include "Customer.hpp"

Customer::Customer(Country* country, QString name)
    : ParentCountry(country)
    , Name(name)
{
}
