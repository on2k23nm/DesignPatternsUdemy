#ifndef HOTDRINK_H
#define HOTDRINK_H

#include <iostream>

/* 

    So fat we have covered only one Go4 design pattern, and that is factory method. Now
    it's time for us to cover the other side, that is the Abstract factory.

    As name suggests - this is "families of factories" or "families of products" and corresponding
    families of factories which use inheritance to actually allow you to polymorphically call on the
    different factories.

    Below is a convoluted example, but we are going to go through it anyway.

    We are going to emulate a hot drink machine which can take tea/coffee or something else. 

    1) First, create a interface struct HotDrink:
        a) Create a virtual destructor
        b) Create method for preparing a drink of specified volume. (make this a pure virtual function)
    2) Now we have family of products - 
        a) For Tea, we'll inherit from Hotdrink
        b) create a prepare function that overrides the virtual function HotDrink::prepare
        c) Similarly create for Coffee..
        So now we have family of objects.
    3) What we can now do is we can have a corresponding family of factories. 
        a) Let's generate HotDrink factory (see separate file HotDrinkFactory.h)
*/

struct HotDrink
{
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0; 
};

// Product 1 - Tea
struct Tea : HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Take a Tea bag, boil water, pour " << volume << " ml, "
            << "add some Lemon and enjoy !" << std::endl;
    }
};

// Product 2 - Coffee 
struct Coffee : HotDrink
{
    void prepare(int volume) override
    {
        std::cout << "Grind some beans, boil water, pour " << volume
            << " ml, add some cream and enjoy !" << std::endl;
    }
};

#endif /* HOTDRINK_H */