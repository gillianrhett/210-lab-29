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

// Constants:
const double Checkout_Base_Rate = 15.0, Return_Rate = 15.0, Donate_Rate = 1.0, Consumed_Base_Rate = 5.0, ReplaceConsumables_Rate = 5.0, People_Base_rate = 10.0;

// Define a function to simulate one week for one library
    // Parameters: map&, library (key), checkout_rate_modifier, return_rate_modifier, donate_rate_modifier, consumed_rate_modifier
    // use the size of the People list as a factor in these calculations
    // return value is void, it just adds and removes items from this library's lists
//void weekly_changes(map<string, array<list<string>,3>>&, string, double, double, double, double, double, double);
// this is getting unwieldy; I'm going to split it up into more functions
void change_books(map<string, array<list<string>,3>>&, string, double, double);

// I might only need these functions for testing purposes
// ---
// Define a function to display one library's books
    // Parameters: map&, library
void display_books(const map<string, array<list<string>,3>>&, string);
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
    ifstream inFile;
    array<string, 3> files = {"books.txt", "consumables.txt", "people.txt"};
    int list_num = 0;
    string in_string;
    // Read data from files and populate map
    array<list<string>, 3> test;
    for (string filename : files) {
        inFile.open(filename);
        // check for file error
        if(!inFile.is_open()) {
            cout << "Error: file \"" << filename << "\" not found.";
            return 1;
        }
        // go through the file and add all the items to each library's list for that type of item
        for (auto pair : Libraries) {
            inFile.seekg(0); // go to the beginning for the next library
            while (!inFile.eof()){ 
                getline(inFile, in_string);
                //cout << in_string << endl; // testing - this works; it's getting the strings from the file
                pair.second.at(list_num).push_back(in_string); // this isn't working
            }
        }
        for (string book : Libraries["Concord"].at(0)) // testing
            cout << book << endl;
        /* TESTING
        for (auto pair : Libraries) {
            inFile.seekg(0); // go to the beginning for the next library
            while (!inFile.eof()){ 
                getline(inFile, in_string);
                test.at(list_num).push_back(in_string);
            }
        }
        cout << "size of list: " << test.at(list_num).size() << " last item in test: " << test.at(list_num).back() << endl;
         END TESTING - this works
         */

        inFile.close(); // close the file
        ++list_num;
    }
    //Libraries["Concord"].at(0).push_back("test"); // testing - this works

    // Begin a time-based simulation of a normal time period of the library activities
    // For 25 time intervals
    // Iterate through each library in the map
    //weekly_changes(Libraries, "Concord", 1, 1, 1, 1); // testing
    display_books(Libraries, "Concord"); // testing
        // Wait or pause briefly to simulate the passage of time between intervals

    // Simulate what happens after the rate of new people joining increases
    //    this will affect the checkout rate and rate of using up consumables
    // Simulate what happens when people become more likely to return their books and to donate books

    return 0;
}        
// End of main function

void change_books(map<string, array<list<string>,3>>& m, string lib_name, double checkout_rate_modifier, double return_rate_modifier) {
// simulate the changes to books, consumables, and people for the given library in one week
    int rand_index; // will store random numbers
    // 1. books get checked out
    int num_books = static_cast<int>(round(Checkout_Base_Rate * checkout_rate_modifier));
    if(num_books > m[lib_name].at(0).size())
            num_books = m[lib_name].at(0).size(); // make sure we don't try to remove more books than we have
    for (int i = 0; !m.empty() && i < num_books && num_books > 0; ++i) {
    // each iteration of this loop removes one random book
        cout << num_books << endl; // testing
            rand_index = rand() % num_books; // will be index number of book that gets checked out
        cout << rand_index << endl; // testing
        list<string>::iterator li = m[lib_name].at(0).begin();
        for(int j = 0; j < rand_index; ++j)
        // traverse the list to get to the book at index rand_index
            advance(li, 1);
        cout << "Checked out book " << *li << endl;
        m[lib_name].at(0).erase(li); // remove the book at index rand_index
    }
}

/* for other change functions:
    params: double donate_rate_modifier, double consumed_rate_modifier, double joining_modifier, double leaving_modifier) {
    // 2. books get returned or donated (this version will not keep track of which specific books 
    //    were checked out; it will just randomly add books from the file)
    num_books += (Return_Rate * return_rate_modifier) + (Donate_Rate * donate_rate_modifier);
    // 3. consumables get used up
    int num_consumables = static_cast<int>(round(Consumed_Base_Rate * consumed_rate_modifier));
    // 4. more consumables get bought
    num_consumables = ReplaceConsumables_Rate; // I haven't included changing this - they have a limited budget
    // 5. new people get library cards
    int num_people = static_cast<int>(round(Consumed_Base_Rate * consumed_rate_modifier))
    // 6. people move away and are removed from the People list
    // Print the changes for this interval
 */

void display_books(const map<string, array<list<string>,3>>& m, string lib_name) {
// display all the books in the given library
    int i = 1;
    for (auto pair : m) {
        for (auto book : pair.second.at(0))
            cout << book << ", ";
        if(i % 10 == 0) // show 10 book names per line
            cout << endl;
        ++i;
    }
}