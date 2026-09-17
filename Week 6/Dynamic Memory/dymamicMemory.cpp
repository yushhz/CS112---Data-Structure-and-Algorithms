#include <iostream>

using namespace std;

int main()
{
  // dynamic memory = Memory that is allocated after the program is already compiled and running.
  //                  Use the 'new' operator to allocate memory in the heap rather than the stack.

  //                  Useful when we don't know how much memory we will need. Makes our program more flexible, especially when accepting user input

  int *pNum = NULL; // pointer to an int, initialized to NULL
  pNum = new int;   // allocate memory on the heap for an int
  *pNum = 42;       // assign a value to the dynamically allocated memory

  cout << "address: " << pNum << endl; // print the address of the dynamically allocated memory
  cout << "value: " << *pNum << endl;  // print the value stored in the dynamically allocated memory

  delete pNum; // free the dynamically allocated memory
  pNum = NULL; // set the pointer to NULL to avoid dangling pointer

  char *pGrades = NULL; // pointer to a char, initialized to NULL
  int size;
  cout << "How many grades do you want to enter? ";
  cin >> size; // get the size of the array from user input

  pGrades = new char[size]; // allocate memory on the heap for an array of 'size' chars

  for (int i = 0; i < size; i++)
  {
    cout << "Enter grade " << (i + 1) << ": ";
    cin >> pGrades[i]; // store user input in the dynamically allocated array
  }

  // print the grades
  cout << "The grades you entered are: ";
  for (int i = 0; i < size; i++)
  {
    cout << pGrades[i] << " ";
  }
  cout << endl;

  delete[] pGrades; // free the dynamically allocated array
  // pGrades = NULL;   // set the pointer to NULL to avoid dangling pointer

  return 0;
}