/* Open-Closed Principle */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Rectangle 
{
    protected:
        int width, height; 
    public:
        Rectangle(int width, int height):width(width), height(height) {}

        int getHeight() const { return height; }
        // void setHeight(int h) { height = h; }
        virtual void setHeight(int h) { height = h; }

        int getWidth() const { return width; }
        // void setWidth(int w) { width = w; }
        virtual void setWidth(int w) { width = w; }

        int area() { return width * height; }
};


// Suppose somewhere down the line, we decide to inherit from the rectangle 
// and make a square. 

class Square : public Rectangle
{
    public:
        Square(int size): Rectangle(size, size) {}
        /* -- Voilates the Liskov Substitution princple --
           If you have a function that takes a base class, any derived
           class should be able to be substituted into this function
           without any problems.
        */
        void setWidth(int w) override { width = height = w; }
        void setHeight(int h) override { width = height = h; }
};

void process(Rectangle& r)
{
    int w = r.getWidth(); 

    r.setHeight(10); // At this point Liskov substitution Principle is voilated for Square !

    cout << "Expected area=" << (w*10) << ", but got area=" << r.area() << endl;
}

int main(int argc, char *argv[])
{
    Rectangle r{3, 4}; 
    process(r);     // Ok ! - Expected area=30, but got area=30 

    Square sq{5};
    process(sq);    // Not Ok ! - Expected area=50, but got area=100


    /* 
    Point is :- You should be able to substitute a derived class (in this case Square which
    is derived from Rectangle), you should be able to substitute in to any location where a
    base class is being used. 
    */
    return 0;
}
