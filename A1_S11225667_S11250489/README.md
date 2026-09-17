====================================================================
CS112: Data Structures & Algorithms - Assignment 1 (Semester II, 2026)
USP Pharmacy Stock Management System
====================================================================

STUDENT ID(S): Ayush Kirpal (S11250489)
: Riyashna Prasad (S11225667)

1. WHAT THE PROGRAM DOES

---

This program manages medicine stock records for the USP Pharmacy
using an array of structs.

Each medicine record has: - Medicine ID (integer) - Medicine Name (string) - Units Available (integer)

The medicine's status ("Available" or "Out of Stock") is NEVER
stored in the struct. It is always calculated on demand by the
getStatus() function, based on whether Units Available is greater
than zero.

When the program starts, it automatically reads all medicine
records from "medicines.txt" (expected to be in the same folder
as the executable) into the array of structs. No data is hard coded
anywhere in the program.

The program then presents a simple text menu with the following
options:

    1. Show table of all medicines
       - Displays a table of every medicine's ID, name, units, and
         calculated availability status
         (e.g. "[5 units] Available" or "Out of Stock")

    2. Show total units in stock
       - Displays the sum of the "units" field across all medicines

    3. Show medicine with highest stock
       - Displays full details of the medicine with the highest
         number of units available

    4. Show percentage of medicines Out of Stock
       - Displays what percentage of all medicine records currently
         have 0 units available

    5. Update units for a medicine
       - Prompts the user for a Medicine ID, looks it up in the
         array, and lets the user enter a new number of units for
         that medicine. If the ID does not exist, the program
         reports this instead of crashing.

    6. Exit
       - Ends the program.

The menu keeps looping, so the user can perform as many operations
as needed until they choose to exit.

2. DATA FILE FORMAT (medicines.txt)

---

Each line in medicines.txt represents one medicine record in the
format:

    MedicineID,MedicineName,UnitsAvailable

Example:
3001,Paracetamol,5
3002,Amoxicillin,0
3003,Ibuprofen,8

The program reads this file line-by-line and splits each line on
the commas to fill in the Medicine ID, Medicine Name, and Units
Available fields of each struct. If medicines.txt is missing or
cannot be opened, the program will print a message and exit safely
instead of crashing.

NOTE: This file must be in the same folder as the CS112_Assignment1.cpp file for it run
successfully.

3. HOW TO RUN THE PROGRAM (Dev-C++ 4.9.9)

---

1. Open Dev-C++ 4.9.9.
2. Go to File -> Open Project or File, and open "CS112_Assignment1.cpp"
   (or create a new empty C++ Console Application project and
   replace its contents with CS112_Assignment1).
3. Make sure "medicines.txt" is placed in the SAME FOLDER as the
   compiled CS112_Assignment1.exe (usually the same folder as CS112_Assignment1.cpp, unless
   you set a different Working Directory in the project settings).
4. Click "Compile & Run" (F9), or "Compile" (F9) then run the
   generated CS112_Assignment1.exe directly.
5. A console window will open showing:
   "Loaded 8 medicine record(s) from "medicines.txt"."
   followed by the main menu.
6. Enter a number from 1 to 6 at the "Enter your choice:" prompt
   and press Enter to use the program. After each action, press
   Enter again when prompted to return to the menu.

7. ACKNOWLEDGEMENT

---

This program was written for CS112 Assignment 1, following the
requirement to use only C++ structs and arrays, reading all data from
the provided file.
