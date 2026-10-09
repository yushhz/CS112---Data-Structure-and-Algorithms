// Authors: Riyashna Prasad and Ayush Kirpal
// Student ID: S11225667 and S11250489
// Date created: 7th October 2026
// Version: 1.10

// About this program:
/*
    USP Pharmacy Stock Management System
    ----------------------------------------
    This program reads medicine records from a text file, allows the user to update stock units,
    and prints a full stock report. Each medicine record consists of an ID, name and the number of units available.

    For example, the data file "medicines.txt" may contain:
    3001,Paracetamol,5
    3002,Ibuprofen,0

    The program will read these records into a linked list of Medicine objects (using the generic
    List and Node classes), and provide the following functionality:

        1. View a table of all medicines with their availability status
        2. View the total number of units in stock
        3. View the medicine with the highest number of units available
        4. View the percentage of medicines that are out of stock
        5. Update the number of units for a medicine (by Medicine ID)

    Files in this program:
        main.cpp   - driver file: reads the data file, shows the menu and runs the chosen option
        Medicine.h - Medicine class (ID, name, units; status is calculated, not stored)
        List.h     - generic LinkedList class that manages the nodes
        Node.h     - generic Node class that holds one item and a pointer to the next node
*/

// Libraries and header files used for input/output, file handling
// string operations, formatting, and the Medicine linked list.
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cstddef>

#include "List.h"
#include "Medicine.h"

using namespace std;

// File containing the medicine records
const string DATA_FILE = "medicines.txt";

// Constants for menu options, table formatting, and input handling
const int MENU_SHOW_TABLE = 1;
const int MENU_SHOW_TOTAL = 2;
const int MENU_SHOW_HIGHEST_STOCK = 3;
const int MENU_SHOW_OUT_OF_STOCK_PCT = 4;
const int MENU_UPDATE_UNITS = 5;
const int MENU_EXIT = 6;

const int ID_COLUMN_WIDTH = 10;
const int NAME_COLUMN_WIDTH = 22;
const int STATUS_COLUMN_WIDTH = 20;
const int TABLE_WIDTH = ID_COLUMN_WIDTH + NAME_COLUMN_WIDTH + STATUS_COLUMN_WIDTH;

const double PERCENTAGE_MULTIPLIER = 100.0;
const int INPUT_BUFFER_SIZE = 1000;

// Function prototypes
int readMedicinesFromFile(List<Medicine> &list, const string &filename);
string intToStr(int value);
string getStatusText(const Medicine &m);
void printMedicineTable(const List<Medicine> &list);
int getTotalUnits(const List<Medicine> &list);
void printHighestStock(const List<Medicine> &list);
double getOutOfStockPercentage(const List<Medicine> &list);
void updateUnits(List<Medicine> &list);
void printMainMenu();
void pauseScreen();

// Main function
int main()
{
  // Create a linked list to hold the medicine records and read them from the data file
  List<Medicine> medicines;
  int medicineCount = readMedicinesFromFile(medicines, DATA_FILE);

  // If no records were read, inform the user and exit the program
  if (medicineCount == 0)
  {
    cout << "No medicine records could be read from \"" << DATA_FILE << "\"." << endl;
    cout << "Please make sure the file exists in the same folder as the program." << endl;
    return 0;
  }

  // Inform the user how many records were loaded and enter the main menu loop
  cout << "Loaded " << medicineCount << " medicine record(s) from \"" << DATA_FILE << "\"." << endl;

  // Main menu loop: keep showing the menu and acting on the user's choice until they select the "Exit" option.
  int choice = 0;
  do
  {
    printMainMenu();
    cout << "Enter your choice: ";
    cin >> choice;

    if (cin.fail())
    {
      cin.clear();
      cin.ignore(INPUT_BUFFER_SIZE, '\n');
      cout << "\nInvalid input. Please enter a number between "
           << MENU_SHOW_TABLE << " and " << MENU_EXIT << ".\n"
           << endl;
      continue;
    }

    // Handle the user's menu choice using a switch statement
    switch (choice)
    {
    case MENU_SHOW_TABLE:
      cout << endl;
      printMedicineTable(medicines);
      break;

    case MENU_SHOW_TOTAL:
      cout << "\nTotal number of units in stock: "
           << getTotalUnits(medicines) << endl;
      break;

    case MENU_SHOW_HIGHEST_STOCK:
      cout << endl;
      printHighestStock(medicines);
      break;

    case MENU_SHOW_OUT_OF_STOCK_PCT:
      cout << "\nPercentage of medicines currently Out of Stock: "
           << fixed << setprecision(2)
           << getOutOfStockPercentage(medicines) << "%" << endl;
      break;

    case MENU_UPDATE_UNITS:
      updateUnits(medicines);
      break;

    case MENU_EXIT:
      cout << "\nExiting program. Goodbye!" << endl;
      break;

    default:
      cout << "\nInvalid choice. Please select an option between "
           << MENU_SHOW_TABLE << " and " << MENU_EXIT << "." << endl;
      break;
    }

    // Pause after every action except exiting, so the user has a chance to read the output before the menu reprints and they are prompted again.
    if (choice != MENU_EXIT)
    {
      cout << endl;
      pauseScreen();
    }

  } while (choice != MENU_EXIT);

  return 0;
}

