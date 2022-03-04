#include <iostream>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void selectionSort(T *start, T *end);
};
template <class T>
void Sorting<T>::selectionSort(T *start, T *end)
{
	// assume start la` min
	int i = 0;
	int minIdx,j;
	while((start+i) != (end -1)){
		j=i+1;
		minIdx = i;
		while((start+j) != end){
			if(*(start+j) < *(start+minIdx)){
				minIdx=j;	
			}
			j++;
		}
		int temp=*(start+minIdx);
		*(start+minIdx) = *(start+i);
		*(start+i) = temp;
		printArray(start,end);
		i++;
	}
}
int main(){
	int arr[] = {9, 2, 8, 1, 0, -2};
	Sorting<int>::selectionSort(&arr[0], &arr[6]);
	
	return 0;
}
/*
int minIdx, i, j;
    for (i=0; (start + i) != (end - 1); i++) {
        minIdx = i;
        for (j = i + 1; (start + j) != end; j++) {
            if (*(start + j) < *(start + minIdx))
                minIdx = j;
        }
        int temp = *(start + minIdx);
        *(start + minIdx) = *(start + i);
        *(start + i) = temp;
        printArray(start, end);
    }*/
