#include <iostream>
 #include <string.h>
using namespace std;
bool l(char *s1, char *s2){
	
	
	
}



bool isPalindrome(string str){
	int size=str.length();
	char *c=new char[size + 1];
	strcpy(c,str.c_str());
	int len=strlen(c);
	return l(c,c+len-1);
}
int main(){
	cout << isPalindrome("mom")<<'\n';

cout << isPalindrome("do geese see god");
return 0;
}
