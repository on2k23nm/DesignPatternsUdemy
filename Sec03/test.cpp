// emplace_back try 

#include <vector>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

struct President
{
    std::string name;
    std::string country;
    int year;
 
    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        cout << "I am being constructed - [" << this << "]" << endl;
    }
 
    President(President&& other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        cout << "I am being moved - [" << this << "]" << endl;
    }

    President(const President& other)
        : name(other.name), country(other.country), year(other.year)
    {
        cout << "I am being copied - [" << this << "]" << endl;
    }
 
    President& operator=(const President& other) = default;

};
int main(int argc, char *argv[])
{
    // vector<President> elections;
    // cout << "emplace_back:" << endl;
    // auto& ref = elections.emplace_back("Nelson Mandela", "South Africa", 1994);
    // cout << &elections[0] << endl;
    // assert(ref.year == 1994 && "uses a reference to the created object (C++17)");
 
    // vector<President> reElections;
    // cout << "rv push_back:" << endl;
    // reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    vector<President> nextElections;
    cout << "1. dt create:" << endl;
    President p("Donald J. Trump", "the USA", 2024);
    cout << "1. dt push_back:" << endl;
    nextElections.push_back(p);
    cout << "1. Done" << endl;
    cout << "------------------" << endl;
    vector<President> nextElections1;
    cout << "2. dt create:" << endl;
    President p2("Donald J. Trump", "USA", 2024);
    cout << "2. dt emplace_back:" << endl;
    nextElections1.emplace_back(p2);
    cout << "2. Done" << endl;

    // std::cout << "\nContents:\n";
    // for (President const& president: elections)
    //     std::cout << president.name << " was elected president of "
    //               << president.country << " in " << president.year << ".\n";
 
    // for (President const& president: reElections)
    //     std::cout << president.name << " was re-elected president of "
    //               << president.country << " in " << president.year << ".\n";



    return 0;
}

