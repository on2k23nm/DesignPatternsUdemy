#ifndef PERSON_H
#define PERSON_H

#include <string>

class PersonBuilder; 
class PersonJobBuilder;
class PersonAddrBuilder;

class Person
{
    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddrBuilder; 
    
    // Address info
    std::string streetAddr, postalCode, city;
    
    // Employment info
    std::string compName, position;
    std::size_t annualSal{0};
    
    // Notice that those fields are private, and we're going to make several builders
    // to work on address and employment specifically. But even though there are 2 aspects
    // of the person class that we want to build up in seperate builders, the number of
    // classes we'll make for the builder infrastructure is actually 4 
    // Is this overenginnering ?? Yes maybe, but we need nice fluent interface !!

public:
    // Person providing static method for initilizing the builder
    static PersonBuilder create(); 
    

};

#endif // PERSON_H