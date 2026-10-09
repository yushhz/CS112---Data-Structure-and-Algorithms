Authors: Riyashna Prasad and Ayush Kirpal
Student ID: S11225667 and S11250489
Date created: 7th October 2026
Version: 1.10

About this program:

    USP Pharmacy Stock Management System
    ----------------------------------------
    This program reads medicine records from a text file, allows the user to update stock units,
    and prints a full stock report. Each medicine record consists of an ID, name and the number of units available.

    This is Assignment 2. It builds on Assignment 1 by replacing the array of structs with a
    linked list of Medicine objects. The List and Node classes are generic (templates), so they can
    be used with any data type, and main.cpp only works through the List class (never through
    Node pointers directly).

    For example, the data file "medicines.txt" may contain:
    3001,Paracetamol,5
    3002,Ibuprofen,0

    The program will read these records into a linked list of Medicine objects, and provide the following functionality:

        1. View a table of all medicines with their availability status
        2. View the total number of units in stock
        3. View the medicine with the highest number of units available
        4. View the percentage of medicines that are out of stock
        5. Update the number of units for a medicine (by Medicine ID)
        6. Exit the program

Files in this program:

    main.cpp
        The driver file. It reads the data file into the list, shows the menu and runs the
        option chosen by the user. It also contains the helper functions for reading the file,
        printing the table, totalling units, finding the highest stock, calculating the
        out-of-stock percentage and updating units.

    Medicine.h
        The Medicine class. It stores the ID (int), name (string) and units (int) as private data.
        The availability status is NOT stored. getStatus() calculates it from the units each time
        ("Available" if units > 0, otherwise "Out of Stock"), so it can never be out of date.
        Two Medicine objects are equal when their IDs match (operator==), which lets the list
        search for a medicine by ID.

    List.h
        The generic List<T> class (singly linked list). It keeps track of the first node, the last
        node and the number of items. It provides:
            insertAtEnd(value) - adds an item to the end of the list
            getAt(index)       - returns the item at a position (0-based)
            search(key)        - returns a pointer to the first item equal to key, or NULL
            size(), isEmpty()  - number of items / whether the list is empty
            clear()            - deletes every node
        The destructor calls clear() so all nodes are freed automatically. Copying a list is
        disabled so two lists can never share (and double-delete) the same nodes.

    Node.h
        The generic Node<T> class. Each node holds one item of type T and a pointer to the next node
        (NULL for the last node).

    medicines.txt
        The data file. One medicine per line in the form ID,Name,Units.

Data file format:

    ID,Name,Units
    e.g.  3001,Paracetamol,5

    - Empty lines are skipped.
    - Lines that do not contain two commas are skipped, so one bad line does not stop the program.
    - If the file is missing or contains no valid records, the program shows a message and exits.

Menu options in detail:

    1. Show table of all medicines
       Prints ID, Name and Status for every medicine. The status shows "[x units] Available"
       when units > 0, otherwise "Out of Stock".

    2. Show total units in stock
       Adds up the units of every medicine.

    3. Show medicine with highest stock
       Prints the full details (ID, name, units, status) of the medicine with the most units.
       If two medicines tie, the one that appears first in the file is shown.

    4. Show percentage of medicines Out of Stock
       (medicines with 0 units / total medicines) x 100, shown to 2 decimal places.

    5. Update units for a medicine
       Asks for a Medicine ID, shows the current units, then asks for the new number of units.
       The change is made in the list (in memory). medicines.txt is not modified.

    6. Exit
       Ends the program.

Input checking:

    - A non-numeric menu choice or an out-of-range number shows an error and the menu is shown again.
    - An unknown Medicine ID shows "No medicine found with ID ...".
    - A non-numeric ID, or new units that are negative or non-numeric, cancels the update.
    - A decimal such as 5.5 is read as the whole number 5.

How to compile and run:

    1. Keep main.cpp, Medicine.h, List.h, Node.h and medicines.txt in the same folder.
    2. Open a terminal in that folder.
    3. Compile:   g++ main.cpp -o pharmacy
    4. Run:       ./pharmacy          (on Windows: pharmacy.exe)

    The program looks for medicines.txt in the folder it is run from.

Example (original medicines.txt):

    Total units in stock ........................ 28
    Percentage of medicines Out of Stock ........ 25.00%
    Medicine with highest stock ................. 3003 Ibuprofen (8 units)

Instructions for the reviewer (Visual Studio)

1. Unzip the submitted folder.

2. Open the folder and double-click the solution file (the .sln file).
   Visual Studio will open the project.

3. In Solution Explorer (right-hand side), check that these files are listed:
   Source Files : main.cpp
   Header Files : Medicine.h, List.h, Node.h

4. Build the program:
   Build > Build Solution (Ctrl+Shift+B)
   The Output window should show "Build: 1 succeeded".

5. Run the program:
   Debug > Start Without Debugging (Ctrl+F5)
   A console window opens showing the USP Pharmacy menu.
   (Using Ctrl+F5 keeps the window open after the program ends.)

6. Use the menu by typing a number and pressing Enter:
   1 Show table of all medicines
   2 Show total units in stock
   3 Show medicine with highest stock
   4 Show percentage of medicines Out of Stock
   5 Update units for a medicine (enter the Medicine ID, then the new units)
   6 Exit

Notes:

- The data file medicines.txt is in the project folder (the same folder as the
  .vcxproj file). The program reads it automatically when it starts.
- If the program says "No medicine records could be read", medicines.txt is not in
  the project folder. Copy it next to the .vcxproj file and run again.
- If Visual Studio asks to retarget the solution or upgrade the platform toolset,
  accept the default option (OK).

ACKNOWLEDGEMENT:

This program was written for CS112 Assignment 2, following the
requirement to use only C++ LinkedList of class object code, reading all data from
the provided file.
