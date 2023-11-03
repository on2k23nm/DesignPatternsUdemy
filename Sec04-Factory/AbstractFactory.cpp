#include <iostream>

#include "HotDrinkFactory.h"
#include "DrinkFactory.h"

using namespace std;

// // If AF wasn't there, we would do this and call it in main()
// unique_ptr<HotDrink> makeDrink(string type)
// {
//     unique_ptr<HotDrink> drink; 

    
//     if (type == "Tea")
//     {
//         drink = make_unique<Tea>(); 
//         drink->prepare(200);
//     }
//     else
//     {

//         drink = make_unique<Coffee>(); 
//         drink->prepare(50); 
//     }
// }

int main(int argc, char *argv[])
{
    // Without AF, you would call somethign like this 
    // auto d = makeDrink("Tea");

    // With AF 
    DrinkFactory df; 
    auto c = df.makeDrink("Coffee", 200);
    auto t = df.makeDrink("Tea", 100);

    return 0;
}

/*
NOTES:

-- Idea of Abstract factories -- 
1) You have family of products (in HotDrink.h)
2) You have a corresponding family of factories (in HotDrinkFactory.h)
3) Because they all share common interface HotDrinkFactory::make(), you can stick them in any kind of data structure. In this
   we made a DrinkFactory where we stuck the factories in a map from string to whatever their implementation is. 
4) When you invoke one of them, you get the appropriate element by key from the map (in DrinkFactory::makeDrink()) and then you
   call make() on it polymorphically.
5) You get the drink, prepare the drink ! - drink itself is also polymprphic because it's family of factories and family of
   products.So you call something polymorphically on the drink and you return that drink in this case as unique_ptr.

This is pretty much the gist of the Abstract Factory Design pattern.

*/