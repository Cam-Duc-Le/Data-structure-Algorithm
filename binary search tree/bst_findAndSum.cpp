#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node* root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    Node* addRec(Node* root, T value);
    Node *add(Node *root, T value){
        if(root == nullptr){    // nothing on the tree - ending condition
            root = new Node(value);
            return root;
        }

        if(value > root->value){   // >    => traverse to the right
            root->pRight = add(root->pRight, value);
        }
        else{  //  <=    => traverse to the left
            root->pLeft = add(root->pLeft, value);
        }
        return root;
    }    

    void add(T value){
        //TODO
        this->root = add(root,value);
        return;
    }

    // STUDENT ANSWER BEGIN
    bool f = 0;
    void find(Node *root,T i){
        if(root == nullptr) return;
        if(root->value == i){
            f = 1;
            return;
        } 
        if(root->pLeft) find(root->pLeft,i);
        if(root->pRight) find(root->pRight,i);
        return;
    }
    bool find(T i) {
    // TODO: return true if value i is in the tree; otherwise, return false.
        find(this->root,i);
        return f;
    }

    T s = 0;
    void sum(Node* root, T l, T r){
        if(root == nullptr) return;
        if(root->value <= r && root->value >= l){
            s += root->value;
        }
        if(root->pLeft) sum(root->pLeft,l,r);
        if(root->pRight) sum(root->pRight,l,r);
        return;
    }
    T sum(T l, T r) {
    // TODO: return the sum of all element in the tree has value in range [l,r].
        sum(this->root,l,r);
        return s;
    }
    // STUDENT ANSWER END
};

int main(){
    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i) {
        bst.add(i);
    }
    cout << bst.find(7) << endl;
    cout << bst.sum(0, 4) << endl;
    return 0;
}