#include <iostream>
using namespace std;

// implement stack using singular linklist
struct Node {
	int data;
	Node *next;
};
class Stack{
	private:
		Node *sNode;
	public:
		Stack(int data);
		~Stack();
		void push(int data);
		bool empty();
		int peak();
		void pop();
		void print();
		
};
Stack::Stack(int data){
	sNode =new Node ();
	sNode->data=data;
	sNode->next=NULL;
}
Stack::~Stack(){
	while(sNode->next)
	{
		Node*temp=sNode;
		sNode=sNode->next;
		delete [] temp;
	}
	delete sNode;
}
void Stack::push(int data){
	Node *temp=new Node();
	temp->data=data;
	temp->next=sNode;
	sNode=temp;
}
bool Stack::empty(){
	if(sNode=='\0') return true;
	return false;
}
void Stack::pop(){
	if(empty()){
		cout<<"not thing to pop"<<'\n';
		return;
	}
	Node *temp=sNode;
	sNode=sNode->next;
	temp->next=NULL;
	delete [] temp;
}
int Stack::peak(){
	return sNode->data;
}
void Stack::print(){
	if (empty()){
		cout<<"empty!"<<'\n';
		return;
	}
	else{
		cout<<"peak's value: "<<sNode->data<<'\n';
		cout<<"our stack: ";
		Node*temp=sNode;
		while(sNode){
			cout<<sNode->data<<"->";
			sNode=sNode->next;
		}
		sNode=temp;
		return;
	}
}

int main(){
	Stack s(27);
	s.pop();
	bool vl=s.empty();
	cout<<vl<<'\n';
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);
	s.print();
	cout<<'\n';
	s.pop();
	s.print();
	vl=s.empty();
	cout<<'\n'<<vl;
return 0;
}
