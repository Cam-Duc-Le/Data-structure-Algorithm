#include <iostream>
using namespace std;
int main(){
	int m;
	cout<<"input m: ";
	cin>>m;
	int **a=new int*[m];
	for(int i=0;i<m;i++){
		a[i]=new int [m];
		for(int j=0;j<m;j++){
			cin>>a[i][j];
		}	
	}
	
	
	for(int i=0;i<m;i++){
		delete [] a[i];	
	}
	delete [] a;

return 0;
}
