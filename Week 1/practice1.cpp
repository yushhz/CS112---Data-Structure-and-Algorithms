/*
Author: Ayush Kirpal
Date: 24/07/2026
Description: Programs asks for two integers, creates a sum and checks if the sum is positive, negative or zero. Then prints sum
Purpose: This program is designed for a practice rundown of C++ and at the same time test the branch im currently using
*/

#include <iostream>

int main()
{

  int num1, num2, sum;
  std::cout << "Enter two integers: ";
  std::cin >> num1 >> num2;

  sum = num1 + num2;

  if (sum > 0)
  {
    std::cout << "The sum is positive." << std::endl;
  }
  else if (sum < 0)
  {
    std::cout << "The sum is negative." << std::endl;
  }
  else
  {
    std::cout << "The sum is zero." << std::endl;
  }

  std::cout << "The sum of " << num1 << " and " << num2 << " is: " << sum << std::endl;

  return 0;
}