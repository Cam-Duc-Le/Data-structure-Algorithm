#include <iostream>
using namespace std;



int strLen(char* str)     
{ 
    /*  
     * STUDENT ANSWER
    */
    if(*str == '\0' ) return 0; 
     return 1 + strLen(str+1); 
} 
int main(){
    char str[] = "Truong ";
    cout << strLen(str);
return 0;
}
