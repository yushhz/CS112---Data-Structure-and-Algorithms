// pointers.cpp
// Author: Ayush Kirpal
// Date created: 03/08/2026

#include <iostream>

using namespace std;

const int SIZE = 10;

int main()
{

  int array[SIZE];
  int TV[5] = {1, 2, 3, 4, 5};

  // int *ptr = array;     // Pointer to the first element of the array | int *ptr = &array[0];
  int *ptr = &array[1]; // Pointer to the second element of the array

  int *remote = TV; // Pointer to the first element of the TV array | int *remote = &TV[0];

  cout << (remote + 1) << endl;                // Address of the second element of the TV array
  cout << "2nd tv: " << *(remote + 1) << endl; // Value of the second element of the TV array

  return 0;
}