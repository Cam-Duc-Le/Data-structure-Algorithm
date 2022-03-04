#include <iostream>
using namespace std;
bool containsPattern(char* text, char* pattern)
{
    /*  
     * STUDENT ANSWER
     */
    if(*text=='\0') return false;
    if(*text == *pattern){
        if(*(pattern+1)=='\0') return true;
        return containsPattern(text+1,pattern+1);
    }
    
    return containsPattern(text+1,pattern);
}
int main(){
   cout << containsPattern((char *)"Dai hoc Bach Khoa",(char *)"Bach Khoa");
return 0;
}