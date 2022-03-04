#include <iostream>
using namespace std;
void swap(int *xp, int *yp){  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
void selectionSort(int *arr, int n){
	const int N=n;
	int i,min;
	min = 0;
	for(i=0; i < n-1; i++){
		min =i;
		for(int j=i+1; j < N; j++){
			if(arr[j] < arr[min]){
				min = j;
			} 
		}
			swap(&arr[i] , &arr[min]);		
	}
}
void printArray(int arr[], int n)  
{  
    int i;  
    for (i = 0; i < n; i++)  
        cout << arr[i] << " ";  
    cout << endl; 
}  
int main(){
	int arr[] = { 2,12, 11, 13, 5, 6 };  
    int n = sizeof(arr) / sizeof(arr[0]);  
  	selectionSort(arr, n);  
    printArray(arr, n);  
  
    return 0;  
}
