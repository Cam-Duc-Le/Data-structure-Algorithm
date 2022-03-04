#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
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

    //Helping function
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

    Node *deleteNode(Node *&root, T value){
        if( root == nullptr) return root; // empty tree  or not found value

        if(value > root->value){   // >    => traverse to the right
            root->pRight=deleteNode(root->pRight, value);
        }
        else if(value < root->value){  //  <    => traverse to the left
            root->pLeft=deleteNode(root->pLeft, value);
        }
        else{   // found  value
            // only one child or none child
            if (root->pLeft == nullptr) {
                Node *temp = root->pRight;
                delete root;
                return temp;
            }
            else if (root->pRight == nullptr) {
                Node* temp = root->pLeft;
                delete root;
                return temp;
            }
            else{  // node with 2 children
                Node *pCur = root->pRight;
                while(pCur->pLeft){
                    pCur = pCur->pLeft;
                }
                root->value = pCur->value;
                root->pRight = deleteNode(root->pRight, pCur->value);
            }
        }
        return root;
    }
   
    void deleteNode(T value){
        //TODO
        this->root = deleteNode(root,value);
        return;
    }
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }
    
    string inOrder(){
        return inOrderRec(this->root);
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
};


int main(){
	BinarySearchTree<int> bst;
	bst.add(9);	
	bst.add(2);
	bst.add(10);
	bst.add(8);
	cout << bst.inOrder()<<endl;	
	bst.add(11);
	bst.deleteNode(9);
	cout << bst.inOrder();
	
	
	return 0;
}
