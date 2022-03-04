#include <iostream>
using namespace std;

void printHailstone(int number){
	if(number==1){
		cout<<1;
		return;
	}
	else{
		if(number%2 == 0){
			cout<<number<<" ";
			printHailstone(number/2);
			return;
		}
		else{
			cout<<number<<" ";
			number=number*3+1;
			printHailstone(number);
			return;
		}
	}
	return;
}
int main(){
	printHailstone(32);
	cout<<'\n';
	printHailstone(5);
return 0;
}
