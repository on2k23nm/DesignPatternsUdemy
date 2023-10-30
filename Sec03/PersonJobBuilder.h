//PersonJobBuilder.h
#ifndef PERSONJOBBUILDER_H
#define PERSONJOBBUILDER_H

#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase
{
public:
    PersonJobBuilder(Person &p) : PersonBuilderBase(p) {}
    
    PersonJobBuilder& at(std::string comp)
    {
        person.compName = comp;
        return *this;
    }

    PersonJobBuilder& as(std::string p)
    {
        person.position = p;
        return *this;
    }

    PersonJobBuilder& earning(std::size_t sal)
    {
        person.annualSal = sal;
        return *this;
    }
};

#endif