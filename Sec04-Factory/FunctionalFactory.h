#ifndef FUNCTIONAL_FACTORY_H
#define FUNCTIONAL_FACTORY_H

#include "HotDrink.h"
#include "HotDrinkFactory.h"

#include <map>
#include <string>
#include <functional>

/*
    In our demonstration of Abstract Factory design pattern we generally follow
    Object Oriented approach, but it is equally possible nowadays to follow a more
    functional approach.

    How we can build a similar factory but without necessarily relying on factories
    as such. Because instead of these factories what you can do is you can have simple
    lambda functions describing how a particular drink is made.


*/

// With DrinkWithVolumeFactory, we want to provide volume of the drnk that we actually
// want to make. What we can do it, we can actually configure it as follows -
class DrinkWithVolumeFactory
{
    // we are going to have a map from name of the drink to the Factory, which actually
    // creates the drink, we are going to have a map from name of the drink to a function. 
    // this function will define how this drink is actually made. Instead of using a factory
    // we are going to use a anonymous function. 

    // Note that, function that returns unique_ptr<HotDrink> and takes no argument 
    std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumeFactory()
    {
        // initialize the factories by just providing the lambdas in place. 
        // for ex. if you want to specify when you amke tea you make 200 ml and when
        // you make coffee you make 100 ml. 

        // This is the factory method
        factories["Tea"] = [] {
            auto tea = std::make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };

        factories["Coffee"] = [] {
            auto coffee = std::make_unique<Coffee>();
            coffee->prepare(100);
            return coffee;
        };
    }

    std::unique_ptr<HotDrink> makeDrink(const std::string& name)
    {
        return factories[name]();
    }
};

#endif /* FUNCTIONAL_FACTORY_H */