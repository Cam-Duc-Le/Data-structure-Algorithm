#include <iostream>
using namespace std;

class Node{
    int data;
    Node* left;
    Node* right;
public:
    Node(): data(0), left(nullptr), right(nullptr){}

    Node(int data, Node* left, Node* right){
        this->data = data;
        this->left = left;
        this->right = right;
    }

    int getData(){
        return this->data;
    }

    void setData(int data){
        this->data = data;
    }

    Node* getLeft(){
        return this->left;
    }

    void setLeft(Node* left){
        this->left = left;
    }

     Node* getRight(){
        return this->right;
    }

    void setRight(Node* right){
        this->right = right;
    }
};

void traverse(Node *root, int &max, int &min){
    if(root == nullptr) return ;

    if(root->getLeft()) traverse(root->getLeft(),max,min);
    if(root->getRight()) traverse(root->getRight(),max,min);
    if(root->getData() > max ) max = root->getData();
    if(root->getData() < min ) min = root->getData();
    return ;
}
int findS(Node* root){
    int min = root->getData();
    int max = root->getData();
    traverse(root,min,max);
    return abs(max - min);
}


int main(){
    Node* node1 = new Node(5, nullptr, nullptr);
    Node* node2 = new Node(2, nullptr, nullptr);
    Node* root = new Node(7, node1, node2);
    cout << findS(root);

    return 0;
}