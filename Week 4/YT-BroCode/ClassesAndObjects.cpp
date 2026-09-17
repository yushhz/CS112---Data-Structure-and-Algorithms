#include <iostream>

using namespace std;

class Human
{

public:
  string name;
  int age;
  string occupation;

  void eat()
  {
    cout << name << " is eating" << endl;
  }

  void drink()
  {
    cout << name << " is drinking" << endl;
  }

  void sleep()
  {
    cout << name << " is sleeping" << endl;
  }
};

class Car
{
public:
  string make;
  string model;
  int year;
  string color;

  void start()
  {
    cout << "The " << color << " " << make << " " << model << " is starting." << endl;
  }

  void accelerate()
  {
    cout << "The " << color << " " << make << " " << model << " is accelerating." << endl;
  }

  void brake()
  {
    cout << "The " << color << " " << make << " " << model << " is braking." << endl;
  }
};

int main()
{

  // Object = A collection of attributes and methods
  //          They can have characteristics and could perform actions
  //          Can be used to mimic real world items (i.e. Car, Dog, Phone, etc.)
  //          Created from a class which acts as a blueprint

  Human human1;
  Human human2;

  Car car1;

  human1.name = "Rick";
  human1.age = 25;
  human1.occupation = "Programmer";

  human2.name = "Morty";
  human2.age = 20;
  human2.occupation = "Student";

  car1.make = "Ford";
  car1.model = "Mustang";
  car1.year = 2022;
  car1.color = "Red";

  cout << human1.name << endl;
  cout << human1.age << endl;
  cout << human1.occupation << endl;

  cout << "--------------------------" << endl;

  human1.eat();
  human1.drink();
  human1.sleep();

  cout << "--------------------------" << endl;

  cout << human2.name << endl;
  cout << human2.age << endl;
  cout << human2.occupation << endl;

  cout << "--------------------------" << endl;

  human2.eat();
  human2.drink();
  human2.sleep();

  cout << "--------------------------" << endl;

  cout << car1.make << endl;
  cout << car1.model << endl;
  cout << car1.year << endl;
  cout << car1.color << endl;

  cout << "--------------------------" << endl;

  car1.start();
  car1.accelerate();
  car1.brake();

  return 0;
}