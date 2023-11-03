#ifndef POINT_EXAMPLE_H
#define POINT_EXAMPLE_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <ostream>

/* 
Let's imagine that we're building a structure for representing
a 2-D point 
*/

/*
enum class PointType
{
    cartesian, 
    polar
};

struct Point
{
    float x, y; 

    // a, b are just silly, they are not in any way helpful in figuring
    // out what you neeed to feed. 
    // ex. if you are feeding in Polar coordinates, does a correspond to rho or to theta ?
    Point(float a, float b, PointType type = PointType::cartesian)
    {
        if (type == PointType::cartesian)
        {
            x = a; 
            y = b;
        }
        else
        {
            x = a * cos(b); 
            y = a * sin(b);
        }
    }

    // Factory pattern is all about making sure that the interface that a particular type provides
    // is sensible, understandable, it’s immediately consumable by the client. When they see the interface,
    // they know exactly how the construction of the object actually happens. 


    // let's say we want to represent a point in polar coordinates 
    // Point (float rho, float theta); <-- unfortunately we can't do this because that ctor is already there.

    // So we somehow need to refactor this code to allow initialization from Polar coordinates.

    // we are going to mitigate the limitation of ctor, byt moving the initialization from a ctor to some
    // other struct.
    
};
*/

/* 
    Below is the implementation for Factory method, we essentially have the following - 

    1. Static methods which allow you to construct a particular object
    2. ctor has been made private, so that it can't be used for construction of object from outside.

*/
class Point 
{
    friend std::ostream& operator<<(std::ostream& os, const Point &p); 
    double x, y;
    
    // Create a private constructor 
    Point(double x, double y): x(x), y(y) {}
public:
    // double x, y;

    // Below are Couple of static member functions. These member functions are going to allow us actually
    // construct the object on the basis of certain coordinates.
    static Point NewCartesian(double x, double y)
    {
        return {x, y}; // [in Modern C++] this is same as Point{x,y}, type is inferred from return type. 
    }
    
    static Point NewPolar(double r, double theta)
    {
        return {r * cos(theta), r * sin(theta)};
    }
};

std::ostream& operator<<(std::ostream& os, const Point &p)
{
    os << "<x=" << p.x << ",y=" << p.y << ">"; 

    return os;
}

#endif /* POINT_EXAMPLE_H */