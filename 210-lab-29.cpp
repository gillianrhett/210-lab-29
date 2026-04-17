// Include headers for iostream, fstream, map, list, cstdlib (for rand), any others I need
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <cstdlib>

using namespace std;

// Constants: Checkout_Base_Rate, Noreturn_Rate, Donate_Rate, Consumed_Base_Rate, ReplaceConsumables_Rate
const double Checkout_Base_Rate = 15.0, Noreturn_Rate = 1.0, Donate_Rate = 1.0, Consumed_Base_Rate = 5.0, ReplaceConsumables_Rate = 5.0;

// Define a function to simulate one week for one library
    // Parameters: map&, library (key), checkout_rate_modifier, p_noreturn_modifier, p_donate_modifier, consumed_rate_modifier
    // use the size of the People list as a factor in these calculations
    // return value is void, it just adds and removes items from this library's lists

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
    // Initialize a map to store the information about each of three libraries

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
	    // 1. books get checked out
        // 2. books get returned or donated (this version will not keep track of which specific books 
        //    were checked out; it will just randomly add books from the file)
        // 3. consumables get used up
        // 4. more consumables get bought
        // 5. new people get library cards
        // 6. people move away and are removed from the People list
        // Print the changes for this interval
        // Wait or pause briefly to simulate the passage of time between intervals

    // Simulate what happens after the rate of new people joining increases
    //    this will affect the checkout rate and rate of using up consumables
    // Simulate what happens when people become more likely to return their books and to donate books

    return 0;
}        
// End of main function