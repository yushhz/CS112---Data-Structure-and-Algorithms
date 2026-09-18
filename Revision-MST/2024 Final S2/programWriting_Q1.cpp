/*
What you need to do:

Make a Shape class that can't be used on its own (abstract class) — it just declares that every shape must have an area() function, but doesn't say how to calculate it yet.
Make two classes that inherit from Shape:
Rectangle — actually calculates area as length × width
Circle — actually calculates area as π × radius²
In main():
Create a Rectangle object, but store it using a Shape pointer (this is the "polymorphism" part — a base class pointer controlling a derived class object).
Call area() through that pointer and print the result.

Why this matters (the concept being tested): Even though the pointer is typed as Shape, calling area() on it correctly runs Rectangle's version of area() — not some generic "Shape" version (since Shape doesn't even have one). This is polymorphism: the same function call behaves differently depending on the actual object type at runtime.
*/

#include <iostream>
using namespace std;

// a) Base class (abstract class)
class Shape
{
public:
  virtual double area() = 0; // pure virtual function
  virtual ~Shape() {}
};

// b) Derived class: Rectangle
class Rectangle : public Shape
{
private:
  double length, width;

public:
  Rectangle(double l, double w) : length(l), width(w) {}

  double area()
  {
    return length * width;
  }
};

// b) Derived class: Circle
class Circle : public Shape
{
private:
  double radius;

public:
  Circle(double r) : radius(r) {}

  double area()
  {
    return 3.14159 * radius * radius;
  }
};

// c) main function
int main()
{
  // create rectangle object
  Shape *rectangle = new Rectangle(5.0, 3.0);

  cout << "Area of Rectangle: " << rectangle->area() << endl;

  delete rectangle;

  return 0;
}