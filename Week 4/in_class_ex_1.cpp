#include <iostream>

using namespace std;

int main(){
	
	int val[5] = {1,2,3,4,5};
	
	int res[5] = {9,8,7,6,5};
	
	int *pt1 = &val[0];
	int *pt2 = res;
	
	for(int i=0;i<5;i++){
		if(*pt1 % 2 == 0){
			*pt2 = *pt1;
		}
		pt1++;
		pt2++;
	}
	
	for(int i=0;i<5;i++){
		cout << val[i] << " ";
	}
	cout << endl;
	
	for(int i=0;i<5;i++){
		cout << res[i] << " ";
	}
	
	return 0;
}
