#include <iostream>
#include <fstream>

using namespace std;

int main()
{

  int n, sum;
  sum = 0;
  ifstream fin;
  ofstream fout;
  fin.open("numbers.txt");
  fout.open("out.txt", ios::app);
  // Check if the file is found and opened successfully

  while (cin >> n)
  {
    cout << "Input from a user: " << n << endl;

    if (n < 0)
    {
      cout << "Negative number, retry" << endl;
      continue;
    }
    else if (n == 0)
    {
      cout << "Zero is not allowed, retry" << endl;
      continue;
    }
    else
    {
      sum += n;
    }
  }
  cout << "The sum of the numbers is: " << sum << endl;

  while (fin >> n)
  {
    cout << "Input from a file: " << n << endl;

    if (n < 0)
    {
      cout << "Negative number, retry" << endl;
      continue;
    }
    else if (n == 0)
    {
      cout << "Zero is not allowed, retry" << endl;
      continue;
    }
    else
    {
      sum += n;
    }
  }
  fout << "The sum of the numbers is: " << sum << endl;

  fin.close();
  fout.close();
  return 0;
}