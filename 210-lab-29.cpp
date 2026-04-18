// Include headers for iostream, fstream, map, list, cstdlib (for rand), any others I need
#include <iostream>
#include <fstream> // for populating the lists
#include <string> // for getline
#include <map> // for storing the libraries and their data
#include <list> // for storing each library's books, consumables, and lists
#include <array> // for storing each library's three lists
#include <cstdlib> // for random numbers
#include <cmath> // for round()

using namespace std;

// Enumeration for the 3 lists
enum ListNum {BOOKS = 0, CONSUMABLES = 1, PEOPLE = 2};

// Constants:
const double Checkout_Base_Rate = 15.0, Return_Rate = 15.0, Donate_Rate = 1.0, Consumed_Base_Rate = 5.0, ReplaceConsumables_Rate = 5.0, People_Base_Rate = 10.0;

// Define functionS to simulate one week for one library
    // Parameters: map&, library (key), checkout_rate_modifier, return_rate_modifier, donate_rate_modifier, consumed_rate_modifier
    // use the size of the People list as a factor in these calculations
    // return value is void, it just adds and removes items from this library's lists
//void weekly_changes(map<string, array<list<string>,3>>&, string, double, double, double, double, double, double);
// this is getting unwieldy; I'm going to split it up into more functions
void change_books(map<string, array<list<string>,3>>&, string, double, double, double);
void change_consumables(map<string, array<list<string>,3>>&, string, double);
void change_people(map<string, array<list<string>,3>>&, string, double, double);

bool read_from_file(map<string, array<list<string>,3>>&, string, string, int);
// I might only need these functions for testing purposes
// ---
// Define a function to display one library's books
    // Parameters: map&, library
void display_books(map<string, array<list<string>,3>>&, string); // I forgot making the map const causes a problem
// Define a function to display one library's consumables
    // Parameters: map&, library

// Define a function to display one library's people
    // Parameters: map&, library
// ---

// Define main function
int main() {
    srand(time(0));
    // Initialize a map to store the information about each of three libraries
    map<string, array<list<string>, 3>> Libraries;
    // the first list is books, the second list is consumables, and the third list is people
    Libraries["Concord"] = {{{},{},{}}};
    Libraries["Walnut Creek"] = {{{},{},{}}};
    Libraries["Pleasant Hill"] = {{{},{},{}}};

    // the starting lists for all three libraries will be the same.
    // I used ChatGPT to generate the lists in the three text files
    if(!read_from_file(Libraries, "Concord", "books.txt", BOOKS))
        return 1;
    if(!read_from_file(Libraries, "Walnut Creek", "books.txt", BOOKS))
        return 1;
    if(!read_from_file(Libraries, "Pleasant Hill", "books.txt", BOOKS))
        return 1;
    if(!read_from_file(Libraries, "Concord", "consumables.txt", CONSUMABLES))
        return 1;
    if(!read_from_file(Libraries, "Walnut Creek", "consumables.txt", CONSUMABLES))
        return 1;
    if(!read_from_file(Libraries, "Pleasant Hill", "consumables.txt", CONSUMABLES))
        return 1;
    if(!read_from_file(Libraries, "Concord", "people.txt", PEOPLE))
        return 1;
    if(!read_from_file(Libraries, "Walnut Creek", "people.txt", PEOPLE))
        return 1;
    if(!read_from_file(Libraries, "Pleasant Hill", "people.txt", PEOPLE))
        return 1;

    
    // Begin a time-based simulation of a normal time period of the library activities
    // For 25 time intervals
    // Iterate through each library in the map
    for (auto pair : Libraries) {
        change_books(Libraries, pair.first, 1.0, 1.0, 1.0);
        change_consumables(Libraries, pair.first, 1.0);
        change_people(Libraries, pair.first, 1.0, 1.0);
    }
    //display_books(Libraries, "Concord"); // testing
        // Wait or pause briefly to simulate the passage of time between intervals

    // Simulate what happens after the rate of new people joining increases
    //    this will affect the checkout rate and rate of using up consumables
    // Simulate what happens when people become more likely to return their books and to donate books

    return 0;
}        
// End of main function

void change_books(map<string, array<list<string>,3>>& m, string lib_name, double checkout_rate_modifier, double return_rate_modifier, double donate_rate_modifier) {
// simulate the changes to books, consumables, and people for the given library in one week
    int rand_index; // will store random numbers
    // 1. books get checked out
    int num_books = static_cast<int>(round(Checkout_Base_Rate * checkout_rate_modifier));
    if(num_books > m[lib_name].at(BOOKS).size())
            num_books = m[lib_name].at(BOOKS).size(); // make sure we don't try to remove more books than we have
    cout << lib_name << ":" << endl;
    for (int i = 0; !m.empty() && i < num_books && num_books > 0; ++i) {
    // each iteration of this loop removes one random book
        rand_index = rand() % m[lib_name].at(BOOKS).size(); // will be index number of book that gets checked out
        list<string>::iterator li = m[lib_name].at(BOOKS).begin();
        for(int j = 0; j < rand_index; ++j)
        // traverse the list to get to the book at index rand_index
            advance(li, 1);
        cout << "\tChecked out book " << *li << endl;
        m[lib_name].at(BOOKS).erase(li); // remove the book at index rand_index
    }
    // 2. books get returned or donated (this version will not keep track of which specific books 
    //    were checked out; it will just randomly add books from the file)
    // books returned:
    num_books = (Return_Rate * return_rate_modifier);
    string book_title = "test R"; // TODO I'll need to store the book names in the program so I can grab random new ones
    for (int i = 0; i < num_books && num_books > 0; ++i) {
    // each iteration of this loop adds one random book
        rand_index = rand() % m[lib_name].at(BOOKS).size(); // will be index number of book that gets checked out
        list<string>::iterator li = m[lib_name].at(BOOKS).begin();
        cout << "\tBook " << book_title << " returned" << endl;
        m[lib_name].at(BOOKS).push_back(book_title); // remove the book at index rand_index
    }
    // books donated:
    num_books = (Donate_Rate * donate_rate_modifier);
    book_title = "test D"; // TODO I'll need to store the book names in the program so I can grab random new ones
    for (int i = 0; i < num_books && num_books > 0; ++i) {
    // each iteration of this loop adds one random book
        list<string>::iterator li = m[lib_name].at(BOOKS).begin();
        cout << "\tNew book " << book_title << " donated" << endl;
        m[lib_name].at(BOOKS).push_back(book_title); // remove the book at index rand_index
    }
}

