#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class point{
      public:
      point(){
        x = 3;
        y = 5;  
      }
  int x;
  int y; 
  void print(){
    cout<<x<<", "<<y<<endl;     
  }   
};

int main(){
     
     point p;
     p.x = 88;
     p.print();
     
     system("PAUSE");
    return 0;   
}
