#include <iostream>
#include <math.h>
using namespace std;

void ascendingSort(int a[], int n) {
    /*
     * STUDENT ANSWER
     * TODO: sort array in ascending order. 
     */
    for(int i=0;i<n;i++){
        for(int j=0;j < (n-i);j++ ){
            if(a[j]>a[j+1]){
                int temp=a[j+1];
                a[j+1]=a[j];
                a[j]=temp;
            }
        }
    }

}

void descendingSort(int a[], int n) {
    /*
     * STUDENT ANSWER
     * TODO: sort array in descending order. 
     */
     for(int i=0;i<n;i++){
        for(int j=0;j < (n-i);j++ ){
            if(a[j]<a[j+1]){
                int temp=a[j+1];
                a[j+1]=a[j];
                a[j]=temp;
            }
        }
    }

}

void mySort(int a[], int n, void (*sort)(int[], int)) {
	/*
     * STUDENT ANSWER
     * TODO: sort array based on sort algorithm of function sort. 
     */
    (*sort)(a,n);

}

int main() {
    int n = 5;
    int a[5] = { 1, 2, 3, 4, 5 };
    void (*sortAlgorithm)(int[], int) = descendingSort;

     mySort(a, n, sortAlgorithm);
    for (int i = 0; i < n; ++i) {
	    printf("%d ", a[i]);
    }
    cout<<'\n';
    n = 10;
    int b[10] = { 4, 6, 1, 3, 4, 7, 8, 9, 10, 0 };
    void (*sortAlgorithm1)(int[], int) = ascendingSort;

    mySort(b, n, sortAlgorithm1);
    for (int i = 0; i < n; ++i) {
	    printf("%d ", b[i]);
    }
	
    return 0;
}