// PersonBuilder.h
#ifndef PERSONBUILDER_H
#define PERSONBUILDER_H

#include "Person.h"

class PersonJobBuilder;
class PersonAddrBuilder;

class PersonBuilderBase
{
protected:
    Person& person;
public:
    explicit PersonBuilderBase(Person& person);

    operator Person() const
    {
        return std::move(person);
    }

    PersonAddrBuilder lives() const; 
    PersonJobBuilder  works() const; 
};

// Dedicated builder for objects of type person. But there is a problem, we want
// to be using this class as a baseclass for PersonJobBuilder & PersonAddrBuilder
class PersonBuilder : public PersonBuilderBase
{
private:
    Person p;
    // Problem is, if you inherit from it, you end up repllicating object over and over 
    // Solution : 
    // 1) Use base class that doesn't have the object, but just has a reference to object
    // 2) Use a derived class which doesn't have the object.
    // (this is the place where the object is really being built up)
public:
    PersonBuilder();
    // In the implementation of this ctor, we are passing p by-reference to PersonBuilderBase
    // reason why we'r doing it is that we want to inherit from PersonBuilderBase and not
    // from PersonBuilder
};

#endif // PERSONBUILDER_H