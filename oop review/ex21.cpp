#include <iostream> 
using namespace std;

int max (int n1, int n2){
	return n1 > n2 ? n1 : n2;
}
int findMax(int* arr, int length)
{
    if(length==1){
    	return arr[0];
	}
	return max( findMax(arr,length-1), arr[length-1] );
}
int main(){
	int arr[] = {10, 5, 7, 9, 15, 6, 11, 8, 12, 2};
	cout << findMax(arr, 10);	
	return 0;
}
