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

        size_t getLength() const;
        const char *getStr() const;
        void setStr(const char *s);
        void display() const; 

        // Overloaded operators for copyng, moving object
        MyString& operator=(const MyString& rhs);       // Copy-ssignment - LHS already exists
        MyString& operator=(MyString&& rhs);            // Move-assignment

        // Unary operators
        MyString operator-() const;

        // Binary operators
        bool operator==(const MyString& rhs);
        MyString operator+(const MyString& rhs);
};

void MyString::display() const
{
    cout << "(" << str << ")" << endl;
}

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

// Using negation unary operator on the MyString to change the case
// of the string
// General form - Type Type::operator-()const 
MyString MyString::operator-() const
{
    cout << __PRETTY_FUNCTION__ << ":<" << this << ">" << endl;
    // Allocate space for the new string
    size_t len = strlen(str);
    char *scopy = new char[len + 1];
    
    // Copy
    strncpy(scopy, str, len + 1);
    
    // Change case 
    for (size_t i=0; scopy[i] != '\0'; ++ i)
    {
        if (isalpha(scopy[i]))
        {
            if (isupper(scopy[i]))
                scopy[i] = tolower(scopy[i]);
            else
                scopy[i] = toupper(scopy[i]);
        }
    }

    MyString s1{scopy};
    delete [] scopy;

    return s1;
}

bool MyString::operator==(const MyString& rhs)
{
    if (strcmp(str, rhs.getStr()) == 0)
        return true;
    else
        return false;
}

MyString MyString::operator+(const MyString& rhs)
{
    size_t len1, len2; 

    len1 = getLength(); 
    len2 = rhs.getLength(); 

    char newStr[len1+len2+1];

    strncpy(newStr, str, len1);
    strncpy(newStr+len1, rhs.getStr(), len2);
    newStr[len1+len2] = '\0';

    return MyString{newStr};
}

int main(int argc, char *argv[])
{
    MyString s1{"Hello"}, s2{"India"};

    MyString s3 = s1 + s2; 

    s1.display(); 
    s2.display();
    s3.display();
    
    (s3+s2).display();

    // Object on the LHS should be MyString for operator+ to be invoked, we can make this work when we
    // define operators as non-menber functions. 
    // MyString res = "Moe" + MyString{"Larry"}; //  error: no match for ‘operator+’ (operand types are ‘const char [4]’ and ‘MyString’)
    MyString res = MyString{"Larry"} + "Moe"; // Works !
    res.display();

    // int arr[5] = {1, 2,3,4,5};
    // const int (&ref)[5] = arr;

    // cout << "arr[2]= " << arr[2] << endl;
    // cout << "ref[2] = " << ref[2] << endl;

    // arr[2] = 10;

    // cout << "arr[2]= " << arr[2] << endl;
    // cout << "ref[2] = " << ref[2] << endl;

    // ref[2] = 11;

    return 0;
}
