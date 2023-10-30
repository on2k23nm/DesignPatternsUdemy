// This is my PersonBuilder.cpp file which has PersonBuilder()

#include "PersonBuilder.h"
#include "PersonAddrBuilder.h"
#include "PersonJobBuilder.h"

PersonBuilderBase::PersonBuilderBase(Person& person) : person(person)
{
    // do nothing here for now 
}

PersonAddrBuilder PersonBuilderBase::lives() const
{
    return PersonAddrBuilder{person}; 
}

PersonJobBuilder PersonBuilderBase::works() const
{
    return PersonJobBuilder{person};
}

PersonBuilder::PersonBuilder():PersonBuilderBase(p) // Note : p is the actual object which is getting created
{
    // do nothing here for now
}
