#include <iostream>

#include "InnerFactory.h"

using namespace std;

int main(int argc, char *argv[])
{
    // one way of calling 
    auto p1 = Point1::PointFactory1::NewPolar(5, M_PI_4);
    cout << p1 << endl;

    // Another way 
    auto p2 = Point2::Factory.NewPolar(5, M_PI_4);
    cout << p2 << endl;
    
    return 0;
}