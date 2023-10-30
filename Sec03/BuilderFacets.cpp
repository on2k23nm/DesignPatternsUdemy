#include <iostream>

using namespace std;

/*
    -- Using multiple builders to build an object --
    Case of object being so complicated that you actually need seperate builders for several
    different aspects of that particular object.

    Builder facade (facade is yet another design pattern which is part of this course)
*/

#include "Person.h"
#include "PersonBuilder.h"

int main(int argc, char *argv[])
{
    // Goal of our execise is to write somethign like the following 
    Person p = Person::create().lives().at("123 London Road").withPostalCode("SW1 1GB").in("London").works().at("PragmaSoft").as("Software Engineer").earning(150000);

    return 0;
}