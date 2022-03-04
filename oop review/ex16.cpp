#include <iostream>
using namespace std;
void print(int n,int *temp){
	
	if(n>= *temp){
		cout<<n;
		return;
	}
	else{
	    cout<<n<<", ";
		print(n+5,temp);
		return;
	}
	
	return;
}



void printPattern(int n) 
{ 
	static int *temp=&n;
    if(n<=0){
    	if(n==0){
			cout<< 0<<", ";
				print(n+5,temp);
			return;
		}
		else{
			cout<<n<<", ";
				print(n+5,temp);
			return;
		}
	}
	else{
		
			cout << n<<", ";
    		printPattern(n-5);
    		return;
	}
	delete [] temp;
    return;
}

int main(){
   printPattern(14);
   cout<<"\n";
   printPattern(16);
   cout<<"\n";
   printPattern(10);
   cout<<"\n";
   printPattern(20);
return 0;
}
