// Authors: Ayush Kirpal and nameOfStudent2
// Student ID: S11250489 and studentID2
// Date created: 29th August 2026
// Version: 1.5

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

    1. Update the number of units available for a specific medicine by ID.
    2. Print a full stock report, including:
        - A table of all medicines with their ID, name, and status (available or out
        - The total number of units in stock across all medicines.
        - The medicine with the highest number of units available (full details).
        - The percentage of medicines that are out of stock.
    The program uses C++17 features and follows best practices for file I/O, string manipulation, and user interaction.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int MAX_MEDICINES = 100; // maximum number of medicines the array can hold
const string DATA_FILE = "medicines.txt";

// Menu options
const int MENU_UPDATE_UNITS = 1;
const int MENU_PRINT_REPORT = 2;
const int MENU_EXIT = 3;

// Table formatting
const int ID_COLUMN_WIDTH = 10;
const int NAME_COLUMN_WIDTH = 25;
const int STATUS_COLUMN_WIDTH = 25;
const int TABLE_WIDTH = ID_COLUMN_WIDTH + NAME_COLUMN_WIDTH + STATUS_COLUMN_WIDTH;

// Stock rules
const int OUT_OF_STOCK_UNITS = 0;
const double PERCENTAGE_MULTIPLIER = 100.0;

// Input handling
const int INPUT_BUFFER_SIZE = 1000;

// Struct definition
struct Medicine
{
    int id;
    string name;
    int unitsAvailable;
};

// Function prototypes

int readMedicinesFromFile(const string &filename, Medicine medicines[], int maxSize);
string getStatus(int units);
void updateMedicineUnits(Medicine medicines[], int count);
void printMedicineTable(const Medicine medicines[], int count);
int calculateTotalUnits(const Medicine medicines[], int count);
int findMedicineWithHighestUnits(const Medicine medicines[], int count);
double calculateOutOfStockPercentage(const Medicine medicines[], int count);
void printFullReport(const Medicine medicines[], int count);
void displayMenu();

// main
int main()
{
    Medicine medicines[MAX_MEDICINES];
    int medicineCount = 0;

    medicineCount = readMedicinesFromFile(DATA_FILE, medicines, MAX_MEDICINES);

    if (medicineCount == 0)
    {
        cout << "No medicine records could be read from \"" << DATA_FILE
             << "\". Please check the file and try again." << endl;
        return 1;
    }

    cout << medicineCount << " medicine record(s) loaded successfully." << endl;

    int choice = 0;

    do
    {
        displayMenu();
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(INPUT_BUFFER_SIZE, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
        case MENU_UPDATE_UNITS:
            updateMedicineUnits(medicines, medicineCount);
            break;
        case MENU_PRINT_REPORT:
            printFullReport(medicines, medicineCount);
            break;
        case MENU_EXIT:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please select " << MENU_UPDATE_UNITS
                 << ", " << MENU_PRINT_REPORT << " or " << MENU_EXIT << "." << endl;
        }

    } while (choice != MENU_EXIT);

    return 0;
}

// Displays the main menu
void displayMenu()
{
    cout << "\n===== USP Pharmacy Stock Management =====" << endl;
    cout << "1. Update units for a medicine" << endl;
    cout << "2. Print stock report" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

// Reads medicine records from the given file into the array.
// Each line in the file is expected in the format: ID,Name,Units
// Returns the number of records successfully read.
int readMedicinesFromFile(const string &filename, Medicine medicines[], int maxSize)
{
    ifstream inFile(filename.c_str());
    int count = 0;

    if (!inFile)
    {
        cout << "Error: could not open file \"" << filename << "\"." << endl;
        return 0;
    }

    string line;

    while (getline(inFile, line) && count < maxSize)
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string idPart, namePart, unitsPart;

        if (getline(ss, idPart, ',') &&
            getline(ss, namePart, ',') &&
            getline(ss, unitsPart, ','))
        {
            medicines[count].id = atoi(idPart.c_str());
            medicines[count].name = namePart;
            medicines[count].unitsAvailable = atoi(unitsPart.c_str());
            count++;
        }
    }

    inFile.close();
    return count;
}

// Calculates (does NOT store) the status of a medicine based on units.
string getStatus(int units)
{
    if (units > OUT_OF_STOCK_UNITS)
    {
        stringstream ss;
        ss << units << " units Available";
        return ss.str();
    }
    else
    {
        return "Out of Stock";
    }
}

// Allows the user to update the units of a medicine identified by ID.
void updateMedicineUnits(Medicine medicines[], int count)
{
    int searchId;
    bool found = false;

    cout << "Enter the Medicine ID to update: ";
    cin >> searchId;

    for (int i = 0; i < count; i++)
    {
        if (medicines[i].id == searchId)
        {
            int newUnits;
            cout << "Current units for " << medicines[i].name
                 << ": " << medicines[i].unitsAvailable << endl;
            cout << "Enter new units available: ";
            cin >> newUnits;

            if (newUnits < 0)
            {
                cout << "Units cannot be negative. Update cancelled." << endl;
            }
            else
            {
                medicines[i].unitsAvailable = newUnits;
                cout << "Stock updated successfully for " << medicines[i].name << "." << endl;
            }

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "No medicine found with ID " << searchId << "." << endl;
    }
}

// Prints a table of all medicines: ID, Name, Status
void printMedicineTable(const Medicine medicines[], int count)
{
    string separator(TABLE_WIDTH, '-');

    cout << "\n"
         << separator << endl;
    cout << left << setw(ID_COLUMN_WIDTH) << "ID"
         << setw(NAME_COLUMN_WIDTH) << "Name"
         << setw(STATUS_COLUMN_WIDTH) << "Status" << endl;
    cout << separator << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left << setw(ID_COLUMN_WIDTH) << medicines[i].id
             << setw(NAME_COLUMN_WIDTH) << medicines[i].name
             << setw(STATUS_COLUMN_WIDTH) << getStatus(medicines[i].unitsAvailable) << endl;
    }

    cout << separator << endl;
}

// Returns the sum of units available across all medicines.
int calculateTotalUnits(const Medicine medicines[], int count)
{
    int total = 0;

    for (int i = 0; i < count; i++)
    {
        total += medicines[i].unitsAvailable;
    }

    return total;
}

// Returns the array index of the medicine with the highest units.
int findMedicineWithHighestUnits(const Medicine medicines[], int count)
{
    int maxIndex = 0;

    for (int i = 1; i < count; i++)
    {
        if (medicines[i].unitsAvailable > medicines[maxIndex].unitsAvailable)
        {
            maxIndex = i;
        }
    }

    return maxIndex;
}

// Returns the percentage of medicines that are out of stock.
double calculateOutOfStockPercentage(const Medicine medicines[], int count)
{
    int outOfStockCount = 0;

    for (int i = 0; i < count; i++)
    {
        if (medicines[i].unitsAvailable == OUT_OF_STOCK_UNITS)
        {
            outOfStockCount++;
        }
    }

    if (count == 0)
    {
        return 0.0;
    }

    return (static_cast<double>(outOfStockCount) / count) * PERCENTAGE_MULTIPLIER;
}

// Prints the complete stock report requested in the assignment:
// - table of all medicines
// - total units in stock
// - medicine with highest units (full details)
// - percentage of medicines out of stock
void printFullReport(const Medicine medicines[], int count)
{
    printMedicineTable(medicines, count);

    int totalUnits = calculateTotalUnits(medicines, count);
    cout << "\nTotal units in stock: " << totalUnits << endl;

    int topIndex = findMedicineWithHighestUnits(medicines, count);
    cout << "\nMedicine with highest units available:" << endl;
    cout << "  ID     : " << medicines[topIndex].id << endl;
    cout << "  Name   : " << medicines[topIndex].name << endl;
    cout << "  Status : " << getStatus(medicines[topIndex].unitsAvailable) << endl;

    double outOfStockPercent = calculateOutOfStockPercentage(medicines, count);
    cout << "\nPercentage of medicines out of stock: "
         << fixed << setprecision(2) << outOfStockPercent << "%" << endl;
}