void change_consumables(map<string, array<list<string>,3>>& m, string lib_name, double consumed_rate_modifier) {
// change the number of consumables (paper towels, pencils, etc.)
    // 3. consumables get used up
    int rand_index;
    int num_consumables = static_cast<int>(round(Consumed_Base_Rate * consumed_rate_modifier));
    if(num_consumables > m[lib_name].at(CONSUMABLES).size())
            num_consumables = m[lib_name].at(CONSUMABLES).size(); // make sure we don't try to remove more books than we have
    for (int i = 0; !m.empty() && i < num_consumables && num_consumables > 0; ++i) {
    // each iteration of this loop removes one random consumable
        rand_index = rand() % m[lib_name].at(CONSUMABLES).size(); // will be index number of book that gets checked out
        list<string>::iterator li = m[lib_name].at(CONSUMABLES).begin();
        for(int j = 0; j < rand_index; ++j)
        // traverse the list to get to the consumable at index rand_index
            advance(li, 1);
        cout << "\tUsed up " << *li << endl;
        m[lib_name].at(CONSUMABLES).erase(li); // remove the consumable at index rand_index
    }
    // 4. more consumables get bought
    num_consumables = ReplaceConsumables_Rate; // I haven't included changing this - they have a limited budget
    for (int i = 0; i < num_consumables && num_consumables > 0; ++i) {
    // each iteration of this loop adds one random consumable
        list<string>::iterator li = m[lib_name].at(CONSUMABLES).begin();
        string consumable_name = "test_c";
        cout << "\tConsumable " << consumable_name << " bought" << endl;
        m[lib_name].at(CONSUMABLES).push_back(consumable_name); // remove the consumable at index rand_index
    }
}

void change_people(map<string, array<list<string>,3>>& m, string lib_name, double joining_modifier, double leaving_modifier) {
// change the number of people who have library cards
    // 5. new people get library cards
    int rand_index = 0;
    int num_people = static_cast<int>(round(People_Base_Rate * joining_modifier));
    string person_name = "test person"; // TODO I'll need to store the book names in the program so I can grab random new ones
    for (int i = 0; i < num_people && num_people > 0; ++i) {
    // each iteration of this loop adds one random book
        rand_index = rand() % m[lib_name].at(PEOPLE).size(); // will be index number of book that gets checked out
        list<string>::iterator li = m[lib_name].at(PEOPLE).begin();
        cout << "\t" << person_name << " got a library card" << endl;
        m[lib_name].at(PEOPLE).push_back(person_name); // remove the book at index rand_index
    }
    // 6. people move away and are removed from the People list
    num_people = static_cast<int>(round(People_Base_Rate * leaving_modifier));
    if(num_people > m[lib_name].at(PEOPLE).size())
            num_people = m[lib_name].at(PEOPLE).size(); // make sure we don't try to remove more people than we have
    for (int i = 0; !m.empty() && i < num_people && num_people > 0; ++i) {
    // each iteration of this loop removes one random person
        rand_index = rand() % m[lib_name].at(PEOPLE).size(); // will be index number of book that gets checked out
        list<string>::iterator li = m[lib_name].at(PEOPLE).begin();
        for(int j = 0; j < rand_index; ++j)
        // traverse the list to get to the person at index rand_index
            advance(li, 1);
        cout << "\t" << *li << " moved away" << endl;
        m[lib_name].at(PEOPLE).erase(li); // remove the consumable at index rand_index
    }
}

bool read_from_file(map<string, array<list<string>,3>>& m, string lib_name, string filename, int list_index) {
// reads from the given file into the list (0 books, 1 consumables, 2 people) for the given Library
    ifstream inFile;
    string in_string;
    // Read data from files and populate map
    // array<list<string>, 3> test; // TESTING
    inFile.open(filename);
    // check for file error
    if(!inFile.is_open()) {
        cout << "Error: file \"" << filename << "\" not found.";
        return false;
    }
    while (!inFile.eof()){ 
        getline(inFile, in_string);
        m[lib_name].at(list_index).push_back(in_string); 
    }
    inFile.close();
    return true;
}

void display_books(map<string, array<list<string>,3>>& m, string lib_name) {
// display all the books in the given library
    int i = 1;
    for (string book : m[lib_name].at(0)) {
        cout << book;
        if (i != m[lib_name].at(0).size()) // if it's not the last book
            cout << ", ";
        if(i % 8 == 0) // show 8 book names per line
            cout << endl;
        ++i;
    }
    cout << "\nTotal number of books: " << m[lib_name].at(0).size() << endl;
}