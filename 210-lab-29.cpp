// Include headers for iostream, fstream, map, list, cstdlib (for rand), any others I need
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <array>
#include <cstdlib>

using namespace std;

// Constants: Checkout_Base_Rate, Noreturn_Rate, Donate_Rate, Consumed_Base_Rate, ReplaceConsumables_Rate
const double Checkout_Base_Rate = 15.0, Return_Rate = 15.0, Donate_Rate = 1.0, Consumed_Base_Rate = 5.0, ReplaceConsumables_Rate = 5.0;

// Define a function to simulate one week for one library
    // Parameters: map&, library (key), checkout_rate_modifier, return_rate_modifier, donate_rate_modifier, consumed_rate_modifier
    // use the size of the People list as a factor in these calculations
    // return value is void, it just adds and removes items from this library's lists
void weekly_changes(map<string, array<list<string>,3>>&, string, double, double, double, double);

// I might only need these functions for testing purposes
// ---
// Define a function to display one library's books
    // Parameters: map&, library

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

    // Open an external file to read the book titles into each library - all libraries start with one copy of every book
        // If file does not open, print an error and exit

    // Read data from file and populate map
        // For each library, populate its Consumables and People lists by randomly selecting names from files.
        // opening file error checking like above
        // For demo purposes, libraries will start with different numbers of consumables and people

    // Close the file

    // Begin a time-based simulation of a normal time period of the library activities
    // For 25 time intervals
    // Iterate through each library in the map

        // Wait or pause briefly to simulate the passage of time between intervals

    // Simulate what happens after the rate of new people joining increases
    //    this will affect the checkout rate and rate of using up consumables
    // Simulate what happens when people become more likely to return their books and to donate books

    return 0;
}        
// End of main function

void weekly_changes(map<string, array<list<string>,3>>& m, string lib_name, double checkout_rate_modifier, double return_rate_modifier, double donate_rate_modifier, double consumed_rate_modifier) {
// simulate the changes to books, consumables, and people for the given library in one week
    int r = 0; // will store random numbers
    // 1. books get checked out
    int num_books = Checkout_Base_Rate * checkout_rate_modifier;
    if(num_books > m[lib_name].at(1).size())
        num_books = m[lib_name].at(1).size(); // make sure we don't try to remove more books than we have

    for (int i = 0; !m.empty() && i < num_books; ++i) {
        r = rand() % num_books + 1; // will be index number of book that gets checked out
        
        for(int j = 0; j < r; ++j) // traverse the books list
            m[lib_name].at(1);
    }
    // 2. books get returned or donated (this version will not keep track of which specific books 
    //    were checked out; it will just randomly add books from the file)
    num_books += (Return_Rate * return_rate_modifier) + (Donate_Rate * donate_rate_modifier);
    // 3. consumables get used up
    // 4. more consumables get bought
    // 5. new people get library cards
    // 6. people move away and are removed from the People list
    // Print the changes for this interval
}