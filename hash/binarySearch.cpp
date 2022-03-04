#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>

using namespace std;
int binarySearch(int arr[], int left, int right, int x){
    if (left <= right)
    {
        //int result = -1;
        int mid = left + (right - 1) / 2;
        if (arr[mid] > x)
        {
            cout << "We traverse on index: " << mid << endl;
            return binarySearch(arr, left, mid - 1, x);
        }
        else if (arr[mid] < x)
        {
            cout << "We traverse on index: " << mid << endl;
            return binarySearch(arr, mid + 1, right, x);
        }
        else
        {
            cout << "We traverse on index: " << mid << endl;
            return mid;
        }
    }

    return -1;
}

bool checkAnswer(int arr[], int n, pair<int, int> &pair1, pair<int, int> &pair2)
{
    if ((pair1.first + pair1.second) == (pair2.first + pair2.second))
        return true;
    return false;
}
bool findPairs(int arr[], int n, pair<int, int> &pair1, pair<int, int> &pair2)
{
    // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise, return false.
    map<int, pair<int, int>> Hash;
    pair<int, int> p;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int sum = arr[i] + arr[j];
            if (Hash.find(sum) == Hash.end())
            { // not exist equal sum
                Hash[sum] = make_pair(i, j);
            }
            else
            {
                pair2.first = arr[i];
                pair2.second = arr[j];
                p = Hash[sum];
                pair1.first = arr[p.first];
                pair1.second = arr[p.second];
                return true;
            }
        }
    }

    return false;
}

#include <string.h>
int foldShift(string key, int addressSize){
    int tmp = 0;
    int sum = 0;
    int i = 0;
    string str;
    for (auto it = key.begin(); it != key.end();){
        i++;
        str = *it;
        
        tmp = tmp * 10 + stoi(str);
        if (++it == key.end() || i == addressSize)
        {
            sum += tmp;
            tmp = 0;
            i = 0;
        }
        str = "";
    }

    int res = 0;
    for (int i = 0; i < addressSize; i++){
        res += sum % 10 * pow(10, i);
        sum /= 10;
    }
    return res;
}
int foldShift(long long key, int addressSize)
{
    return (to_string(key), addressSize);
}
int rotation(long long key, int addressSize)
{
    string tmp = to_string(key % 10);
    key /= 10;
    tmp.append(to_string(key));
    return foldShift(tmp, addressSize);
}


int interpolationSearch(int arr[], int left, int right, int x){
    if(left <= right){
        
        int mid = (left + right)/2;

        if(x > arr[mid]){
           // cout << "We traverse on index: " << mid << endl;
            return interpolationSearch(arr,mid+1,right,x);
        } 
        else if(x < arr[mid]){
            //cout << "We traverse on index: " << mid << endl;
            return interpolationSearch(arr,left,mid-1,x);
        }
        else{
            cout << "We traverse on index: " << mid << endl;
            return mid;
        }
    }
    return -1;
}

int jumpSearch(int arr[], int x, int n){
        for(int k=0; k<n; k+=4){
            if(x == arr[k]){
                cout<<k;
                return k;
            }
            else if( x <= arr[n-1] && x > arr[k] && k > n-4  ){
                cout<<k<<" ";
                for(int i=k+1; i<n; i++){
                    if(arr[i] == x){
                        cout<<i;
                        return i;
                    }
                    else{
                        cout<<i<<" ";
                    }
                }
                return -1;
            }
            else if( (x < arr[k+4]) && (x > arr[k]) && (k+4 < n) ){
                cout<<k<<" ";
                if( k+4 < n) cout<<k+4<<" ";
                
                for(int i=k+1; i<k+4; i++){
                    if(arr[i] == x){
                        cout<<i;
                        return i;
                    }
                    else{
                        cout<<i<<" ";
                    }
                }
                return -1;
            }
            else if(x > arr[n-1] && k > n-4){
                for(int i=k; i<n; i++){
                    cout<<i<<" ";
                }
                cout<<n;
                return -1;
            }
            else{
                cout<<k<<" ";
            }
        }
    return -1;
}



long long middleSquare(long long seed , int size){
	seed = seed*seed; 
	cout<<"seed is "<<seed<<endl;
	int len= log10(seed) + 1;
	if(len <= size) return seed; 
	while(true){
		seed = seed/10; 
		len = log10(seed) +1;
		if(len == size) break; 
		//extract first digit
		//int clone = seed;
		int firstDigit = seed/(int)pow(10,len-1); 
		seed = seed - firstDigit * pow(10,len-1); 
		len = log10(seed) + 1; 
		if(len == size ) break; 
	}
	return seed; 
}
long int moduloDivision(long int seed, long int mod){
    return seed%mod ;
}
long int digitExtraction(long int seed,int* extractDigits,int size){
    long int res = 0;
    string str = to_string(seed);
    string s;
    int c = 0, k = 0;
    for(auto it = str.begin(); it != str.end(); it++){
        if(k == extractDigits[c] && c < size){
            c++;
            s = *it;
            res = 10*res + (long int)std::stoi(s);
        }
        k++;
    }
    return  res;
}

int main(){

    /*
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    int x = 9;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = binarySearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array" : cout << "Element is present at index " << result;*/
    /*
    int arr[] = { 3, 4, 7, 1, 0 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2)){
        if (checkAnswer(arr, n, pair1, pair2)) {
            printf("Your answer is correct.\n");
        }
        else printf("Your answer is incorrect.\n");
    }
    else printf("No pair found.\n");
*/

    cout << "rotate n fold shift: "<<rotation(600101, 2)<<endl;

/*
    int arr[] = { 1,2,3,4,5,6,7,8,9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 9;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"     : cout << "Element is present at index " << result;
*/

    int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 611, 612, 613 };
    int x = 614;
    int n = sizeof(arr) / sizeof(arr[0]);
    cout<<"number of element: "<<n<<endl;
    int index = jumpSearch(arr, x, n);

    if (index != -1) {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else {
        cout << "\n" << x << " is not in array!";
    }

/*
    cout <<"moduloDiv: " <<moduloDivision(137456, 19);
    cout<<endl;
    int a[]={1,2,5};
    cout << "digit extract:  "<<digitExtraction(122443,a,3);
    cout<<endl;
    cout <<"mid square:  "<<midSquare(9452);
*/
    return 0;
}