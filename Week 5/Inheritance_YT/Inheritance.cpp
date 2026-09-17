#include <iostream>

using namespace std;

// Parent class
class Animal
{
public:
  bool alive = true;

  void eat()
  {
    cout << "This animal is eating" << endl;
  }
};

// Child class
class Dog : public Animal
{
public:
  void bark()
  {
    cout << "Woof!" << endl;
  }
};

class Cat : public Animal
{
public:
  void meow()
  {
    cout << "Meow!" << endl;
  }
};

int main()
{

  // Inheritance = A class can receive attributes and methods from another class
  //               Children classes inherit from a Parent class
  //               Helps to reuse similar code found within multiple classes

  Dog dog;
  Cat cat;

  cout << dog.alive << endl;
  dog.eat();
  dog.bark();

  cout << "--------------------------" << endl;

  cout << cat.alive << endl;
  cat.eat();
  cat.meow();

  return 0;
}