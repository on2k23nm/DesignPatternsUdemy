#ifndef PERSONADDRBUILDER_H
#define PERSONADDRBUILDER_H

#include "PersonBuilder.h"

class PersonAddrBuilder : public PersonBuilderBase
{
public:
    PersonAddrBuilder(Person &person) : PersonBuilderBase(person) {}
    
    // ---------- FLUENT INTERFACE ------------
    PersonAddrBuilder& at(std::string streetAddr)
    {
        person.streetAddr = streetAddr;
        return *this;
    }

    PersonAddrBuilder& withPostalCode(std::string pc)
    {
        person.postalCode = pc;
        return *this;
    }

    PersonAddrBuilder& in(std::string c)
    {
        person.city = c;
        return *this;
    }
};

#endif