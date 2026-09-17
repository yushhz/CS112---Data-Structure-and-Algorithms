#include <iostream>

using namespace std;

void walk(int steps);
int factorial(int num);

int main()
{

  // recursion = a programming technique where a function invokes itself from within
  //             break a complex concept into a repeatable single step

  // (iterative vs recursive)

  // advantages = less code and is cleaner
  //              useful for sorting and searching algorithms

  // disadvantages = uses more memory and is slower

  walk(5);
  cout << "Factorial of 10 is: " << factorial(10) << endl;

  return 0;
}

void walk(int steps)
{
  if (steps > 0)
  {
    cout << "You take a step" << endl;
    walk(steps - 1); // Recursive call
  }
}

int factorial(int num)
{
  if (num > 1)
  {
    return num * factorial(num - 1); // Recursive call
  }
  else
  {
    return 1; // Base case
  }
}