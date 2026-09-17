#include <iostream>
#include <stdlib.h>

using namespace std;

void doll ( int size )
{
	if (size == 0 ) // No doll can be smaller than 0
		return; // Return does not have to return
			// something, it can be used to exit a
			// function
	cout<<size<<endl;
	doll (size-1); // Decrements the size variable so the next
			// doll will be smaller.
}



int main()
{
    doll(10);
    system("PAUSE");
    return 0;
}


