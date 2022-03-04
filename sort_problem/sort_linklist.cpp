#include <iostream>
using namespace std;
struct Node {
	int data;
	Node *next;
};
Node *creatNode(int N){
	
	Node *head =new Node;
	Node *temp=head;
	cin>>head->data;
	if(N==1) {
		head->next=NULL;
		return head;
	}
	while(N != 1){
	    Node *sub=new Node;
	    cin>>sub->data;
	    sub->next=NULL;
		temp->next=sub;
		temp=temp->next;
		N--;
	}
	return head;
}

void printNode(Node *head){
	
	while(head != NULL){
		cout<<head->data<<" - ";
		head=head->next;
	}
}

void swap(Node *head,Node *p){
		
		if(p == head){// swap 2 start node
			Node *temp = new Node; 
			temp=head->next;
			head->next=head->next->next;
			temp->next=head;
			head=temp;
			return ;
		}
		
		Node *n=head;
		while(n->next != p){
				n=n->next;
		}
			Node *temp1= new Node; 
			temp1=n->next; 
			n->next=n->next->next;
			Node *temp2=new Node;
			temp2= n->next->next;
			n->next->next=temp1;
			temp1->next=temp2;

	return ;
}

void bubbleSort(Node *head,int N){
	Node *temp=head;
	while(N){
		while(temp->next != NULL){
			if(temp->data > temp->next->data){
				swap(head,temp);
			} 
			temp=temp->next;
		}
		temp=head;
		N--;
	}
	return;
}

int main(){
	int N;
	cout<<"input N(number of nodes): ";
	cin>>N;
	cout<<'\n';
	cout<<"input data for node: ";
	Node* head=creatNode(N);
	cout<<'\n';
	//head=swap(head,head);
	//Node *test=swap(head,head->next->next->next);
	
	bubbleSort(head,N);
	
	cout<<"LinkList after reoder:   ";
	printNode(head);
	delete[] head;

return 0;
}
