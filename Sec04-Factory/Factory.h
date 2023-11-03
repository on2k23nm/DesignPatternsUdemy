#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <ostream>


/* 
    We have 2 Factory methods (static member functions) inside Point, 
    but sometimes what you really want to do is you want to do even more
    in terms of SoC (seperation of concerns). So if you have dedicated code
    for the construction of Point object, why not move it into a sepeate
    component ?

*/
struct PointFactory;

class Point 
{
    friend struct PointFactory; // Violates the OpenClose Principle, friend class mechanism is hostile to OCP.
    friend struct PointFactory2;

    friend std::ostream& operator<<(std::ostream& os, const Point &p); 
    double x, y;
    
    // Create a private constructor 
    Point(double x, double y): x(x), y(y) {}
};

// what this actually is is a dedicated factory. In Go4 there is no pattern called factory - 
// there is 1) Factory method, 2) Abstract Factory
// This is a concrete factory, definitely not abstract.
// 
// What's gonna happen here ? 
// 1) Take factory methods NewCartesian and NewPolar and stick them in the PointFactory  (Cut, Paste)
// 2) Now, there are lots of different options how you want to expose the point factory 
//    a) construct the factory itself in main(), only problem here is that the private constructor 
//       in Point is inaccessible 
//    b) Make everthing in Point as public ! (not good ! )
struct PointFactory
{
    // Below 2 are factory methods moved here from Point ! (they don't have to be static now)
    static Point NewCartesian(double x, double y)
    {
        return {x, y}; // [in Modern C++] this is same as Point{x,y}, type is inferred from return type. 
    }
    
    static Point NewPolar(double r, double theta)
    {
        return {r * cos(theta), r * sin(theta)};
    }
};

struct PointFactory2
{
    // Below 2 are factory methods moved here from Point ! (they don't have to be static now)
    Point NewCartesian(double x, double y)
    {
        return {x, y}; // [in Modern C++] this is same as Point{x,y}, type is inferred from return type. 
    }
    
    Point NewPolar(double r, double theta)
    {
        return {r * cos(theta), r * sin(theta)};
    }

};
std::ostream& operator<<(std::ostream& os, const Point &p)
{
    os << "<x=" << p.x << ",y=" << p.y << ">"; 

    return os;
}

#endif /* FACTORY_METHOD_H */