/* Single Responsibility Principle */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

/* 
Class of replicating a Journal
and storing your most intimate thoughts. 
*/
struct Journal {
    string title;
    vector<string> entries; 

    Journal(const string &title): title(title)
    {
        cout << "ctor -> Journal::Journal(const string&)" << endl; 
    }

    // Add entry to the journal
    void add_entry(const string& entry)
    {
        static int count=1; 

        entries.push_back(lexical_cast<string>(count++) + ": " + entry); 
    }

    // Persistence, problem with this is that if you want to change
    // the persistance, you have to change persistence in 10 or 20
    // of however many classes are actually using it. 
    // void save(const string& filename)
    // {
    //     ofstream ofs(filename);
    //
    //     for (const auto &e: entries)
    //         ofs << e << endl;
    // }
};

struct PersistenceManager
{
    static void save(const Journal& j, const string& filename)
    {
        ofstream ofs(filename);

        ofs << "=== " << j.title << " ===" << endl;
        for (const auto &e: j.entries)
            ofs << e << endl;
        ofs << "=== END ===" << endl;
    }

};

int main(int argc, char *argv[])
{
    Journal journal{"Dear Diary"};

    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");

    //! journal.save("Diary"); 
    PersistenceManager::save(journal, "file.txt");

    return 0;
}