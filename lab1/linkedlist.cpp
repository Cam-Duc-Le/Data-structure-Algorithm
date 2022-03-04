#include <iostream>
#include <string.h>
using namespace std;
struct book {
	char* name=new char[100];
	int year;
	book* next;
};
book *createBook(int n){
	book *head=new book;
	cin>>head->name;
	cin>>head->year;
	if(n==1){
		head->next=NULL;
		return head;
	}
	book *cur=new book;
	cin>>cur->name;
	cin>>cur->year;
	head->next=cur;
	while(n>=3){
		book *sub=new book;
		cin>>sub->name;
		cin>>sub->year;
		cur->next=sub;
		cur=sub;
		n--;
	}
	cur->next=NULL;
return head;
}
book *addBook(book *head,book *a,int position){
		if(position<=0) return head;
		if(position==1){ // add to the head
			a->next=head;
			head=a;
			return head;
		}
		
		
		int count=2;
		book *temp;
		temp=head;
		while(temp!=NULL){	
			if(count==position){
				a->next=temp->next;
				temp->next=a;
				return head;
			}
			count++;
		
			if(temp->next==NULL){		// position > number of node:   	//the case when no more node exsit			
				temp->next=a;
				return head;
			}
			temp=temp->next;
		}
		delete[] temp;
return head;
}
book *removeBook(book *head,int position){
	if(position<=0) return head;
	
	book *temp=head;
	if(position==1){
		head=head->next;
		delete [] temp->name;
		delete [] temp;
		return head;
	}
	
	while(temp->next!=NULL){
		if(position==2){
			
		}
		position--;
	}
	
return head;
}

void print(book *head)
{
	cout<<"\n";
  while (head != NULL)
  {
    cout << head->name <<" - "<< head->year << endl;
    head = head->next;
  }
}

int main(){
	int n = 0;
 	cout<<"input n:";
 	 cin>>n;
  if (n > 0)
  {
    book *head = createBook(n);

    book *newBook = new book();
    cout<<"input newBook-> name: ";
    cin>>newBook->name;
    cout<<"input newBook-> year: ";
    cin>>newBook->year;
    int position;
    cout<<"input position: ";
    cin >> position;
    head = addBook(head, newBook, position);
    print(head);
  }
	
return 0;
}
