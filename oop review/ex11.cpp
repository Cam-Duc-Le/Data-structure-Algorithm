#include <iostream>
using namespace std;



void printArray(int n)
{
    /*  
     * STUDENT ANSWER
     */
    if(n < 0 ) return; 
     printArray(n-1);
     if(n > 0 ) cout<<", ";
     cout<<n;
    
}
int main(){
    printArray(5);
    cout<<'\n';
    printArray(10);
return 0;
}