// Reads "ID,Name,Units" lines into the linked list. Empty or malformed
// lines are skipped. Returns the number of records read.
int readMedicinesFromFile(List<Medicine> &list, const string &filename)
{
  ifstream inFile(filename.c_str());
  int count = 0;

  if (!inFile.is_open())
  {
    return 0;
  }

  string line;
  while (getline(inFile, line))
  {
    if (line.empty())
    {
      continue;
    }

    int firstComma = line.find(',');
    int secondComma = line.find(',', firstComma + 1);

    if (firstComma == (int)string::npos || secondComma == (int)string::npos)
    {
      continue;
    }

    int id = atoi(line.substr(0, firstComma).c_str());
    string name = line.substr(firstComma + 1, secondComma - firstComma - 1);
    int units = atoi(line.substr(secondComma + 1).c_str());

    list.insertAtEnd(Medicine(id, name, units));
    count++;
  }

  inFile.close();
  return count;
}

string intToStr(int value)
{
  ostringstream oss;
  oss << value;
  return oss.str();
}

// Builds the status text shown in the table: "[x units] Available"
// when units > 0, otherwise "Out of Stock".
string getStatusText(const Medicine &m)
{
  if (m.getStatus() == "Available")
  {
    return "[" + intToStr(m.getUnits()) + " units] Available";
  }
  return "Out of Stock";
}

void printMedicineTable(const List<Medicine> &list)
{
  cout << left
       << setw(ID_COLUMN_WIDTH) << "ID"
       << setw(NAME_COLUMN_WIDTH) << "Name"
       << setw(STATUS_COLUMN_WIDTH) << "Status" << endl;
  cout << string(TABLE_WIDTH, '-') << endl;

  for (int i = 0; i < list.size(); i++)
  {
    const Medicine &m = list.getAt(i);
    cout << left
         << setw(ID_COLUMN_WIDTH) << m.getId()
         << setw(NAME_COLUMN_WIDTH) << m.getName()
         << getStatusText(m) << endl;
  }
}

int getTotalUnits(const List<Medicine> &list)
{
  int total = 0;
  for (int i = 0; i < list.size(); i++)
  {
    total += list.getAt(i).getUnits();
  }
  return total;
}

void printHighestStock(const List<Medicine> &list)
{
  if (list.isEmpty())
  {
    cout << "No records available." << endl;
    return;
  }

  int highestIdx = 0;
  for (int i = 1; i < list.size(); i++)
  {
    if (list.getAt(i).getUnits() > list.getAt(highestIdx).getUnits())
    {
      highestIdx = i;
    }
  }

  // // Create a linked list and load the medicine records from the file.
  const Medicine &m = list.getAt(highestIdx);
  cout << "Medicine with the highest number of units available:" << endl;
  cout << "  Medicine ID : " << m.getId() << endl;
  cout << "  Name        : " << m.getName() << endl;
  cout << "  Units       : " << m.getUnits() << endl;
  cout << "  Status      : " << m.getStatus() << endl;
}
// Calculates the percentage of medicines that are out of stock (units == 0).
double getOutOfStockPercentage(const List<Medicine> &list)
{
  if (list.isEmpty())
  {
    return 0.0;
  }

  int outOfStock = 0;
  for (int i = 0; i < list.size(); i++)
  {
    if (list.getAt(i).getStatus() == "Out of Stock")
    {
      outOfStock++;
    }
  }
  return (double(outOfStock) / double(list.size())) * PERCENTAGE_MULTIPLIER;
}

// Prompts the user for a Medicine ID and new units, searches for the medicine in the list, and updates its units if found.
void updateUnits(List<Medicine> &list)
{
  int id, newUnits;
  cout << "\nEnter the Medicine ID to update: ";
  cin >> id;

  if (cin.fail())
  {
    cin.clear();
    cin.ignore(INPUT_BUFFER_SIZE, '\n');
    cout << "Invalid Medicine ID entered." << endl;
    return;
  }

  // Search by ID using a temporary Medicine (equality compares IDs).
  Medicine *m = list.search(Medicine(id, "", 0));
  if (m == 0)
  {
    cout << "No medicine found with ID " << id << "." << endl;
    return;
  }

  cout << "Current units for " << m->getName()
       << " (ID " << id << "): " << m->getUnits() << endl;
  cout << "Enter the new number of units: ";
  cin >> newUnits;

  if (cin.fail() || newUnits < 0)
  {
    cin.clear();
    cin.ignore(INPUT_BUFFER_SIZE, '\n');
    cout << "Invalid number of units entered. Update cancelled." << endl;
    return;
  }

  m->setUnits(newUnits);
  cout << "Stock updated successfully. " << m->getName()
       << " now has " << m->getUnits() << " units ("
       << m->getStatus() << ")." << endl;
}

// Displays the main menu options to the user. The option numbers printed here match the MENU_* constants used in the switch statement in main(), so the two can never fall out of step.
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

// Pauses the program and waits for the user to press Enter before continuing. This is used after displaying results so the user has time to read them before the menu reappears.
void pauseScreen()
{
  cout << "Press Enter to continue...";
  cin.ignore(INPUT_BUFFER_SIZE, '\n');
  cin.get();
}