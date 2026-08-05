#include <iostream>

using namespace std;

int main()
{

  // Null Pointers = special value that means something has no value.
  //                 When a pointer is holding a null value,
  //                 that pointer is not pointing to anything (null pointer)

  // nullptr = keyboard represents a null pointer literal

  // nullptr are helpful when determining if an address
  // was successfully assigned to a pointer

  // Intialized so that pointer does not point to a random memory location
  int *pointer = nullptr; // pointer is initialized to null
  int x = 123;

  pointer = &x; // pointer is assigned the address of x

  if (pointer == nullptr)
  {
    cout << "Address was not assigned" << '\n';
  }
  else
  {
    cout << "Address was assigned" << '\n';
  }

  return 0;
}