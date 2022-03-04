
#include <iostream>
#include <string>
using namespace std;
int count(char a, string s){
	int c = 0;
	int i = 0;
	while(s[i] != '\0'){
		if(a == s[i]) c++;
		i++;
	}
	return c;
}
bool isPermutation (string a, string b) {
	if(a.length() != b.length()){
		return false;
	}
	int i = 0;
	while(i < a.length()){
		if(count(a[i],a) != count(a[i],b)) return false;
		i++;	
	}
	return true;
}

int main(){
	string a = "abba";
	string b="baba";
	cout << isPermutation(a, b)<<'\n';
	string a1 = "abbac";
	string b1="baba";
	cout << isPermutation(a1, b1);

	return 0;
}



