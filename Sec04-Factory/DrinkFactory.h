#ifndef DRINK_FACTORY_H
#define DRINK_FACTORY_H

#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <map>
#include <string>

/*
    DrinkFactory is something that is going to keep track
    of kind of factories that we have. It's the facilitator
    for all of the factories that we have made and having them in
    some sort of map and exposing to whoever is actually interested
    in making a drink.

    DrinkFactory class is going to help us construct drinks on the
    basis of the different factories. There are different ways in which
    we can play this, but in our case we are going to have a map.

    Instead of calling if statement for tea/coffee, you make it more orgainzed.
*/

class DrinkFactory
{
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hotDrinkFactories;
public:
    DrinkFactory()
    {
        hotDrinkFactories["Coffee"] = std::make_unique<CoffeeFactory>();
        hotDrinkFactories["Tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> makeDrink(const std::string& name, std::size_t quant)
    {
        auto d = hotDrinkFactories[name]->make();
        d->prepare(quant);

        return d;
    }
};

#endif /* DRINK_FACTORY_H */