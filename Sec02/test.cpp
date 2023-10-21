/* Single Responsibility Principle */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class MyClass {
    public:
        // MyClass(int value){
        //     cout << __PRETTY_FUNCTION__ << endl;
        // }
        explicit operator int() const {
            cout << __PRETTY_FUNCTION__ << endl;
            return 42;
        }
};

int main(int argc, char *argv[])
{
    MyClass obj;

    int x = static_cast<int>(obj);

    cout << "x=" << x << endl;

    return 0;
}