#include <iostream>
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
    Person new_person;
    new_person.id = id_counter++;
    new_person.name = name;
    return new_person;
  }

private:
  static int id_counter;
};

// Initialize the static ID counter to 0
int PersonFactory::id_counter = 0;

int main() {
    PersonFactory factory;

    Person person1 = factory.create_person("Alice");
    Person person2 = factory.create_person("Bob");

    cout << "Person 1 - ID: " << person1.id << ", Name: " << person1.name << endl;
    cout << "Person 2 - ID: " << person2.id << ", Name: " << person2.name << endl;

    return 0;
}