#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BusParking{
  public:
    class Interval{
      public:
        int start;
        int end;
    
        Interval(int start = 0, int end = 0) {
            this->start = start;
            this->end = end;
        }
        friend class BusParking;
        friend class Node;
    };
    class Node{
      public:
        Interval *itv;
        Node *left, *right;
        friend class BusParking;
        friend class Interval;
        Node() : itv(NULL), left(NULL), right(NULL) {} ;
        Node(Interval *i) : itv(i), left(NULL), right(NULL) {} ;
        ~Node() {} ;
    };

    Node *root;
    int result = 0;
    vector<Interval> v;
    BusParking() : root(nullptr) {};
    ~BusParking(){};
    friend class Node;
    friend class Interval;

    int getHeightRec(Node *root){
        if (root == NULL) return 0;
        int lh = this->getHeightRec(root->left);
        int rh = this->getHeightRec(root->right);
        return (lh > rh ? lh : rh) + 1;
    }
    
    Node *rightRotate(Node *root){
      Node *newRoot = root->left;
      root->left = newRoot->right;
      newRoot->right = root;
      return newRoot;
    }

    Node *leftRotate(Node *root){
      Node *newRoot = root->right;
      root->right = newRoot->left;
      newRoot->left = root;
      return newRoot;
    }

    Node *insert(Node *root, int s, int t, bool &b){
        if(root == nullptr){
          Interval *newItv = new Interval(s,t);
          root = new Node (newItv);
          b = true;
          return root;
        }

        if(s < root->itv->start) root->left = insert(root->left, s, t, b);
        else if(s > root->itv->start) root->right = insert(root->right, s, t, b);
        else{ 
          if(t < root->itv->end) root->left = insert(root->left, s, t, b);
          else if(t > root->itv->end) root->right = insert(root->right, s, t, b);
          else{
              return root;
          } 
        }

        int rootbalance = getHeightRec(root->left) - getHeightRec(root->right);
        if(rootbalance > 1){  
          if (getHeightRec(root->left->left) >= getHeightRec(root->left->right) ){
            return rightRotate(root);
          }
          else{
              root->left = leftRotate(root->left);
              return rightRotate(root);
          }
        }
        else if(rootbalance < -1){ 
          if(getHeightRec(root->right->left) <= getHeightRec(root->right->right) ){
           return leftRotate(root);
          }
          else{
            root->right = rightRotate(root->right);
            return leftRotate(root);
          }
        }

      return root;
    }  
    void add(int s, int t){
        if(t <= s) return;
        bool b = false;
        this->root = insert(this->root, s, t, b);
        //
        if(b == true){
            v.push_back(Interval(s,t));
            this->result = minP(v);
        }
    }


    Node *remove(Node *root, int s, int t, bool &b){
        if(root == nullptr) return root;

        if(s < root->itv->start) root->left = remove(root->left, s, t, b);
        else if(s > root->itv->start) root->right = remove(root->right, s, t, b);
        else{ 
          if(t < root->itv->end) root->left = remove(root->left, s, t, b);
          else if(t > root->itv->end) root->right = remove(root->right, s, t, b);
          else{
            if(root->left == nullptr){
                Node *rT = root->right;
                delete root->itv;
                delete root;
                b = true;
                return rT;
            }
            else if(root->right == nullptr){
                Node *rT = root->left;
                delete root->itv;
                delete root;
                b = true;
                return rT;
            }
            else{   
                Node *pCur = root->left;
                while(pCur->right) pCur = pCur->right;
                Interval *i = pCur->itv;
                pCur->itv = root->itv;
                root->itv = i;
                root->left = remove(root->left, s, t, b);
            }
          }
        }
        
      

      if(root == nullptr) return root;
      int rootbalance = getHeightRec(root->left) - getHeightRec(root->right);
        if(rootbalance > 1){    // left unbalance
          if (getHeightRec(root->left->left) >= getHeightRec(root->left->right) ){
            return rightRotate(root);
          }
          else{
              root->left = leftRotate(root->left);
              return rightRotate(root);
          }
        }
        else if(rootbalance < -1){ // right unbalance
          if(getHeightRec(root->right->left) <= getHeightRec(root->right->right) ){
            return leftRotate(root);
          }
          else{
            root->right = rightRotate(root->right);
            return leftRotate(root);
          }
        }

      return root;
    }
    void remove(int s, int t){
        if(t <= s) return;
        bool b = false;
        this->root = remove(this->root, s, t, b);
        if(b == true){
            int size = this->v.size();
	        Interval *temp = new Interval[size];
	        for(int i=size-1; i>=0; i--){
		        if((v.back().start != s) || (v.back().end != t)){
			        temp[i] = v.back();
			        v.pop_back();
		        }
		        else{
			        temp[i].start = -1;
			        temp[i]. end = -1;
			        v.pop_back();
		        }
	        }
	        if(!v.empty()) v.pop_back();

	        for(int i = 0; i < size; i++){
		        if(temp[i].start != -1 && temp[i].end != -1){
			        v.push_back(temp[i]);
		        }
	        }
            delete []temp;

            this->result = minP(v);
        }
    }


    int minP(vector<Interval> lInterval) {
    //{{ STUDENT_ANSWER }}
      vector<Interval> sub = lInterval;
      int size = lInterval.size();
      int *sA = new int [size];
      int *eA = new int [size];
      for(int i=size-1; i>=0; i--){
          sA[i] = sub.back().start;
          eA[i] = sub.back().end;
          sub.pop_back();
      }
    
      std::sort(sA, sA+size);
      std::sort(eA, eA+size);
  
      int maxBus = 1, busArrived = 1;
      int s = 1, e = 0;
      while( s<size && e<size){
        if(sA[s] < eA[e]){
            busArrived++;
            if(busArrived > maxBus) maxBus = busArrived;
            s++;
        }
        else{
            busArrived--;
            e++;
        }
      }

      delete [] sA;
      delete [] eA;
      return maxBus;
    };
    int minPark(){
      return result;
    }


    void print(){
			prettyPrintTree(this->root);
			cout << "\n";
		}
		void prettyPrintTree(Node* _root, string prefix = "", bool isLeft = true){
			if (!_root) {
				cout << "Empty tree!\n";
				return;
			}

			if (_root->right) {
				prettyPrintTree(_root->right, prefix + (isLeft ? "|   " : "    "), false);
			}

			cout << prefix + (isLeft ? "------" : "------") + "<" + to_string(_root->itv->start) + "," + to_string(_root->itv->end) + ">\n";

			if (_root->left) {
				prettyPrintTree(_root->left, prefix + (isLeft ? "    " : "|   "), true);
			}
		}
};

int main() {
  BusParking *b = new BusParking();
  b->add(1, 5);
  b->add(1, 6);
  b->add(1, 5);
  b->add(2, 5);
  b->add(5, 7);
  b->add(3, 5);
  b->print();
  cout << b->minPark()<<'\n';
  b->remove(2,5);
  cout << b->minPark()<<'\n';
  delete b;
  return 0;
}
