/* Open-Closed Principle */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Document; 

// /* Interface for scanning, Faxing the document 
//    some machine that can scan, fax, or whatever
// */
// class IMachine
// {
//     // bunch of pure virual methods
//     virtual void print(Document& doc)   = 0; 
//     virtual void scan(Document& doc)    = 0;
//     virtual void fax(Document& doc)     = 0;
// };

// // Multi function printer which implements IMachine interface 
// struct MultiFunctionPrinter: IMachine
// {
//     void print(Document& doc) override
//     {
//         // Ok
//     }
    
//     void scan(Document& doc) override
//     {
//         // Ok 
//     }

//     void fax(Document& doc) override
//     {
//         // Ok 
//     }
// };

// struct Scanner: IMachine
// {
//     void print(Document& doc) override
//     {
//         // Throw NotImplemented exception, some people might say - just leave them blank
//         // So, if somebody does scanner.print, they don't get anything. Problem is, either way, 
//         // what you are doing is, you are sending the client a wrong message. You are sending
//         // them a message that you have a scanner that can also print, which isn't true. But
//         // you are giving them the API anyways, simply because the interface that's been defined
//         // for handling all this stuff is just to big. And what we really need is to segregate
//         // the interfaces because no client would always require print, scan & fax as well.
//         // 
//     }
    
//     void scan(Document& doc) override
//     {
//         // Ok 
//     }

//     void fax(Document& doc) override
//     {
//         // Throw NotImplemented exception
//     }
// };

/*
-- Segregate the interface -- 
Instead of having single monolithic Document Processor (IMachine) interface that included
all print(), scan() & fax() methods which would force Printer, Scanner and Fax to implement
methods they don't use. Breaking down the interfaces into smaller, more focused ones helps
maintain a cleaner and more maintainable codebase.
*/

class IPrinter
{
    virtual void print(Document& doc) = 0; 
};

class IScanner
{
    virtual void scan(Document& doc) = 0; 
};

class IFax
{
    virtual void fax(Document& doc) = 0; 
};

// Printer, implements print function 
class Printer: IPrinter
{
    void print(Document& doc) override {} 
};

// Scanner, implements scan function
class Scanner: IScanner
{
    void scan(Document& doc) override {} 
};

// Fax, implements fax function
class Fax: IFax
{
    void fax(Document& doc) override {} 
};

// MultiFunctionPrinter, implements all functions 
struct MultiFunctionPrinter: IPrinter, IScanner, IFax
{
    void print(Document& doc) override {}
    void scan(Document& doc) override {}
    void fax(Document& doc) override {}
};

int main(int argc, char *argv[])
{
    return 0;
}
