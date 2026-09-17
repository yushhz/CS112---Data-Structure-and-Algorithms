#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
class student{
      private:
        string id;
        int mark;        
      public:
        float getGPA();
        float calcGPA(){
          //doi calcmark
          return 4.3;
        }
        void  setMark(int mark);
        void print_student_details();      
};
void student::print_student_details(){
    cout<<"id: "<<id<<endl<<"name: "<<mark<<endl<<"GPA: "<<calcGPA()<<endl<<endl;
} 
void  student::setMark(int mark){
     student::mark = mark;
} 
float student::getGPA(){
     return calcGPA();
}      
int main(){
    student s1;
    //s1.setMark(89);
    //s1.setGPA(5.4);
    cout<<"\n GPA is: "
    <<s1.getGPA()<<endl;
    
    s1.print_student_details();
    system("PAUSE");
    return 0;
}


