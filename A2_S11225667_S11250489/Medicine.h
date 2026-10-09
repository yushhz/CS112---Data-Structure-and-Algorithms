#ifndef MEDICINE_H
#define MEDICINE_H

#include <string>
using namespace std;

class Medicine
{
private:
  int id;
  string name;
  int units;

public:
  Medicine() : id(0), name(""), units(0) {}
  Medicine(int id, const string &name, int units)
      : id(id), name(name), units(units) {}

  int getId() const { return id; }
  string getName() const { return name; }
  int getUnits() const { return units; }

  void setUnits(int newUnits) { units = newUnits; }

  // Status is calculated, never stored, so it cannot go out of date.
  string getStatus() const
  {
    return units > 0 ? "Available" : "Out of Stock";
  }

  // Two medicines are considered equal when their IDs match.
  // This lets List<Medicine>::search() find a medicine by ID.
  bool operator==(const Medicine &other) const
  {
    return id == other.id;
  }
};

#endif