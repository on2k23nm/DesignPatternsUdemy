/* Open-Closed Principle */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>

using namespace std;

/*
-- backend web server -- 
*/


/*
start creating object oriented structures which actually represent the
different part of the HTML that you are building.
*/
struct HtmlBuilder;

// element is just going to represent a tag,including anything inside the tag "<name>text</name>"
// this is just a utility class for modelling an HTML element
struct HtmlElement
{
    string name, text; 
    vector<HtmlElement> elements; // inner HtmlElements
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text): name(name), text(text) {} 

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
// Now, this gets you the structure, now the interesting thing is how do you actually
// build up these elements ? This is where the builder pattern comes in.


// Builder pattern
struct HtmlBuilder
{
    HtmlElement root; // top-level element
    
    HtmlBuilder(string rootName)
    {
        root.name = rootName;
    }

    // utility functions to add elements
    HtmlBuilder& addChild(string childName, string childText)
    {
        root.elements.emplace_back(childName, childText);
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
    // Web server 
    auto text = "hello"; 
    string output; 

    output += "<p>";
    output += text; 
    output += "</p>";

    cout << output << endl;

    // scale 
    string words[] = { "hello", "world" };
    ostringstream oss; 
    oss << "<ul>\n";
    for (auto w: words)
        oss << "  <li>" << w << "</li>\n";
    oss << "</ul>";
    cout << oss.str() << endl;

    /* 
       -- building simple bits of HTML out of strings (approach that doesn't scale) --
       html has para, list items, images et. It also defines certain
       rules as to what kind of tags can contain what other kind of tag
       none of this is being enforced in OO fashion. 

       Idea of the builder design pattern is that instead of building together
       a strout of little concatinations (hello, world), you define sort of OO
       structure which supports its transformation to a string. 
    */
    HtmlBuilder builder("ul");
    builder.addChild("li", "hello");
    builder.addChild("li", "world");
    cout << builder.str();

    /*
    One of the improvements to our implementation
    of the builder is something called a "Fluent Interface"
    We've got 2 addChild() calls one after another. What
    if we can do it like below -
    */

    HtmlBuilder builder1("ul");
    builder1.addChild("li", "hello").addChild("li", "world"); // fluent interface
    // // ^^^^^^^^^^ to make a fluent interface we simply change the return type of addChild to pointer/ref
    // // to HtmlBuilder, we can keep calling addChild after that to inf. 
    // // This is particularly convenient in builders because - 
    // // 1) Sometimes builders you make want to do several very similar things
    // // 2) You might want to specify how the chain of build commands can be constructed.
    cout << builder1.str(); 

    // Another thing you can do is to give hint to the consumer/client that they should
    // actually be using the Builder.Up to you how you can do this, but one way is to use static
    // funtion in HTMLElement, see above (the function is not inline because it is giving compilation issues)
    // After you do all that, you can say something like this - 
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