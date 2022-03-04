#include <iostream>
#include <fstream>
using namespace std;
int add(int a, int b) {
    return a + b;
}
int sub(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
int divide(int a, int b) {
    return a / b;
}
void calculate(int a, int b, int opt)
{
    int (*myfunc)(int, int);
      
    // STUDENT ANSWER BEGIN
    if (opt==0)
    {
        myfunc=&add;
	}
    else if(opt==1)
    {
        myfunc=& sub;
    }
    else if(opt==2)
    {
         myfunc=&multiply;
    }
    else {
          myfunc=&divide;
    }
    

    // STUDENT ANSWER END

    int ans = (*myfunc)(a, b);
    printf("Output of calculation is %d.\n", ans);
}
int main() {
    calculate(1,2,0);
    cout<<'\n'<<'\n';
    calculate(1,2,1);
    return 0;
}
