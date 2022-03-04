#include <iostream>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start + 1;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    static void merge(T* left, T* middle, T* right){
        /*TODO*/
        Sorting::printArray(left, right);
    }
    static	void merge(int arr[], int l, int m, int r){
    	int n1 = m - l + 1;
    	int n2 = r - m;
 
    	// Create temp arrays
    	int L[n1], R[n2];
 
    	// Copy data to temp arrays L[] and R[]
    	for (int i = 0; i < n1; i++)
        	L[i] = arr[l + i];
    	for (int j = 0; j < n2; j++)
        	R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    	int i = 0;
    // Initial index of second subarray
    	int j = 0;
 
    // Initial index of merged subarray
    	int k = l;
 
    	while (i < n1 && j < n2) {
        	if (L[i] <= R[j]) {
            	arr[k] = L[i];
            	i++;
        	}
        	else {
            	arr[k] = R[j];
            	j++;
        	}
        	k++;
    	}
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    merge(arr+l,arr+m,arr+r);
}
    
    static void mergeSort(T *A, int start,int end ) {
   	       if( start >= end ) return;
           int mid = (start + end ) / 2 ;           // defines the current array in 2 parts .
           mergeSort (A, start , mid ) ;                 // sort the 1st part of array .
           mergeSort (A,mid+1 , end ) ;              // sort the 2nd part of array.

        // merge the both parts by comparing elements of both the parts.
        merge(A,start , mid , end );   
    }
    static void mergeSort(T* start, T* end) {
    	int count = 0;
		T *temp = start;
		while(temp!=end){
			temp++;
			count++;
		}	
       mergeSort(start,0,count);
    }
};

int main(){
	int arr[] = {0,2,4,3,1,4};
	Sorting<int>::mergeSort(&arr[0], &arr[5]);
	 
	return 0;
}
