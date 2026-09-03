// Authors: Riyashna Prasad and Ayush Kirpal
// Student ID: S11250489 and S11225667
// Date created: 29th August 2026
// Version: 1.9

// About this program:
/*
    USP Pharmacy Stock Management System
    ----------------------------------------
    This program reads medicine records from a text file, allows the user to update stock units,
    and prints a full stock report. Each medicine record consists of an ID, name and the number of units availabe.

    For example, the data file "medicines.txt" may contain:
    3001,Paracetamol,5
    3002,Ibuprofen,0

    The program will read these records into an array of structs, and provide the following functionality:

        1. View a table of all medicines with their availability status
        2. View the total number of units in stock
        3. View the medicine with the highest number of units available
        4. View the percentage of medicines that are out of stock
        5. Update the number of units for a medicine (by Medicine ID)
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>

using namespace std;

// Constants
// ------------------------------------------------------------------------
// Grouping constants like this means every "tunable" value in the program
// has one clear definition, instead of the same number being retyped
// (and possibly mistyped) in several places throughout the code.

const int MAX_MEDICINES = 100; // Maximum records the array can hold
const string DATA_FILE = "medicines.txt";

// Menu option numbers. Using named constants instead of raw numbers means
// the switch statement, the menu text, and the input validation message
// can never accidentally fall out of sync with each other.
const int MENU_SHOW_TABLE = 1;
const int MENU_SHOW_TOTAL = 2;
const int MENU_SHOW_HIGHEST_STOCK = 3;
const int MENU_SHOW_OUT_OF_STOCK_PCT = 4;
const int MENU_UPDATE_UNITS = 5;
const int MENU_EXIT = 6;

// Table column widths (in characters), used with setw() when printing
// the medicine table. Keeping these as named constants means the table
// header, the data rows, and the separator line all stay aligned even
// if a width is changed later.
const int ID_COLUMN_WIDTH = 10;
const int NAME_COLUMN_WIDTH = 22;
const int UNITS_COLUMN_WIDTH = 10;
const int STATUS_COLUMN_WIDTH = 15;
const int TABLE_WIDTH = ID_COLUMN_WIDTH + NAME_COLUMN_WIDTH + UNITS_COLUMN_WIDTH + STATUS_COLUMN_WIDTH;

// Sentinel value returned by search functions when nothing is found.
// Using a named constant instead of a bare "-1" makes the intent obvious
// at every call site (findMedicineById == NOT_FOUND, rather than == -1).
const int NOT_FOUND = -1;

// A medicine is considered out of stock once its units reach this value.
const int OUT_OF_STOCK_UNITS = 0;

// Used to convert a fraction (e.g. 0.25) into a percentage (25.00%).
const double PERCENTAGE_MULTIPLIER = 100.0;

// Size of the buffer cin.ignore() should skip over after bad input,
// large enough to discard an entire mistyped line.
const int INPUT_BUFFER_SIZE = 1000;

// -------------------- Struct Definition --------------------
// Groups the three pieces of data that describe one medicine record.
// Note: availability status is deliberately NOT stored here - it is
// always calculated from "units" via getStatus(), so it can never
// become out of date.
struct Medicine
{
    int id;
    string name;
    int units;
};

// Function Prototypes
int readMedicinesFromFile(Medicine list[], int maxSize, const string &filename);
string getStatus(int units);
int findMedicineById(Medicine list[], int count, int id);
bool updateMedicineUnits(Medicine list[], int count, int id, int newUnits);
void printMedicineTable(Medicine list[], int count);
int getTotalUnits(Medicine list[], int count);
int getHighestStockIndex(Medicine list[], int count);
double getOutOfStockPercentage(Medicine list[], int count);
void printMainMenu();
void pauseScreen();
string intToStr(int value);

// Main Function
int main()
{
    // The array of structs that holds every medicine record for the
    // lifetime of the program, plus how many of its slots are in use.
    Medicine medicines[MAX_MEDICINES];
    int medicineCount = readMedicinesFromFile(medicines, MAX_MEDICINES, DATA_FILE);

    // If nothing could be read, there is nothing useful the program can
    // do, so it reports the problem and exits immediately.
    if (medicineCount == 0)
    {
        cout << "No medicine records could be read from \"" << DATA_FILE << "\"." << endl;
        cout << "Please make sure the file exists in the same folder as the program." << endl;
        return 0;
    }

    cout << "Loaded " << medicineCount << " medicine record(s) from \"" << DATA_FILE << "\"." << endl;

    // Main menu loop: keep showing the menu and acting on the user's
    // choice until they select the "Exit" option.
    int choice = 0;
    do
    {
        printMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid (non-numeric) input gracefully. If the user
        // types letters instead of a number, cin enters a "fail" state
        // and stops reading, so we must clear that state and discard
        // the bad input before asking again.
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(INPUT_BUFFER_SIZE, '\n');
            cout << "\nInvalid input. Please enter a number between "
                 << MENU_SHOW_TABLE << " and " << MENU_EXIT << ".\n"
                 << endl;
            continue;
        }

        switch (choice)
        {
        case MENU_SHOW_TABLE:
            cout << endl;
            printMedicineTable(medicines, medicineCount);
            break;

        case MENU_SHOW_TOTAL:
        {
            int total = getTotalUnits(medicines, medicineCount);
            cout << "\nTotal number of units in stock: " << total << endl;
            break;
        }

        case MENU_SHOW_HIGHEST_STOCK:
        {
            int idx = getHighestStockIndex(medicines, medicineCount);
            if (idx == NOT_FOUND)
            {
                cout << "\nNo records available." << endl;
            }
            else
            {
                cout << "\nMedicine with the highest number of units available:" << endl;
                cout << "  Medicine ID : " << medicines[idx].id << endl;
                cout << "  Name        : " << medicines[idx].name << endl;
                cout << "  Units       : " << medicines[idx].units << endl;
                cout << "  Status      : " << getStatus(medicines[idx].units) << endl;
            }
            break;
        }

        case MENU_SHOW_OUT_OF_STOCK_PCT:
        {
            double pct = getOutOfStockPercentage(medicines, medicineCount);
            cout << "\nPercentage of medicines currently Out of Stock: "
                 << fixed << setprecision(2) << pct << "%" << endl;
            break;
        }

        case MENU_UPDATE_UNITS:
        {
            int id, newUnits;
            cout << "\nEnter the Medicine ID to update: ";
            cin >> id;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(INPUT_BUFFER_SIZE, '\n');
                cout << "Invalid Medicine ID entered." << endl;
                break;
            }

            // Look the medicine up first so we can show its current
            // units and name before asking for the replacement value.
            int idx = findMedicineById(medicines, medicineCount, id);
            if (idx == NOT_FOUND)
            {
                cout << "No medicine found with ID " << id << "." << endl;
                break;
            }

            cout << "Current units for " << medicines[idx].name
                 << " (ID " << id << "): " << medicines[idx].units << endl;
            cout << "Enter the new number of units: ";
            cin >> newUnits;

            // Reject non-numeric input and negative unit counts, since
            // a medicine can never have fewer than zero units in stock.
            if (cin.fail() || newUnits < OUT_OF_STOCK_UNITS)
            {
                cin.clear();
                cin.ignore(INPUT_BUFFER_SIZE, '\n');
                cout << "Invalid number of units entered. Update cancelled." << endl;
                break;
            }

            updateMedicineUnits(medicines, medicineCount, id, newUnits);
            cout << "Stock updated successfully. " << medicines[idx].name
                 << " now has " << medicines[idx].units << " units ("
                 << getStatus(medicines[idx].units) << ")." << endl;
            break;
        }

        case MENU_EXIT:
            cout << "\nExiting program. Goodbye!" << endl;
            break;

        default:
            cout << "\nInvalid choice. Please select an option between "
                 << MENU_SHOW_TABLE << " and " << MENU_EXIT << "." << endl;
            break;
        }

        // Pause after every action except exiting, so the user has a
        // chance to read the output before the menu reprints and
        // scrolls it away.
        if (choice != MENU_EXIT)
        {
            cout << endl;
            pauseScreen();
        }

    } while (choice != MENU_EXIT);

    return 0;
}
// Function Definitions
// ------------------------------------------------------------------------
/*
    Reads medicine records from a comma separated text file into the
    given array of structs.

    Each line in the file is expected to look like:
        ID,Name,Units
    e.g. "3001,Paracetamol,5"

    Lines that are empty or don't contain two commas are skipped, so a
    single malformed line in the file won't crash the program - it is
    simply ignored and reading continues with the next line.

    Returns the number of records successfully read (0 if the file
    could not be opened at all).
*/
int readMedicinesFromFile(Medicine list[], int maxSize, const string &filename)
{
    ifstream inFile(filename.c_str());
    int count = 0;

    if (!inFile.is_open())
    {
        return 0;
    }

    string line;
    while (count < maxSize && getline(inFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        // Find the two commas that separate id, name, and units.
        // find() returns string::npos if the character isn't present,
        // which is how we detect a malformed line below.
        int firstComma = line.find(',');
        int secondComma = line.find(',', firstComma + 1);

        if (firstComma == (int)string::npos || secondComma == (int)string::npos)
        {
            continue; // skip malformed lines
        }

        // substr(start, length) carves out each field using the comma
        // positions found above: everything before the first comma is
        // the ID, everything between the commas is the name, and
        // everything after the second comma is the units.
        string idPart = line.substr(0, firstComma);
        string namePart = line.substr(firstComma + 1, secondComma - firstComma - 1);
        string unitsPart = line.substr(secondComma + 1);

        // atoi() ("ASCII to integer") converts the numeric-looking text
        // fields into actual int values. c_str() is needed because
        // atoi() only understands old-style C strings, not C++ string
        // objects.
        list[count].id = atoi(idPart.c_str());
        list[count].name = namePart;
        list[count].units = atoi(unitsPart.c_str());

        count++;
    }

    inFile.close();
    return count;
}
/*
    Calculates and returns the availability status of a medicine
    based on its number of units. The status is never stored in
    the struct, only ever calculated when needed - this guarantees
    it can never drift out of sync with the actual unit count.
*/
string getStatus(int units)
{
    if (units > OUT_OF_STOCK_UNITS)
    {
        return "Available";
    }
    else
    {
        return "Out of Stock";
    }
}
/*
    Searches the array for a medicine with the given ID using a simple
    linear scan (checking each element in turn).
    Returns the index if found, or NOT_FOUND if no match exists.
*/
int findMedicineById(Medicine list[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (list[i].id == id)
        {
            return i;
        }
    }
    return NOT_FOUND;
}
/*
    Updates the number of units for the medicine with the given ID.
    Internally reuses findMedicineById() rather than searching again,
    so there is only one place in the program that knows how to look
    a medicine up by ID.
    Returns true if the update was successful, false if the ID was not found.
*/
bool updateMedicineUnits(Medicine list[], int count, int id, int newUnits)
{
    int idx = findMedicineById(list, count, id);
    if (idx == NOT_FOUND)
    {
        return false;
    }
    list[idx].units = newUnits;
    return true;
}
/*
    Prints a formatted table of all medicines showing their ID, name,
    units, and calculated availability status.
*/
void printMedicineTable(Medicine list[], int count)
{
    // Column headers, left-aligned and padded to fixed widths so every
    // row lines up neatly underneath them.
    cout << left
         << setw(ID_COLUMN_WIDTH) << "ID"
         << setw(NAME_COLUMN_WIDTH) << "Name"
         << setw(UNITS_COLUMN_WIDTH) << "Units"
         << setw(STATUS_COLUMN_WIDTH) << "Status" << endl;

    // A separator line exactly as wide as the four columns combined.
    cout << string(TABLE_WIDTH, '-') << endl;

    for (int i = 0; i < count; i++)
    {
        string status = getStatus(list[i].units);
        string statusText;

        // Build a more descriptive status string for display: available
        // medicines show their unit count in brackets, while
        // out-of-stock medicines just show the plain label.
        if (status == "Available")
        {
            statusText = "[" + intToStr(list[i].units) + " units] Available";
        }
        else
        {
            statusText = "Out of Stock";
        }

        cout << left
             << setw(ID_COLUMN_WIDTH) << list[i].id
             << setw(NAME_COLUMN_WIDTH) << list[i].name
             << setw(UNITS_COLUMN_WIDTH) << list[i].units
             << statusText << endl;
    }
}
/*
    Returns the sum of units across all medicine records.
*/
int getTotalUnits(Medicine list[], int count)
{
    int total = 0;
    for (int i = 0; i < count; i++)
    {
        total += list[i].units;
    }
    return total;
}
/*
    Returns the index of the medicine with the highest number of units,
    found by keeping track of the best index seen so far while scanning
    through the array once.
    Returns NOT_FOUND if the array is empty.
*/
int getHighestStockIndex(Medicine list[], int count)
{
    if (count == 0)
    {
        return NOT_FOUND;
    }

    int highestIdx = 0;
    for (int i = 1; i < count; i++)
    {
        if (list[i].units > list[highestIdx].units)
        {
            highestIdx = i;
        }
    }
    return highestIdx;
}
/*
    Returns the percentage of medicines that currently have zero units
    (i.e. are Out of Stock). Counts matching records, then converts the
    fraction out of the total into a percentage.
*/
double getOutOfStockPercentage(Medicine list[], int count)
{
    if (count == 0)
    {
        return 0.0;
    }

    int outOfStockCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (list[i].units == OUT_OF_STOCK_UNITS)
        {
            outOfStockCount++;
        }
    }

    return (double(outOfStockCount) / double(count)) * PERCENTAGE_MULTIPLIER;
}
/*
    Displays the main menu options to the user. The option numbers
    printed here match the MENU_* constants used in the switch
    statement in main(), so the two can never fall out of step.
*/
void printMainMenu()
{
    cout << "======================================" << endl;
    cout << "   USP PHARMACY - STOCK MANAGEMENT" << endl;
    cout << "======================================" << endl;
    cout << MENU_SHOW_TABLE << ". Show table of all medicines" << endl;
    cout << MENU_SHOW_TOTAL << ". Show total units in stock" << endl;
    cout << MENU_SHOW_HIGHEST_STOCK << ". Show medicine with highest stock" << endl;
    cout << MENU_SHOW_OUT_OF_STOCK_PCT << ". Show percentage of medicines Out of Stock" << endl;
    cout << MENU_UPDATE_UNITS << ". Update units for a medicine" << endl;
    cout << MENU_EXIT << ". Exit" << endl;
    cout << "======================================" << endl;
}
/*
    Pauses the program until the user presses Enter, so that
    output can be read before the menu is shown again.
*/
void pauseScreen()
{
    cout << "Press Enter to continue...";
    // Discard any leftover newline character still sitting in the input
    // buffer from the previous cin >> read, otherwise cin.get() below
    // would return immediately without actually waiting for the user.
    cin.ignore(INPUT_BUFFER_SIZE, '\n');
    cin.get();
}
/*
    Converts an integer to its string representation using an
    ostringstream (the output-only counterpart to stringstream),
    since older C++ standards don't provide a built-in to_string().
*/
string intToStr(int value)
{
    ostringstream oss;
    oss << value;
    return oss.str();
}