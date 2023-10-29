/* Groovy-Styled Builder */
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>

using namespace std;


/*
    -- Uniform Iniitialization Syntax --
*/

// we are going to use Tag as base class to allow the clients to
// actually write something that looks like HTML.
struct Tag 
{
    // What we'r going to do is to use this tag as a base class
    // in order to allow the clients to actually write something
    // which looks a lot like HTML.

    // add o/p operator, the stream op operator. That's going to be useful
    // for printing the whole thing. It is a rather involved chunk of code.
    friend ostream& operator<<(ostream& os, const Tag& tag);



    string name, text; 
    vector<Tag> children; 
    vector<pair<string, string>> attributes; 

protected:
    Tag (const string& name, const string &text):
        name(name), text(text) {}
    Tag (const string& name, const vector<Tag>& children):
        name(name), children(children) {} 
};

// HTML has concrete implementations of different tags like for ex. a Paragraph
// So we're going to define a paragraph as a inherited class 
struct ParaGraph : Tag
{
    ParaGraph(const string& text) : Tag("p", text) {}
    ParaGraph(initializer_list<Tag> children) : Tag("p", children) {}
};

// Image tag
struct Image : Tag
{
    explicit Image(const string& url) : Tag{"Img", ""}
    {
        attributes.emplace_back("src", url);
    }
};

ostream& operator<<(ostream& os, const Tag& tag)
{
    os << "<" << tag.name; 

    for (const auto& att : tag.attributes)
        os << " " << att.first << "=\"" << att.second << "\"";
    if (tag.children.size() == 0)
    {
        os << "/>" << endl;
    }
    else
    {
        os << ">" << endl;

        if (tag.text.length())
            os << tag.text << endl;
        
        for (const auto& child : tag.children)
            os << child; 
        
        os << "</" << tag.name << ">";        
    }

    return os;
}

int main(int argc, char *argv[])
{
    // what I'm trying to show here is that, thanks to single mechanism of
    // uniform initilizaton in C++, what you can do is to construct pseudo DSLs (Domain Specific Language), and
    // furthermore it's interesting to know that you can actually constrain what elements go inside other elements
    // by difining different constructors on all of these elements. Ex. Image can't contain any other tags,
    // so it simply doesn't have a constructor which takes initializer_list.

    // This is a small aside to a overall discussion of builder concept, but essentially it is very similar because
    // you are using/abusing uniform initializaton syntax to define structures in a more natural and understandable
    // way
    cout <<  ParaGraph{Image{"http://pokemon.com/pikachu.img"}}  << endl;
    
    return 0;
}