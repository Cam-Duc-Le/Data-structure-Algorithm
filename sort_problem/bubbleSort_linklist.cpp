#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList()
    {
      this->head = NULL;
      this->tail = NULL;
      this->count = 0;
    }
    ~SLinkedList(){};
    void add(T e)
    {
        Node *pNew = new Node(e);

        if (this->count == 0)
        {
            this->head = this->tail = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }

        this->count++;
    }
    int size()
    {
        return this->count;
    }
    void printList()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        cout << ss.str() << endl;
    }
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(T data) {
            this->data = data;
            this->next = NULL;
        }
    };

    void bubbleSort();
};

template <class T>
void SLinkedList<T>::bubbleSort()
{
	Node *temp = this->head;
	T sD;
	int i=0;
	int j=0;
	while(i < (this->size()-1) ){
		while(j < (this->size()-i-1)){
			if(temp->data > temp->next->data){ // swap
				sD = temp->data;
				temp->data = temp->next->data;
				temp->next->data = sD; 	
			}
			j++;
			temp=temp->next;
		}
		this->printList();
		i++;
		j=0;
		temp = this->head;
	}
}

int main(){
	int arr[] = {9, 2, 8, 4, 1};
	SLinkedList<int> list;
	for(int i = 0; i <int(sizeof(arr))/4;i++)
    	list.add(arr[i]);
	list.bubbleSort();
	return 0;
}
