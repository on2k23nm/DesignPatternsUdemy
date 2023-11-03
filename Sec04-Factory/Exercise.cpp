#include <iostream>
#include <string>
using namespace std;

/*
You are given a class called Person . The person has two fields: id , and name .

Please implement a non-static PersonFactory that has a create_person()  method that takes a person's name.

The id  of the person should be set as a 0-based index of the object created. So, the first person the factory makes should have id=0, second id=1 and so on.

#include <string>
using namespace std;

struct Person
{
  int id;
  string name;
};

class PersonFactory
{
public:
  Person create_person(const string& name)
  {
    // todo
  }
};

*/

struct Person
{
    int id;
    string name;
};

class PersonFactory
{
public:
    PersonFactory() : id_counter(0) {}

    Person create_person(const string& name)
    {
        Person new_person;
        new_person.id = id_counter++;
        new_person.name = name;
        return new_person;
    }

private:
    int id_counter;
};

int main() {
    PersonFactory factory;

    Person person1 = factory.create_person("Alice");
    Person person2 = factory.create_person("Bob");

    cout << "Person 1 - ID: " << person1.id << ", Name: " << person1.name << endl;
    cout << "Person 2 - ID: " << person2.id << ", Name: " << person2.name << endl;

    return 0;
}