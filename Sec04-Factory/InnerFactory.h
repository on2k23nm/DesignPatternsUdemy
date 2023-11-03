#ifndef INNER_FACTORY_H
#define INNER_FACTORY_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <ostream>


/* 
    Put the Factory itself right inside the type and expose it as a way 
    of giving a hint as to - 
    1) What you should be doing ?
    2) What you should be constructing ?

    This also solves a second problem - that is the problem of breaking the OCP (Open close principle)

    If you are prepared to sort of  plan ahead and make sure that your factories is made the same time
    that your actual type is made you can avoid this whole business of having friend class in the first
    place because Inner classes have access to the private members of the outer classes.

    Q: How do you want to expose the factory ?
    1) Bring PointFactory inside Point1 as private and access it like this --  (as in class Point1)
        Point1::PointFactory1::NewPolar(5, M_PI_4);
    2) Make PointFactory private - now you won't be able to access PointFactory from main() because it is private to Point (see class Point2)
       but what you can do it is make it effectively singleton. Essentially what you can do is you can make it an instance of Factory and expose
       that instance directy from the point.

*/

class Point1 
{
    friend std::ostream& operator<<(std::ostream& os, const Point1 &p); 
    double x, y;
    
    Point1(double x, double y): x(x), y(y) {}
public:
    struct PointFactory1
    {
        // Below 2 are factory methods moved here from Point ! (they don't have to be static now)
        static Point1 NewCartesian(double x, double y) // static is still required 
        {
            return {x, y}; // here we can use the constructor of Point even though it's private 
        }
        
        static Point1 NewPolar(double r, double theta)
        {
            return {r * cos(theta), r * sin(theta)};
        }

    };
};

class PointFactory2;

class Point2
{
    friend std::ostream& operator<<(std::ostream& os, const Point2 &p); 
    double x, y;
    
    Point2(double x, double y): x(x), y(y) {}

    class PointFactory2
    {
        PointFactory2() {}
    public:
        // Below 2 are factory methods moved here from Point ! (they don't have to be static now)
        static Point2 NewCartesian(double x, double y) // static is necessary 
        {
            return {x, y}; 
        }
        
        static Point2 NewPolar(double r, double theta) // static is necessary 
        {
            return {r * cos(theta), r * sin(theta)};
        }
    };
public:
    static PointFactory2 Factory;  // Instance of factory
};

// for Point1
std::ostream& operator<<(std::ostream& os, const Point1 &p)
{
    os << "<x=" << p.x << ",y=" << p.y << ">"; 

    return os;
}

// for Point2
std::ostream& operator<<(std::ostream& os, const Point2 &p)
{
    os << "<x=" << p.x << ",y=" << p.y << ">"; 

    return os;
}

#endif /* INNER_FACTORY_H */