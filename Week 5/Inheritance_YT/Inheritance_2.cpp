#include <iostream>

using namespace std;

class Shape
{
public:
  double area;
  double volume;
};

class Cube : public Shape
{
public:
  double side;
  Cube(double side)
  {
    this->side = side;
    this->area = side * side * 6;
    this->volume = side * side * side;
  }
};

class Sphere : public Shape
{
public:
  double radius;
  Sphere(double radius)
  {
    this->radius = radius;
    this->area = 4 * 3.14159 * (radius * radius);
    this->volume = (4.0 / 3.0) * 3.14159 * (radius * radius * radius);
  }
};

int main()
{
  Cube cube(10);
  Sphere sphere(10);

  cout << "Cube Area: " << cube.area << endl;
  cout << "Cube Volume: " << cube.volume << endl;
  cout << "---------------------------" << endl;
  cout << "Sphere Area: " << sphere.area << endl;
  cout << "Sphere Volume: " << sphere.volume << endl;

  return 0;
}