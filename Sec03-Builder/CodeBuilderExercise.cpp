// Builder Coding Exercise

// You are asked to implement the Builder design pattern for rendering simple chunks of code.

// Sample use of the builder you are asked to create:

//     auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
//     cout << cb;

// The expected output of the above code is:

//     class Person
//     {
//       string name;
//       int age;
//     };

// Please observe the same placement of curly braces and use two-space indentation.


#include <string>
#include <ostream>
#include <vector>   
#include <utility>  // required for pair
#include <sstream>  // required for ostringstream
#include <iostream>

using namespace std;

class CodeBuilder;

class CodeElement
{
    friend class CodeBuilder;
    
    string className;  // name of the struct
    vector<pair<string, string>> elements; // name of the members inside the struct 
    const size_t indentSize = 2;    // indentation 

    CodeElement() {} // this has to be kept private
public:
    string str(size_t indent=0) const
    {
        ostringstream oss; 

        size_t nrSpaces = indentSize * indent;

        string ind(nrSpaces, ' ');
        oss << ind << "class " << className << "\n";

        oss << "{" << "\n";

        ++indent;
        nrSpaces = indentSize * indent;

        ind = string(nrSpaces, ' ');

        // now print the elements 
        for (const auto& e: elements)
            oss << ind << e.second << " " << e.first << ";" << "\n";

        oss << "};" << "\n";

        return oss.str();        
    }

    // static CodeBuilder build(string rootName);
};

class CodeBuilder
{
    friend ostream& operator<<(ostream& os, const CodeBuilder& obj);
    
    CodeElement root; // top-level element
public:
    CodeBuilder(const string& className)
    {
        root.className = className;
    }
    
    CodeBuilder& add_field(const string& name, const string& type)
    {
        root.elements.emplace_back(name, type);

        return *this;
    }

    string str() const { return root.str(); }
};

ostream& operator<<(ostream& os, const CodeBuilder& obj)
{
    os << obj.str();

    return os;
}

int main(int argc, char *argv[])
{
    
    auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    cout << cb;

    return 0;
}