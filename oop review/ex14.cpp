#include <iostream>
using namespace std;

int findLCM(int a, int b)
{
     static int cc = 0;
    
    cc = cc+b;
    
    if((cc % a == 0) && (cc % b == 0)) return cc;
    return findLCM(a, b);
}
int main(){
   cout << findLCM(10, 102);
return 0;
}
