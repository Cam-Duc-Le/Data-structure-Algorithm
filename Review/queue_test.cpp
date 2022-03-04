#include <iostream>
using namespace std;
class queue{
	private:
		 int nE,cap;
		int front;
		int *arr;
	public:
		queue();
		queue(int *array,int cap);
		~queue();
		void enqueue(int element);
		void dequeue();
		bool empty();
		bool full();
		void print();
};

queue::queue(){
	this->front=0;
	this->cap=10;
	this->nE=0;
	this->arr=new int [10];
}
queue::queue(int *array,int cap){
	this->cap=cap;
	this->arr=new int[cap];
	int i=0;
	this->nE=0;
	while( array[i]!='\0' && (this->nE < cap) )
	{
		this->arr[i]=array[i];
		nE++;
		i++;
	}
	this->front =0;
	cout<<"nE:" <<nE<<"\n";
}
queue::~queue(){
	this->front=0;
	this->nE=0;
	this->cap=0;
	delete [] this->arr;
	this->arr=NULL;
}
bool queue::empty(){
	if (nE==0) return true;
	return false;
}
bool queue::full(){
	if (nE==cap) return true;
	return false;
}
void queue::enqueue(int element){
	if(full()==true){
		cout<<"queue already full!"<<'\n';
		return;
	}
	this->arr[nE]=element;
	nE++;	
	return;
}
void queue::dequeue(){
	if(empty()==true){
		cout<<"empty queue => can't dequeue"<<"\n";
		return;
	}
	this->nE --;
	arr[front]=0;
	this->front++;
	cout<<"dequeued nE:"<<nE<<'\n';
	return;
}
void queue::print(){
	int temp=this->nE;
	int i=this->front;
	while(temp!=0 && i<nE)
	{
		cout<<arr[i]<<"  ";
		temp--;
		i++;
	}
	return;
}

int main(){
	int arr[]={1,2,3};
	queue q(arr,10);
	q.print();
	cout<<'\n';
	q.dequeue();
	
	q.enqueue(27);
	q.enqueue(21);
	q.enqueue(27);
	q.enqueue(27);
	q.enqueue(72);
	
	q.print();
return 0;
}
