#include <iostream>
using namespace std;

class Node{
    int data;
    Node* next;
public:
    Node(): data(0), next(nullptr){}

    Node(int data, Node* next){
        this->data = data;
        this->next = next;
    }

    int getData(){
        return this->data;
    }

    void setData(int data){
        this->data = data;
    }

    Node* getNext(){
        return this->next;
    }

    void setNext(Node* next){
        this->next = next;
    }
};

void reduceDuplicate(Node*root){
    Node *tmp = root;
    while(tmp->getNext() != nullptr){
        Node *del = tmp->getNext();
        if(tmp->getData() == del->getData()){
            tmp->setNext(del->getNext());
            delete del;
        }
        else{
            tmp=tmp->getNext();
        }
    }
}
void printList(Node *root){
  Node *t = root;
  while(t){
    cout<<t->getData()<<" - ";
    t = t->getNext();
  }
}
int main(){
    Node* node1 = new Node(16, nullptr);
    Node* node2 = new Node(5, node1);
    Node* node3 = new Node(4, node2);
    Node* node4 = new Node(3, node3);
    Node* node5 = new Node(1, node4);
    Node* node6 = new Node(1, node5);
    Node* node7 = new Node(0, node6);
    printList(node7);
    cout<<"\n";
    reduceDuplicate(node7);
    cout<<"after delete:  ";
    printList(node7);
    while(node7){
        Node *t = node7;
        node7 = node7->getNext();
        delete t;
    }
    return 0;
}