/*
    CS112: Data Structures & Algorithms - Assignment 1 (Semester II, 2026)
    USP Pharmacy Stock Management System

    Description:
    This program reads medicine stock records from a text file into an
    array of structs, and allows the user to:
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

// -------------------- Constants --------------------
const int MAX_MEDICINES = 100;      // Maximum records the array can hold
const string DATA_FILE   = "medicines.txt";

// -------------------- Struct Definition --------------------
struct Medicine
{
    int    id;
    string name;
    int    units;
};

// -------------------- Function Prototypes --------------------
int    readMedicinesFromFile(Medicine list[], int maxSize, const string &filename);
string getStatus(int units);
int    findMedicineById(Medicine list[], int count, int id);
bool   updateMedicineUnits(Medicine list[], int count, int id, int newUnits);
void   printMedicineTable(Medicine list[], int count);
int    getTotalUnits(Medicine list[], int count);
int    getHighestStockIndex(Medicine list[], int count);
double getOutOfStockPercentage(Medicine list[], int count);
void   printMainMenu();
void   pauseScreen();
string intToStr(int value);

// -------------------- main() --------------------
int main()
{
    Medicine medicines[MAX_MEDICINES];
    int medicineCount = readMedicinesFromFile(medicines, MAX_MEDICINES, DATA_FILE);

    if (medicineCount == 0)
    {
        cout << "No medicine records could be read from \"" << DATA_FILE << "\"." << endl;
        cout << "Please make sure the file exists in the same folder as the program." << endl;
        return 0;
    }

    cout << "Loaded " << medicineCount << " medicine record(s) from \"" << DATA_FILE << "\"." << endl;

    int choice = 0;
    do
    {
        printMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid (non-numeric) input gracefully
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input. Please enter a number between 1 and 6.\n" << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
                cout << endl;
                printMedicineTable(medicines, medicineCount);
                break;

            case 2:
            {
                int total = getTotalUnits(medicines, medicineCount);
                cout << "\nTotal number of units in stock: " << total << endl;
                break;
            }

            case 3:
            {
                int idx = getHighestStockIndex(medicines, medicineCount);
                if (idx == -1)
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

            case 4:
            {
                double pct = getOutOfStockPercentage(medicines, medicineCount);
                cout << "\nPercentage of medicines currently Out of Stock: "
                     << fixed << setprecision(2) << pct << "%" << endl;
                break;
            }

            case 5:
            {
                int id, newUnits;
                cout << "\nEnter the Medicine ID to update: ";
                cin >> id;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid Medicine ID entered." << endl;
                    break;
                }

                int idx = findMedicineById(medicines, medicineCount, id);
                if (idx == -1)
                {
                    cout << "No medicine found with ID " << id << "." << endl;
                    break;
                }

                cout << "Current units for " << medicines[idx].name
                     << " (ID " << id << "): " << medicines[idx].units << endl;
                cout << "Enter the new number of units: ";
                cin >> newUnits;

                if (cin.fail() || newUnits < 0)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid number of units entered. Update cancelled." << endl;
                    break;
                }

                updateMedicineUnits(medicines, medicineCount, id, newUnits);
                cout << "Stock updated successfully. " << medicines[idx].name
                     << " now has " << medicines[idx].units << " units ("
                     << getStatus(medicines[idx].units) << ")." << endl;
                break;
            }

            case 6:
                cout << "\nExiting program. Goodbye!" << endl;
                break;

            default:
                cout << "\nInvalid choice. Please select an option between 1 and 6." << endl;
                break;
        }

        if (choice != 6)
        {
            cout << endl;
            pauseScreen();
        }

    } while (choice != 6);

    return 0;
}
// -------------------- Function Definitions --------------------
/*
    Reads medicine records from a comma separated text file into the
    given array of structs. 
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

        // Find the two commas that separate id, name, and units
        int firstComma = line.find(',');
        int secondComma = line.find(',', firstComma + 1);

        if (firstComma == (int)string::npos || secondComma == (int)string::npos)
        {
            continue; // skip malformed lines
        }

        string idPart    = line.substr(0, firstComma);
        string namePart   = line.substr(firstComma + 1, secondComma - firstComma - 1);
        string unitsPart = line.substr(secondComma + 1);

        list[count].id    = atoi(idPart.c_str());
        list[count].name  = namePart;
        list[count].units = atoi(unitsPart.c_str());

        count++;
    }

    inFile.close();
    return count;
}
/*
    Calculates and returns the availability status of a medicine
    based on its number of units. The status is never stored in
    the struct, only ever calculated when needed.
*/
string getStatus(int units)
{
    if (units > 0)
    {
        return "Available";
    }
    else
    {
        return "Out of Stock";
    }
}
/*
    Searches the array for a medicine with the given ID.
    Returns the index if found, or -1 if not found.
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
    return -1;
}
/*
    Updates the number of units for the medicine with the given ID.
    Returns true if the update was successful, false if the ID was not found.
*/
bool updateMedicineUnits(Medicine list[], int count, int id, int newUnits)
{
    int idx = findMedicineById(list, count, id);
    if (idx == -1)
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
    cout << left
         << setw(10) << "ID"
         << setw(22) << "Name"
         << setw(10) << "Units"
         << setw(15) << "Status" << endl;
    cout << string(57, '-') << endl;

    for (int i = 0; i < count; i++)
    {
        string status = getStatus(list[i].units);
        string statusText;

        if (status == "Available")
        {
            statusText = "[" + intToStr(list[i].units) + " units] Available";
        }
        else
        {
            statusText = "Out of Stock";
        }

        cout << left
             << setw(10) << list[i].id
             << setw(22) << list[i].name
             << setw(10) << list[i].units
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
    Returns the index of the medicine with the highest number of units.
    Returns -1 if the array is empty.
*/
int getHighestStockIndex(Medicine list[], int count)
{
    if (count == 0)
    {
        return -1;
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
    Returns the percentage of medicines that currently have 0 units
    (i.e. are Out of Stock).
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
        if (list[i].units == 0)
        {
            outOfStockCount++;
        }
    }

    return (double(outOfStockCount) / double(count)) * 100.0;
}
/*
    Displays the main menu options to the user.
*/
void printMainMenu()
{
    cout << "======================================" << endl;
    cout << "   USP PHARMACY - STOCK MANAGEMENT" << endl;
    cout << "======================================" << endl;
    cout << "1. Show table of all medicines" << endl;
    cout << "2. Show total units in stock" << endl;
    cout << "3. Show medicine with highest stock" << endl;
    cout << "4. Show percentage of medicines Out of Stock" << endl;
    cout << "5. Update units for a medicine" << endl;
    cout << "6. Exit" << endl;
    cout << "======================================" << endl;
}/*
    Pauses the program until the user presses Enter, so that
    output can be read before the menu is shown again.
*/
void pauseScreen()
{
    cout << "Press Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}
/*
    Converts an integer to its string representation.
*/
string intToStr(int value)
{
    ostringstream oss;
    oss << value;
    return oss.str();
}
