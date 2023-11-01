/* Open-Closed Principle */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>

using namespace std;

/*
Dependency Inversion Principle is actually split into 2 ideas :-  
1)	High level modules should not depend on low-level modules. Both should depend on abstractions.
2)	Abstractions should not depend on details. Details should depend on Abstractions
*/

// Model relationships between different people

// This signifies relationship between Person A and Person B
enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

// // Low level constructs to store the relationships 
// // low-level because essentially all it does is to provide functionality
// // for data storage.
// struct Relationships
// {
//     vector<tuple<Person, Relationship, Person>> relations; 
//     void addParentAndChild(const Person& parent, const Person& child)
//     {
//         relations.push_back({parent, Relationship::parent, child});
//         relations.push_back({child, Relationship::child, parent});
//     }

//     void printRelations()
//     {
//         for (const auto& relation: relations)
//         {
//             const Person& person1 = get<0>(relation);
//             const Relationship& relationship = get<1>(relation);
//             const Person& person2 = get<2>(relation); 

//             cout << person1.name << " is the " 
//              << (relationship == Relationship::parent ? "parent of " : "child of ")
//              << person2.name << endl; 
//         }
//     }
// };

// // High-level module - which is going to depend on Low-level module like Relationships 
// // If we want to do research on the data, we have to have a high-level module 
// struct Research
// {
//     // to do the research, somehow we need to get the data, but the worst thing to
//     // do here, which breaks the dependency inversion principle is to actually take
//     // a direct dependency on a low level module.
//     Research(Relationships& relationships)
//     {
//         auto& relations = relationships.relations;
//         // HL module starts depending on LL module, using vector in Relationships

//         // Suppose Relationships module decides to make relations private or give 
//         // the vector some other name, this code is broken. So Dependency Inversion Principle
//         // protects you from changes in the implementation details. 
//         for (const auto& r: relations)
//         {
//             const Person& person1 = get<0>(r);
//             const Relationship& relationship = get<1>(r);
//             const Person& person2 = get<2>(r);

//             if (person1.name == "John" && relationship == Relationship::parent)
//             {
//                 cout << person2.name << " is the child of John" << endl;
//             } 
//         }
//     }
// };

// -- the fix -- 
// 1) You can typically fix it through abstraction. Instead of having direct dependency on some low level module,
//    you would typically introduce some interface. 
// 2) The other part of the problem is really if you want to find all the children of a particular person,
//    then I would argue that the Single responsibility principle still puts this resoinsibility as part
//    of the relationships class. So your Research class doen't really have to delve into finding
//    the children of somebody. You can move it down to low level module.

struct RelationshipBrowser // Interface for struct Relationships
{
    virtual vector<Person> findAllChildren(const string& parentName) = 0;
};

// Now, Relationships is providing functionality of RelationshipBrowser
struct Relationships : RelationshipBrowser
{
    vector<tuple<Person, Relationship, Person>> relations; 
    void addParentAndChild(const Person& parent, const Person& child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    void printRelations()
    {
        for (const auto& relation: relations)
        {
            const Person& person1 = get<0>(relation);
            const Relationship& relationship = get<1>(relation);
            const Person& person2 = get<2>(relation); 

            cout << person1.name << " is the " 
             << (relationship == Relationship::parent ? "parent of " : "child of ")
             << person2.name << endl; 
        }
    }

    vector<Person> findAllChildren(const string& parentName)
    {
        vector<Person> pvec; 
        
        for (const auto& r: relations)
        {
            const Person& person1 = get<0>(r);
            const Relationship& relationship = get<1>(r);
            const Person& person2 = get<2>(r);

            if (person1.name == parentName && relationship == Relationship::parent)
            {
                pvec.push_back(person2);
            } 
        }

        return pvec;
    }

};

/*
This approach follows the Dependency Inversion Principle, allowing the Research
class to depend on an abstraction (RelationshipBrowser) rather than a concrete 
implementation (Relationships). This makes your code more flexible and easier to
maintain, as you can easily swap out different implementations of the RelationshipBrowser
interface.
*/
struct Research
{
    RelationshipBrowser& browser; // Dependency on the RelationshipBrowser interface

    Research(RelationshipBrowser& browser): browser(browser)
    {
        // vector<Person> children = browser.findAllChildren("John");
        // for (const auto& child : children)
        // {
        //     cout << child.name  << " is the child of John" << endl;
        // }
    }

    void performResearch(const string& parentName)
    {
        vector<Person> children = browser.findAllChildren(parentName);

        // Now you can work with the 'children' vector
        for (const auto& child : children)
        {
            cout << parentName << " is the parent of " << child.name << endl;
        }
    }
};

int main(int argc, char *argv[])
{
    Person parent{"John"};
    Person child1{"Matt"}, child2{"Chris"};

    Relationships relationships;
    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    //relationships.printRelations();

    /*
    Now, when you create an instance of Research, you can pass an instance of
    Relationships (which implements the RelationshipBrowser interface) to its
    constructor. This allows Research to work with the findAllChildren method through
    the RelationshipBrowser interface:
    */
    Research research(relationships); // Inject the dependency

    research.performResearch("John");

    return 0;
}

// Dependency Injection allows you to specify certain defaults - for example, dependancy injection
// would allows you to specify that whenever somebody wants a RelationshipBrowser, they should
// be provided a copy or reference to Relationships class. So this is how Dependancy injection kind
// of plays on top of the Dependency Inversion principle.
// But, Dependency Inversion principle just basically says that both of the HL & LL module should
// really be depending on abstraction and you shouldn't depend on details of somebody elses
// implementation.