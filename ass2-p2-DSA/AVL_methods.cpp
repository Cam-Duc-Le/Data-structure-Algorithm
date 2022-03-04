#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }
    
    Node *rightRotate(Node *root){
      Node *newRoot = root->pLeft;
      root->pLeft = newRoot->pRight;
      newRoot->pRight = root;
      return newRoot;
    }

    Node *leftRotate(Node *root){
      Node *newRoot = root->pRight;
      root->pRight = newRoot->pLeft;
      newRoot->pLeft = root;
      return newRoot;
    }

    Node *insert(Node *root, T value){
        if(root == nullptr){
          root = new Node (value);
          return root;
        }

        if(value < root->data) root->pLeft = insert(root->pLeft,value);
        else if(value >= root->data) root->pRight = insert(root->pRight,value);
        else{ 
          return root;
        }

        int rootbalance = getHeightRec(root->pLeft) - getHeightRec(root->pRight);
        if(rootbalance > 1){  
          if (getHeightRec(root->pLeft->pLeft) >= getHeightRec(root->pLeft->pRight) ){
            return rightRotate(root);
          }
          else{
              root->pLeft = leftRotate(root->pLeft);
              return rightRotate(root);
          }
        }
        else if(rootbalance < -1){ 
          if(getHeightRec(root->pRight->pLeft) <= getHeightRec(root->pRight->pRight) ){
           return leftRotate(root);
          }
          else{
            root->pRight = rightRotate(root->pRight);
            return leftRotate(root);
          }
        }

      return root;
    }  
    void insert(T value){
        this->root = insert(this->root,value);
    }


    Node *remove(Node *root, T value){
      if(root == nullptr) return root;

      if(value < root->data){ root->pLeft = remove(root->pLeft, value);}
      else if(value > root->data){ root->pRight = remove(root->pRight,value);}
      else{  // root->data = value
        if(root->pLeft == nullptr){
          Node *rT = root->pRight;
          delete root;
          return rT;
        }
        else if(root->pRight == nullptr){
          Node *rT = root->pLeft;
          delete root;
          return rT;
        }
        else{   
          Node *pCur = root->pLeft;
          while(pCur->pRight) pCur = pCur->pRight;
          T vT = pCur->data;
          pCur->data = root->data;
          root->data = vT;
          root->pLeft = remove(root->pLeft, value);
        }
      }

      if(root == nullptr) return root;
      int rootbalance = getHeightRec(root->pLeft) - getHeightRec(root->pRight);
        if(rootbalance > 1){    // left unbalance
          if (getHeightRec(root->pLeft->pLeft) >= getHeightRec(root->pLeft->pRight) ){
            return rightRotate(root);
          }
          else{
              root->pLeft = leftRotate(root->pLeft);
              return rightRotate(root);
          }
        }
        else if(rootbalance < -1){ // right unbalance
          if(getHeightRec(root->pRight->pLeft) <= getHeightRec(root->pRight->pRight) ){
            return leftRotate(root);
          }
          else{
            root->pRight = rightRotate(root->pRight);
            return leftRotate(root);
          }
        }

      return root;
    }
    void remove(const T &value)
    {
      this->root = remove(this->root, value);
    }


    void printInorder(Node *root){
      if(root == nullptr) return;
      printInorder(root->pLeft);
      cout<<root->data<<" ";
      printInorder(root->pRight);
    }
    void printInorder(){
        printInorder(this->root);
    }

    bool search(const T &value){
        if(root == nullptr) return false;
        
        Node *p = root;
        while(p){
          if(value > p->data) p = p->pRight;
          else if(value < p->data) p = p->pLeft;
          else{ //value == data
            return true;
          }
        }
        return false;
    }

    void RemoveAll() { RemoveAll(root); }
    void RemoveAll(Node *&node){
      if (node == nullptr) return;

        RemoveAll(node->pLeft);
        RemoveAll(node->pRight);

        delete node;
      node = nullptr;
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        //int balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main() {
  /*
  AVLTree<int> avl;
  int arr[] = {10,52,98,32,68,92,40,13,42,63};
  for (int i = 0; i < 10; i++){
	  avl.insert(arr[i]);
  }
  avl.printTreeStructure();
  cout<<'\n'<<'\n'<< '\n';
  avl.remove(10);
  avl.printTreeStructure();
*/
  cout<<'\n';
  AVLTree<int> avl1;
    int arr1[] = { 10,52,98,32,68,92,40,13,42,63,99,100 };
    for (int i = 0; i < 12; i++){
        avl1.insert(arr1[i]);
    }
    avl1.printTreeStructure();
    avl1.printInorder();
  cout << endl;
  cout << avl1.search(10)<<'\n';
    for (int i = 11; i >= 0; i--) {
       // avl1.remove(arr1[i]);
    }
    avl1.RemoveAll();
    avl1.printTreeStructure();
  return 0;
}
