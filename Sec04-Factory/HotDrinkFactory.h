#ifndef HOTDRINK_FACTORY_H
#define HOTDRINK_FACTORY_H

#include "HotDrink.h"
#include <memory>

/*
    [ ** This file is continued from HotDrink.h **]

    We have abstract factory (HotDrinkFactory) from which
    we inherit and we can actually try and make certain products.
*/

struct HotDrinkFactory
{
    virtual std::unique_ptr<HotDrink> make() const = 0;
};


// --- Family of Drink Factories  ---

struct TeaFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Tea>(); 
    }
};

struct CoffeeFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Coffee>(); 
    }
};

#endif /* HOTDRINK_FACTORY_H */