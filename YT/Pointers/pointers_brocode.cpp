#include <iostream>

using namespace std;

int main()
{

  // Pointers - variable that stores a memory address of another variable
  //            sometimes it's easire to work with an address

  // & address-of operator
  // * dereference operator

  string name = "Bro Code";
  int age = 21;
  string freePizzas[5] = {"Pizza1", "Pizza2", "Pizza3", "Pizza4", "Pizza5"};

  string *pName = &name;            // pointer to name
  int *pAge = &age;                 // pointer to age
  string *pFreePizzas = freePizzas; // pointer to first element of array

  cout << *pName << '\n';
  cout << *pAge << '\n';
  cout << *pFreePizzas << '\n'; // dereference pointer to get first element of array

  return 0;
}