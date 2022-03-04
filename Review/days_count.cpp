#include <iostream>
using namespace std;
struct time{
	int date,month, year;
};
int main(){
	time s,e;
	int day1=0 , day2=0;
	cout<<"start of the period: ";
	cin>>s.date;cout<<"/"; cin>>s.month;cout<<"/"; cin>>s.year;
	cout<<"\n"
	cout<<"end of the period: ";
	cin>>e.date;cout<<"/";cin>>e.month;cout<<"/"; cin>>e.year;
	int m31[]={1,3,5,7,8,10,12};
	int m30[]={4,6,9,11};
	int m28;
	if(s.year%4 == 0 && s.year%4 != 0 ){ // nam nhuam
		if(s.month ==2) day1= 31 + 29 +  s.year*365 + s.date;
	}
	if(e.year%4 == 0 && e.year%4 != 0 ){ // nam nhuam
		if(e.month ==2) day2= 31 + 29 +  e.year*365 + e.date;
	}
	
	// tinh so nam nhuan 
	if(s.year%400 == ){
		
	}
	
	
	return 0;
}
