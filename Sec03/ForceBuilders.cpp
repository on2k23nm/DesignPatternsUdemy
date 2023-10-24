/* Open-Closed Principle */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>

using namespace std;


class HtmlBuilder;

// element is just going to represent a tag,including anything inside the tag "<name>text</name>"
// this is just a utility class for modelling an HTML element
class HtmlElement
{
    friend class HtmlBuilder;

    string name, text; 
    vector<HtmlElement> elements; // inner HtmlElements
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text): name(name), text(text) {} 

    public:
        string str(size_t indent = 0) const
        {
            ostringstream oss;
            size_t nr_spaces = indent_size*indent;

            string i(nr_spaces, ' ');
            oss << i << "<" << name << ">" << endl;
            
            if (text.size() > 0)
                oss << string(indent_size*(indent + 1), ' ') << text << endl;

            for (const auto& e: elements)
                oss << e.str(indent + 1);

            oss << i << "</"  << name << ">" << endl;

            return oss.str(); 
        }

        static HtmlBuilder build(string rootName);
}; 

// Builder pattern
class HtmlBuilder
{
    HtmlElement root; // top-level element

    public:  
        HtmlBuilder(string rootName)
        {
            root.name = rootName;
        }

        // utility functions to add elements
        HtmlBuilder& addChild(string childName, string childText)
        {
            // Note that here vector can't access HtmlElement ctor as it is private
            root.elements.emplace_back(HtmlElement(childName, childText));
        
            return *this; // For fluent-interface 
        }

        // we want str() function now which returns a string representation of whatever
        // it is that we are actually building.
        string str() const
        {
            return root.str(); 
        }
};

HtmlBuilder HtmlElement::build(string rootName)
{
    return HtmlBuilder(rootName);
}

int main(int argc, char *argv[])
{
    
    auto builder2 = HtmlElement::build("ul");
    builder2.addChild("li", "hello").addChild("li", "world");
    cout << builder2.str();

    return 0;
}

/*
OUTPUT:
$ ./Sec03/LifeWithoutBuilders 
<ul>
  <li>
    hello
  </li>
  <li>
    world
  </li>
</ul>
$
*/