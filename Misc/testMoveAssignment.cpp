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
        void setStr(const char *s);

        // Overloaded operators
        MyString& operator=(const MyString& rhs);       // Copy-ssignment - LHS already exists
        MyString& operator=(MyString&& rhs);            // Move-assignment
};

size_t MyString::getLength() const
{
    return strlen(str);
}

void MyString::setStr(const char *s)
{
    cout << __PRETTY_FUNCTION__ << ":<" << this << ">" << endl;
    str = const_cast<char *>(s);
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
        size_t len = strlen(s);
        str = new char[len + 1];
        strncpy(str, s, len + 1);
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
    str = nullptr;
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

// Move-assignment operator has general format :
// Type& Type::operator=(Type &&rhs)
MyString& MyString::operator=(MyString&& rhs)
{
    cout << __PRETTY_FUNCTION__ << ":<" << this << ">" << endl;
    
    // Check self assignment
    if (this == &rhs)           // p1 = p1 
        return *this;           // return current object
    
    delete [] str;              // deallocate whatever is held in str previously
    str = const_cast<char *>(rhs.getStr()); // str now points to whatever was pointed to by rhs
    rhs.setStr(nullptr);        // null out the RHS object
    
    return *this;
}

int main(int argc, char *argv[])
{
    MyString a{"Hello"};    // Overloaded ctor MyString::MyString(const char*)
    
    a = MyString{"Hola"};   // Overloaded ctor MyString::MyString(const char*)
                            // and then Move assignment
    
    a = "Bonjour";          // Overloaded ctor MyString::MyString(const char*)
                            // and then move assignment


    return 0;
}