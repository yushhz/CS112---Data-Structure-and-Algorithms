#include <iostream>

using namespace std;

struct Point
{
  int x;
  int y;
};

int main()
{
  // Point p1, p2, p3;
  // or
  // Point p[3];
  // or
  Point p[3] = {{1, 2}, {10, 20}, {30, 40}};

  // int x1 = 1;
  // int y1 = 2;
  p[0].x = 1;
  p[0].y = 2;

  // int x2 = 10;
  // int y2 = 20;
  p[1].x = 10;
  p[1].y = 20;

  // int x3 = 30;
  // int y3 = 40;
  p[2].x = 30;
  p[2].y = 40;

  return 0;
}