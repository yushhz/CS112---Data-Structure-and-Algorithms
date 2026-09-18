/*
Question 1:

Write a C++ class Book with attribute title and author

    Provide an appropriate parameterized constructor
    Write a method printBook() to display book details
*/

#include <iostream>
#include <string>
using namespace std;

class Book
{
private:
  string title;
  string author;

public:
  // Parameterized constructor
  Book(string t, string a)
  {
    title = t;
    author = a;
  }

  // Method to display book details
  void printBook()
  {
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
  }
};

int main()
{
  Book b1("The Hobbit", "J.R.R. Tolkien");
  b1.printBook();
  return 0;
}
