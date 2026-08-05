#include <iostream>

// pbv - Pass by value
// refVar - reference variable
// ptrVar - pointer variable

using namespace std;

void f(int *fptrVar)
{
  *fptrVar = 110;
}

int main()
{

  int pbv = 8;        // Normal variable
  int &refVar = pbv;  // Reference variable
  int *ptrVar = &pbv; // Pointer variable

  cout << "B4 function call : pbv, refVar, ptrVar: " << endl;
  cout << pbv << ", " << refVar << ", " << *ptrVar << endl;

  f(ptrVar); // Pass by reference

  cout << "after function call: " << endl;
  cout << pbv << ", " << refVar << ", " << *ptrVar << endl;

  return 0;
}