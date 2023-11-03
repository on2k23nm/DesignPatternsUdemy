#include <iostream>

#include "Factory.h"

using namespace std;

int main(int argc, char *argv[])
{
    //! auto p1 = Point(10, M_PI_4); Not possible as ctor is private 

    // with static methods
    auto p = PointFactory::NewCartesian(10, 11);
    cout << p << endl;

    // with non-static methods 
    PointFactory2 pf2; 
    auto p2 = pf2.NewCartesian(12, 13);

    cout << p2 << endl;


    return 0;
}