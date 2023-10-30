// Person.cpp
#include "Person.h"
#include "PersonBuilder.h"

PersonBuilder Person::create()
{
    return PersonBuilder();
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << "Street Address :" << p.streetAddr << "\n";
    os << "Postal Code    :" << p.postalCode << "\n";
    os << "Company Name   :" << p.compName << "\n";
    os << "Position       :" << p.position << "\n";
    os << "Annual Income  :" << p.annualSal;

    return os;
}

// Output :
// $ ./Sec03/BuilderFacets
// Street Address :123 London Road
// Postal Code    :SW1 1GB
// Company Name   :PragmaSoft
// Position       :Software Engineer
// Annual Income  :150000
