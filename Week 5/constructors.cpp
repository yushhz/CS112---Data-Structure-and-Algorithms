#include <iostream>

using namespace std;

class point{
    public:
    point(){
       x = -1;
       y = -1;
    }
    point(int x, int y){
     this->x = x;
     this->y = y;          
    }
    protected:
    int x;
    int y;
};
class circle: public point{
    public:
    circle();
    circle(int x, int y, int radius);
    int radius;
    void print(){
        cout<<x<<", "<<y<<", "<<radius<<endl;     
    }
};

circle::circle()
:point(){
     radius = -1;                
}
circle::circle(int x, int y, int radius)
//:point(x,y)
{
 this->radius = radius;
}


int main(){
    //point p;
    
    
    circle c(4, 6, 9);
    c.print();
    
    
    system("pause");
    return 0;
}
