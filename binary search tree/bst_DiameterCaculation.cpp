#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = (int)posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }

    //Helping functions
    /* Function to find height of a tree */
int height(Node* root, int& ans) { 
    if (root == NULL) return 0; 
  
    int left_height = height(root->pLeft, ans); 
    int right_height = height(root->pRight, ans); 
  
    // update the answer, because diameter of a 
    // tree is nothing but maximum value of 
    // (left_height + right_height + 1) for each node 
    ans = max(ans, 1 + left_height + right_height); 
  
    return 1 + max(left_height, right_height); 
} 
  
/* Computes the diameter of binary tree with given root. */
int diameter(Node* root) { 
    if (root == NULL)  return 0; 
    int ans = 0; // This will store the final answer 
    int height_of_tree = height(root, ans); 
    return ans; 
}

    int getDiameter(){
        return diameter(root);
    }
};

int main(){
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("",1, 4);
    binaryTree.addNode("L",2, 6);
    binaryTree.addNode("R",3, 9);
    binaryTree.addNode("LL",4, 10);
    cout << binaryTree.getDiameter();   

    return 0;
}