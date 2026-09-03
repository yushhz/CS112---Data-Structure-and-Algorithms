/*
 * USP Pharmacy - Medicine Stock Management System
 * ------------------------------------------------
 * Reads medicine records (ID, Name, Units) from a text file into an
 * array of structs, allows the user to update stock units, and prints
 * a full stock report.
 *
 * Data file format (one medicine per line):
 *     ID,Name,Units
 * e.g.
 *     3001,Paracetamol,5
 *
 * Written for Dev C++ 4.9.9 (plain C++ / C++98 style - no STL containers
 * other than string, no C++11 features).
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

// Struct definition
struct Medicine
{
    int id;
    string name;
    int unitsAvailable;
};

// ---------------------------------------------------------------------
// Function prototypes
// ---------------------------------------------------------------------
int readMedicinesFromFile(const string &filename, Medicine medicines[], int maxSize);
string getStatus(int units);
void updateMedicineUnits(Medicine medicines[], int count);
void printMedicineTable(const Medicine medicines[], int count);
int calculateTotalUnits(const Medicine medicines[], int count);
int findMedicineWithHighestUnits(const Medicine medicines[], int count);
double calculateOutOfStockPercentage(const Medicine medicines[], int count);
void printFullReport(const Medicine medicines[], int count);
void displayMenu();

// ---------------------------------------------------------------------
// main
// ---------------------------------------------------------------------
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
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            updateMedicineUnits(medicines, medicineCount);
            break;
        case 2:
            printFullReport(medicines, medicineCount);
            break;
        case 3:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please select 1, 2 or 3." << endl;
        }

    } while (choice != 3);

    return 0;
}

// ---------------------------------------------------------------------
// Displays the main menu
// ---------------------------------------------------------------------
void displayMenu()
{
    cout << "\n===== USP Pharmacy Stock Management =====" << endl;
    cout << "1. Update units for a medicine" << endl;
    cout << "2. Print stock report" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

// ---------------------------------------------------------------------
// Reads medicine records from the given file into the array.
// Each line in the file is expected in the format: ID,Name,Units
// Returns the number of records successfully read.
// ---------------------------------------------------------------------
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

// ---------------------------------------------------------------------
// Calculates (does NOT store) the status of a medicine based on units.
// ---------------------------------------------------------------------
string getStatus(int units)
{
    if (units > 0)
    {
        stringstream ss;
        ss << "[" << units << " units] Available";
        return ss.str();
    }
    else
    {
        return "Out of Stock";
    }
}

// ---------------------------------------------------------------------
// Allows the user to update the units of a medicine identified by ID.
// ---------------------------------------------------------------------
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

// ---------------------------------------------------------------------
// Prints a table of all medicines: ID, Name, Status
// ---------------------------------------------------------------------
void printMedicineTable(const Medicine medicines[], int count)
{
    cout << "\n---------------------------------------------------------------" << endl;
    cout << left << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(25) << "Status" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left << setw(10) << medicines[i].id
             << setw(25) << medicines[i].name
             << setw(25) << getStatus(medicines[i].unitsAvailable) << endl;
    }

    cout << "---------------------------------------------------------------" << endl;
}

// ---------------------------------------------------------------------
// Returns the sum of units available across all medicines.
// ---------------------------------------------------------------------
int calculateTotalUnits(const Medicine medicines[], int count)
{
    int total = 0;

    for (int i = 0; i < count; i++)
    {
        total += medicines[i].unitsAvailable;
    }

    return total;
}

// ---------------------------------------------------------------------
// Returns the array index of the medicine with the highest units.
// ---------------------------------------------------------------------
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

// ---------------------------------------------------------------------
// Returns the percentage of medicines that are out of stock.
// ---------------------------------------------------------------------
double calculateOutOfStockPercentage(const Medicine medicines[], int count)
{
    int outOfStockCount = 0;

    for (int i = 0; i < count; i++)
    {
        if (medicines[i].unitsAvailable == 0)
        {
            outOfStockCount++;
        }
    }

    if (count == 0)
    {
        return 0.0;
    }

    return (static_cast<double>(outOfStockCount) / count) * 100.0;
}

// ---------------------------------------------------------------------
// Prints the complete stock report requested in the assignment:
// - table of all medicines
// - total units in stock
// - medicine with highest units (full details)
// - percentage of medicines out of stock
// ---------------------------------------------------------------------
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
