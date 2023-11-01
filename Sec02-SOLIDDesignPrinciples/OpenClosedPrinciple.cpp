/* Open-Closed Principle */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/* Let's say we are making a website which sells certain products 
   Each of those products have cerain traits such as color
 */
enum class Color { red, green, blue};
enum class Size { small, medium, big};

// Define a product 
struct Product {
    string name;
    Color color;
    Size size; 
};

// Define a simple Product filter
struct ProductFilter {
    vector<Product*> filterByColor(vector<Product*> items, Color color) {
        vector<Product*> results;
        for (const auto &e: items) {
            if (e->color == color)
                results.push_back(e);
        }

        return results;
    }

    vector<Product*> filterBySize(vector<Product*> items, Size size) {
        vector<Product*> results;
        for (const auto &e: items) {
            if (e->size == size)
                results.push_back(e);
        }

        return results;
    }

    vector<Product*> filterBySizeAndColor(vector<Product*> items, Size size, Color color) {
        vector<Product*> results;
        for (const auto &e: items) {
            if (e->size == size && e->color == color)
                results.push_back(e);
        }

        return results;
    }
};

// --- Implementation below using Open-Closed principle ---

template <typename T> struct AndSpecification;

// Specification base class
template <typename T> struct Specification
{
    virtual bool isSatisfied(T* item) = 0;
};

// Filter base class
template <typename T> struct Filter
{
    virtual vector<T*> filter (vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{
    vector<Product *> filter(vector<Product*> items, Specification<Product> &spec) override
    {
        vector<Product*> results;
        for (const auto &item : items)
        {
            if (spec.isSatisfied(item))
                results.push_back(item);
        }

        return results;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color; 

    ColorSpecification(Color color): color(color) {}
    bool isSatisfied(Product *item) override
    {
        return color == item->color; 
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size; 

    SizeSpecification(Size size): size(size) {}
    bool isSatisfied(Product *item) override
    {
        return size == item->size; 
    }
};

template <typename T> struct AndSpecification : Specification<T>
{
    Specification<T> &first; 
    Specification<T> &second; 

    AndSpecification(Specification<T> &first, Specification<T> &second):
        first(first), second(second) {}

    bool isSatisfied(T *item) override
    {
        return first.isSatisfied(item) && second.isSatisfied(item); 
    }
};

int main(int argc, char *argv[]) {
    Product apple { "Apple", Color::green, Size::small };
    Product tree  { "Tree", Color::green, Size::big };
    Product house { "House", Color::blue, Size::big };

    vector<Product*> items { &apple, &tree, &house };

    ProductFilter pf; 
    auto green_things = pf.filterByColor(items, Color::green);

    for (const auto &item: green_things)
        cout << "Item " << item->name << " is green" << endl;

    auto big_things = pf.filterBySize(items, Size::big);
    for (const auto &item: big_things)
        cout << "Item " << item->name << " is big" << endl;

    auto big_green_things = pf.filterBySizeAndColor(items, Size::big, Color::blue);
    for (const auto &item: big_green_things)
        cout << "Item " << item->name << " is big and blue" << endl;

    /* 
     * -- Same has been implemented below usnig Open-Closed principle --
     * Open-Closed principle : Open (for extention) - Closed (for modification) principle 
     * The goal of the open-closed principle is to avoid
     * having to jump into code you had already written. Open for extension means you can
     * always make a new specification by extending (inheriting) but closed for modification
     * In the context of the Specification pattern, you would never require yourself to go back
     * into the Filter interface or the Specification interface - you would never need to change
     * them, you would extend them by inheritance and then you would make combinators like
     * AndSpecification, Orspecification, etc.
     * Notice that we have template arguments for Specification & Filters, so we have not constrained
     * ourselves with Product, we can also have other kinds of items in here.
     */
    BetterFilter bf; 
    ColorSpecification green(Color::green);
    SizeSpecification big(Size::big);

    for (const auto &item: bf.filter(items, green))
    {
        cout << "Item " <<  item->name << " is green" << endl;
    }

    for (const auto &item: bf.filter(items, big))
    {
        cout << "Item " <<  item->name << " is big" << endl;
    }

    AndSpecification<Product> greenAndBig(green, big);
    for (const auto &item: bf.filter(items, greenAndBig))
    {
        cout << "Item " <<  item->name << " is green & big" << endl;
    }

    return 0;
}
