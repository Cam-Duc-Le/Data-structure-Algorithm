#include<stdio.h>
#include<iostream>

using namespace std;

// You can also add more helping functions if needed.

int maxNumOfPlayers(int n, long long a[]) {
    // TODO: return the maximum number of players who can participant in the tournament. In case cannot set up a tournament that meets all the conditions, return 0.
    
}



int main(){

long long a[] = { 2, 2, 3 };
int n = sizeof(a) / sizeof(long long);

cout << maxNumOfPlayers(n, a);

long long a[] = { 1, 2, 7, 16 };
int n = sizeof(a) / sizeof(long long);

cout << maxNumOfPlayers(n, a);
    return 0;
}