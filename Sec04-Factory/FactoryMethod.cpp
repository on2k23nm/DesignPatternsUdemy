#include <iostream>

#include "FactoryMethod.h"

using namespace std;

int main(int argc, char *argv[])
{
    //! auto p1 = Point(10, M_PI_4); Not possible as ctor is private 

    auto p = Point::NewPolar(10, M_PI_4);

    cout << p << endl;

    return 0;
}