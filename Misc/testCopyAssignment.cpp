#include <iostream>
#include <cstring>

using namespace std;

class MyString
{
    private:
        char *str; 
    public:
        // ctor
        MyString(); 
        MyString(const char *s); 
        // explicit MyString(const MyString &source); -- if we use explicit then we have to use static_cast<MyString>(..)
        MyString(const MyString &source);
        
        // dtor
        ~MyString();

        //void display() const;
        size_t getLength() const;
        const char *getStr() const;

        // Overloaded operators
        MyString& operator=(const MyString& rhs); // Assignment - LHS already exists
};

size_t MyString::getLength() const
{
    return strlen(str);
}

const char* MyString::getStr() const
{
    cout << __PRETTY_FUNCTION__ << ":<" << this << ">" << endl;
    return str; 
}

// Executes when MyString a; -- there is no construction information here.
MyString::MyString(): str{nullptr}
{
    cout << __PRETTY_FUNCTION__ << ":<" << this << ">" << endl;
    str = new char[1];
    *str = '\0';
}

// Executes when MyString a{"hello"};
MyString::MyString(const char* s)
{
    cout << __PRETTY_FUNCTION__ << ":<" << this << ">" << endl;
    if (s == nullptr)
    {
        str = new char[1];
        str[0] = '\0'; 
    }
    else
    {
        // allocate space for the str to hold the raw string s
        size_t len = strlen(s) + 1;     // len(s) + '\0'
        str = new char[len + 1];

        // copy the raw string s in to str
        strcpy(str, s);
    }
}

MyString::MyString(const MyString &src)
{
    cout << __PRETTY_FUNCTION__ << ":<" << this << ">" << endl;
    size_t len = 0;
    // allocate space for the LHS MyString
    len = src.getLength();      // 0 or non-zero
    str = new char[len + 1];    // len + 1 can be 1 or > 1
    // Copy the RHS string into LHS and done
    strncpy(str, src.getStr(), len + 1);
}

MyString::~MyString()
{
    cout << __PRETTY_FUNCTION__ << ":<" << this << ">" << endl;
    delete [] str; 
}

// Copy-assignment operator has general format :
// Type& Type::operator=(const Type &rhs)
MyString& MyString::operator=(const MyString& rhs)
{
    cout << __PRETTY_FUNCTION__ << ":<" << this << ">" << endl;
    
    // Check self assignment
    if (this == &rhs)                       // p1 = p1 
        return *this;                       // return current object
    
    delete [] str;                          // deallocate whatever is held in str previously
    size_t len = rhs.getLength();
    str = new char[len + 1];                // create memory space for new content 
    strncpy(str, rhs.getStr(), len + 1);    // copy new content into str

    return *this;
}

int main(int argc, char *argv[])
{
    // MyString s1;            // no-args ctor
    // MyString s2{};          // no-args ctor
    
    MyString s3{nullptr};   // MyString::MyString(const char*)
    MyString s4("Larry");   // MyString::MyString(const char*)
    // const char *s = s3.getStr();
    // cout << "s3=(" << s << ")" << endl;

    // s = s4.getStr();
    // cout << "s4=(" << s << ")" << endl;

    MyString s5{"Frank"};
    MyString s6 = s5;       // s6 hasn't been created yet, so this is initialization;
                            // Call is same as MyString s6{s5}; Call will go to MyString::MyString(const MyString&)

    // Assignment occurs when an object is already initialized and you want to
    // assign another object to it. Default is swallow copy, but since we have raw
    // pointers in our MyString class, we have to use deep copy, and so we have to
    // define our own assignment operator.
    s6 = s4;                // s6 is already created, so this is assignment statement
                            // Call is s6.operator=(s4), we are ignoring the return value in this case.
                            // return value MyString& are used for chain assignment and avoiding copies.
    const char *s = s6.getStr();
    cout << "s6=(" << s << ")" << endl;

    s6 = "This is a test string";   // Call will be s6 = MyString("This is a test string"), which will invoke 
                                    // s6.operator=(MyString("This is a test string")) since s6 is  already created. 
    s = s6.getStr();
    cout << "s6=(" << s << ")" << endl;

    MyString s7 = "This is a test string for demo of converting ctor"; // MyString::MyString(const char*)
    s = s7.getStr();
    cout << "s7=(" << s << ")" << endl;


    return 0;
}