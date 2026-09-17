#include <iostream>
//#include <string.h>

using namespace std;

class Shape{
	private:
		int area;
	public:
		virtual void draw() ;
};

class Circle: public Shape {
	public:
		void draw(){
			cout << "\nDrawing a Circle";
		}
};

class Rect: public Shape {
	public:
//		void draw(){
//			cout << "\nDrawing a Rect";
//		}
};

int main(){
	
//	Shape s;
//	s.draw();
	Circle c;
	c.draw();
	
	return 0;
}
