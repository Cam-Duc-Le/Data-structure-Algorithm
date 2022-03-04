#include <iostream>
using namespace std;
int main(){
	int n;
	cout<<"input N: ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	//
	int max=a[0],sec=a[0];
	for (int j=1;j<n;j++){
		if(a[j]>max){
			max=a[j];
		}
		if(a[j]<max&& a[j]>sec){
			sec=a[j];
		}
		if(a[j-1]<max&& a[j-1]>sec){
			sec=a[j-1];
		}
	}
	cout<<"max: "<<max<<'\n';
	cout<<"sec: "<<sec<<'\n';
return 0;
}
