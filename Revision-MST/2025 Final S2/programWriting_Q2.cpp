/*
Question 2:

You are designing a simple payment system for an e-commerce website.
- Create a base class Payment with a pure virtual function processPayment()
- Derive two classes: CreditCardPayment and PayPalPayment.
- Override processPayment() in each class to display a meaningful message.
- In main(), create objects of both derived classes, store them in pointers to Payment, and call processPayment().
*/

#include <iostream>
using namespace std;

// Base class with pure virtual function
class Payment
{
public:
  virtual void processPayment() = 0; // pure virtual function
  virtual ~Payment() {}              // virtual destructor
};

// Derived class 1
class CreditCardPayment : public Payment
{
public:
  void processPayment() override
  {
    cout << "Processing payment via Credit Card..." << endl;
  }
};

// Derived class 2
class PayPalPayment : public Payment
{
public:
  void processPayment() override
  {
    cout << "Processing payment via PayPal..." << endl;
  }
};

int main()
{
  Payment *p1 = new CreditCardPayment();
  Payment *p2 = new PayPalPayment();

  p1->processPayment();
  p2->processPayment();

  delete p1;
  delete p2;

  return 0;
}