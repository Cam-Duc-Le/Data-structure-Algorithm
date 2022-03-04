#include <iostream>
using namespace std;



int findGCD(int a, int b)
{
    if (a<=0||b<=0)
    {
       return 0;
    }
    else if(a==b){
        return a;
    }
    else if(a>b){
        return findGCD(a-b,b);
    }
    else
    {
        return findGCD(b-a,a);
    }
    
}
int main(){
    cout << findGCD(124,32);
return 0;
}