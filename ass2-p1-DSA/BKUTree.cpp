#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class K, class V>
class BKUTree {
public:
    class AVLTree;
    class SplayTree;

    class Entry {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

private:
    AVLTree* avl;
    SplayTree* splay;
    queue<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5) {
        this->maxNumOfKeys = maxNumOfKeys;
        avl = new AVLTree();
        splay = new SplayTree();
    };
    ~BKUTree() { 
        this-> clear();
        delete avl;
        delete splay;
    };
    friend class AVLTree;
    friend class SplayTree;
    // add BKUTree checked
    void add(K key, V value){ 
            Entry *newEntry = new Entry(key,value); // create entry

            typename SplayTree::Node* s = nullptr; // return address of new node
            splay->add(newEntry, s);
            typename AVLTree::Node* a = nullptr;// return address of new node
            avl->add(newEntry, a);
            // linking
            s->corr = a; 
            a->corr = s;

           // push key to queue
            if(keys.size() >= (unsigned int)maxNumOfKeys){    // queue already full
                keys.pop();
                keys.push(key);
            }
            else{ // queue not full 
                keys.push(key);
            }
    };

    void remove(K key){
        splay->remove(key);
        avl->remove(key);
        // delete if key exist in queue
            queue <K> tmpQ;
            while(!keys.empty()){
                if(keys.front() != key) tmpQ.push(keys.front());
                keys.pop();
            }
            keys = tmpQ;
            
            // push root's key to the queue after delete
            if(keys.size() >= (unsigned int)maxNumOfKeys){    // queue already full
                keys.pop();
                keys.push(splay->root->entry->key);
            }
            else{ // queue not full 
                keys.push(splay->root->entry->key);
            } 

    };

    V search(K key, vector<K>& traversedList){
        // 1.
        if(key == splay->root->entry->key) return splay->root->entry->key;
        // 2.
        V result;
        bool b ;
        bool check = false;
        typename AVLTree::Node *tmp;
        queue <K> subQ = keys;
        while(subQ.empty() == false){
            if(subQ.front() == key){ // key already exist
                b = true;
                subQ.pop();
            } 
            else{
                subQ.pop();
            }
        } 
        int opt = 1;
        if(b == true){ // key already in queue
            result = splay->search(key,traversedList,opt);  // 1 for splay 1 time ; 0 for normal splay
           b = false;
        }
        // 3.
        else{ // key not exist in traverselist
            // 3.1 a,b,c
            typename AVLTree::Node *ref = splay->root->corr; //3a
            tmp = avl->search(key, ref, check, traversedList, 0);  // return a pointer// 3b thuc hien tim kiem va tra ve tmp la node chua key
            vector<K> tempV;
            if(check == true){    //3c da~ tim thay thi check la true
              result = splay->search(tmp->corr->entry->key, tempV, opt); //  splay 1 time at corr on splay tree
            }
            else{ //3.1 d e - not found when search = ref 
                typename AVLTree::Node *r = nullptr;
                bool z = false;
                r = avl->search(key, ref, z, traversedList, 1); // tim kiem tren cay avl tong
                // thay doi traversedList 
                result = splay->search(r->corr->entry->key, tempV, opt);
            }
        }
        
        // 4.
        if(keys.size() >= maxNumOfKeys){    // queue already full
            keys.pop();
            keys.push(key);
        }
        else{ // queue not full 
            keys.push(key);
        }

        return result;
    };

    void traverseNLROnAVL(void (*func)(K key, V value)){
        avl->traverseNLR(func);
    };
    void traverseNLROnSplay(void (*func)(K key, V value)){
        splay->traverseNLR(func);
    };

    void clear(){
        splay->clear();
        avl->clear();
        delete splay;
        delete avl;
        avl = nullptr; 
        splay = nullptr;
        while (!keys.empty()) keys.pop();
    };

    void print(){
        if(avl == nullptr && splay == nullptr) cout<<"empty tree"<<'\n';
        cout<<"AVL:"<<'\n';
        avl->print();
        cout<<"Splay"<<'\n';
        splay->print();
    }
    void printKeys(){
        while (!keys.empty()) {
            cout << '\t' << keys.front();
            keys.pop();
        }
        cout << '\n';
    }


    class SplayTree {
    public:
        class Node {
            Entry* entry;
            Node* left;
            Node* right;
            typename AVLTree::Node* corr;

            Node(Entry* entry = NULL, Node* left = NULL, Node* right = NULL) {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->corr = NULL;
            }
            friend class BKUTree;
            friend class SplayTree;
            friend class AVLTree;
        };

    public:
        Node* root;

        SplayTree(): root(NULL) {};
        ~SplayTree() { this->clear(); };
        friend class BKUTree;
        friend class AVLTree;

        Node *rightRotate(Node *root){ //rotate node and modify balance only
            Node *newRoot = root->left;
            root->left = newRoot->right;
            newRoot->right = root;
            return newRoot;
        };

        Node *leftRotate(Node *root){ // rotate node and modify balance only
            Node *newRoot = root->right;
            root->right = newRoot->left;
            newRoot->left = root;
            return newRoot;
        };
        
        Node *splay(Node *root, K key){ // splay 4 cases: ll, lr, rr, rl
            if(root == nullptr ) return root;

            if(key < root->entry->key){ // left case
                if(root->left == nullptr) return root;

                if(key < root->left->entry->key){ // left left -> right rotate
                    root = rightRotate(root); // root now is node's parent
                    root = rightRotate(root);
                }
                else if(key > root->left->entry->key){ // left right
                    if(root->left->right != nullptr){
                        root->left = leftRotate(root->left); // fisrt rotate left 
                        root = rightRotate(root);   // sec rotate right
                    }
                }
            }
            else{ // right case: key > root->entry->key
                if(root->right == nullptr) return root;

                if(key > root->right->entry->key){ //right right case
                    root = leftRotate(root);
                    root = leftRotate(root);
                }
                else if(key < root->right->entry->key){ // right left
                    if(root->right->left != nullptr){
                        root->right = rightRotate(root->right);
                        root = leftRotate(root);
                    } 
                }
            }
            return root;
        };

        // search trong add nhu bst;
        int countSplay ;
        //add splay checked
        Node *add(Node *root, Entry *newEntry, Node *&splayReturn){ 
            // nothing in side root
            if(root == nullptr){  
                root = new Node (newEntry);
                splayReturn = root;
                return root;
            }

            //normal add
            if(newEntry->key > root->entry->key){
                root->right = add(root->right, newEntry, splayReturn);
            }
            else if(newEntry->key < root->entry->key){
                root->left = add(root->left, newEntry, splayReturn);
            }
            else{
                throw ("Duplicate key");
                return root;
            }

            // splay time 
            // case when countSplay = 1 ??
            countSplay ++;
            if(countSplay == 2){
                root = splay(root, newEntry->key);
                countSplay = 0;
            }
            else if(countSplay == 1 && splayReturn == this->root->right){
                root = leftRotate(root);
                countSplay = 0;
            }
            else if(countSplay == 1 && splayReturn == this->root->left){
                root = rightRotate(root);
                countSplay = 0;
            }
            return root;
        };
        void add(K key, V value){ 
            Entry *newEntry = new Entry(key,value);
            Node* splayReturn = nullptr;
            this->root = add(root, newEntry, splayReturn);
        };
        void add(Entry* entry){ 
            Node* splayReturn = nullptr;
            this->root = add(root, entry, splayReturn);
        };
        void add(Entry* entry, Node*& splayReturn){  // splayReturn 
            this->root = add(root, entry, splayReturn);
        };
        
        //remove splay checked
        Node *removeSub;
        Node *remove(Node *root, K key){// change
            if(root == nullptr){// nothing to do
                throw ("Not found");
                return root;
            }

            if(key > root->entry->key) root->right = remove(root->right, key);
            else if(key < root->entry->key) root->left = remove(root->left, key);
            else{ // found key
                if (root->corr == nullptr) delete root->entry;
                else{ 
                    root->corr = nullptr;
                    root->entry = nullptr;
                }
                removeSub = root;
                return root;
            }

            countSplay ++;

            if(countSplay == 2){
                root = splay(root, key);
                countSplay = 0;
            }
            else if(countSplay == 1 && removeSub == this->root->right){
                root = leftRotate(root);
                removeSub = nullptr;
                countSplay = 0;
            }
            else if(countSplay == 1 && removeSub == this->root->left){
                root = rightRotate(root);
                removeSub = nullptr;
                countSplay = 0;
            }
             
            return root;
        };
        void remove(K key){
            this->root = remove(root , key); // splay that node to root
            Node *rTemp = this->root; 
            Node *rTemp2 = this->root->left;
            Node *l = this->root->left;
            Node *r = this->root->right;
            while(rTemp2->right) rTemp2 = rTemp2->right; // max of left sub tree
            // splay max left sub tree  here
            vector<K> v;
            int opt = 0;
            this->root = search(l, rTemp2->entry->key, v, opt);  // normal splay: splay infinity time
            this->root->right = r; // because root now is max key so nothing exist on the right
            delete rTemp;
        };

        // search splay checked
        Node *searchSub;
        V tRes; //for BKU;
        Node *search(Node *root, K key, vector<K>& traversedList, int &opt){
            if(root == nullptr){// nothing to do
                throw ("Not found");
                return root;
            }


            if(key > root->entry->key){
                traversedList.push_back(root->entry->key);
                root->right = search(root->right,key,traversedList,opt);
            }
            else if(key < root->entry->key){
                traversedList.push_back(root->entry->key);
                root->left = search(root->left,key,traversedList,opt);
            } 
            else{ // found key 
                searchSub = root;
                tRes = root->entry->value;
                return root;
            }
// them bien de xac dinh splay 1 lan hay 2
            if(opt == 1){  // after splay 1 time opt = 3 so that there won't be any splay anymore
                countSplay ++;
                if(countSplay == 2){
                    root = splay(root, key);
                    countSplay = 0;
                    searchSub = nullptr;
                    opt = 3;
                }
                else if(countSplay == 1 && searchSub == this->root->right){
                    root = leftRotate(root);
                    searchSub = nullptr;
                    countSplay = 0;
                    opt = 3;
                }
                else if(countSplay == 1 && searchSub == this->root->left){
                    root = rightRotate(root);
                    searchSub = nullptr;
                    countSplay = 0;
                    opt = 3;
                }
            }

            if( opt == 0){ // splay until reach root
                countSplay ++;
                if(countSplay == 2){
                    root = splay(root, key);
                    countSplay = 0;
                }
                else if(countSplay == 1 && searchSub == this->root->right){
                    root = leftRotate(root);
                    searchSub = nullptr;
                    countSplay = 0;
                }
                else if(countSplay == 1 && searchSub == this->root->left){
                    root = rightRotate(root);
                    searchSub = nullptr;
                    countSplay = 0;
                }
            }
            
            // 
            return root;
        };
        V search(K key, vector<K>& traversedList, int &opt){
            this->root = search(root, key, traversedList, opt);
            if(opt == 3) return tRes;
            else{
                if(this->root->entry->key == key) return root->entry->value;
                else throw ("Not found"); 
            }
        };
        V search(K key){ 
            vector<K> traversedList;
            int opt = 0;
            this->root = search(root, key, traversedList, opt);
            if(this->root->entry->key == key) return root->entry->value;
            else throw ("Not found");
        };
        
        //traverse splay checked
        void NLR(Node* _root, void (*func)(K key, V value)){
            if (_root){
                (*func)(_root->entry->key, _root->entry->value);
                NLR(_root->left, func);
                NLR(_root->right, func);
            }
        };
        void traverseNLR(void (*func)(K key, V value)){
            NLR(this->root, func);
        };

        // clear splay checked
        Node *clear(Node *root){
            if(root == nullptr) return root;

            root->left = clear(root->left);
            root->right = clear(root->right);
            delete root->entry;
            delete root;
            root = nullptr;
            return root;
        }
        void clear(){
            this->root= clear(root);
        };
        
        // print only
        void print(){
			prettyPrintTree(root);
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

			cout << prefix + (isLeft ? "└── " : "┌── ") + "<" + to_string(_root->entry->key) + "," + to_string(_root->entry->value) + ">\n";

			if (_root->left) {
				prettyPrintTree(_root->left, prefix + (isLeft ? "    " : "|   "), true);
			}
		}
        
    };

    class AVLTree {
    public:
        class Node {
            Entry* entry;
            Node* left;
            Node* right;
            int balance;
            typename SplayTree::Node* corr;

            Node(Entry* entry = NULL, Node* left = NULL, Node* right = NULL) {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->balance = 0;
                this->corr = NULL;
            }
            friend class BKUTree;
            friend class SplayTree;
            friend class AVLTree;
        };

    public:
        Node* root;

        AVLTree(): root(NULL) {};
        ~AVLTree() { this->clear(); };
        friend class BKUTree;
        friend class SplayTree;

        int getHeightRec(Node *node){ // caculate height of tree
            if (node == nullptr) return 0;
            int lh = this->getHeightRec(node->left);
            int rh = this->getHeightRec(node->right);
            return (lh > rh ? lh : rh) + 1;
        };

        Node *rightRotate(Node *root){ //rotate node and modify balance only
            Node *newRoot = root->left;
            root->left = newRoot->right;
            newRoot->right = root;
            newRoot->balance = getHeightRec(newRoot->left) - getHeightRec(newRoot->right);
            newRoot->right->balance = getHeightRec(newRoot->right->left) - getHeightRec(newRoot->right->right);
            return newRoot;
        };

        Node *leftRotate(Node *root){ // rotate node and modify balance only
            Node *newRoot = root->right;
            root->right = newRoot->left;
            newRoot->left = root;
            newRoot->balance = getHeightRec(newRoot->left) - getHeightRec(newRoot->right);
            newRoot->left->balance = getHeightRec(newRoot->left->left) - getHeightRec(newRoot->left->right);
            return newRoot;
        };

        //add avl checked
        Node *add(Node *root, Entry *newEntry, Node *&avlReturn){
            if(root == nullptr){ // empty tree
                root = new Node (newEntry);
                avlReturn = root;
                return root;
            }
            // traverse to find suitable position for key
            if(newEntry->key < root->entry->key) root->left = add(root->left, newEntry, avlReturn);
            else if(newEntry->key > root->entry->key) root->right = add(root->right, newEntry, avlReturn);
            else  throw ("Duplicate key");
            //
            root->balance = getHeightRec(root->left) - getHeightRec(root->right);
            if(root->balance > 1){  
                if (getHeightRec(root->left->left) >= getHeightRec(root->left->right) ){
                    return rightRotate(root);
                }
                else{
                    root->left = leftRotate(root->left);
                    return rightRotate(root);
                }
            }
            else if(root->balance < -1){ 
                if(getHeightRec(root->right->left) <= getHeightRec(root->right->right) ){
                    return leftRotate(root);
                }
                else{
                    root->right = rightRotate(root->right);
                    return leftRotate(root);
                }
            }

            return root;
        };
        void add(Entry *entry, Node *&avlReturn){// for BKU tree
            this->root = add(root,entry,avlReturn);
        }
        void add(Entry* entry){
            Node *avlReturn = nullptr;
            root = add(root,entry,avlReturn);
        };
        void add(K key, V value){
            Entry *newEntry = new Entry(value,key);
            add(newEntry);
        };

        //remove avl checked
        Node *remove(Node *root, K key){ //  splay delete must also but node value and key to root
            if(root == nullptr) return root;

            if(key < root->entry->key){ root->left = remove(root->left, key);}
            else if(key > root->entry->key){ root->right = remove(root->right, key);}
            else{  // root->entry->key = key
                if(root->left == nullptr){
                    Node *rT = root->right;
                    if (root->corr == nullptr) delete root->entry;
                    else{ 
                        root->corr = nullptr;
                        root->entry = nullptr;
                    }
                    delete root;
                    return rT;
                }
                else if(root->right == nullptr){
                    Node *rT = root->left;
                    if (root->corr == nullptr) delete root->entry;
                    else{ 
                        root->corr = nullptr;
                        root->entry = nullptr;
                    }
                    delete root;
                    return rT;
                }
                else{   // ??????
                    Node *pCur = root->left;
                    while(pCur->right) pCur = pCur->right; // take max of left subtree
                    if(root->corr != nullptr) root->corr->corr = nullptr;
                    Entry *eT = pCur->entry;
                    typename SplayTree::Node *nT = pCur->corr;
                    pCur->corr = root->corr;
                    pCur->entry = root->entry;
                    root->entry = eT;
                    root->corr = nT;
                    if(root->corr != nullptr) root->corr->corr = root;
                    //delete again
                    root->left = remove(root->left, key);
                }
            }

            if(root == nullptr) return root;
            root->balance = getHeightRec(root->left) - getHeightRec(root->right);
            if(root->balance > 1){    // left unbalance
                if (getHeightRec(root->left->left) >= getHeightRec(root->left->right) ){
                    return rightRotate(root);
                }
                else{
                    root->left = leftRotate(root->left);
                    return rightRotate(root);
                }
            }
            else if(root->balance < -1){ // right unbalance
                if(getHeightRec(root->right->left) <= getHeightRec(root->right->right) ){
                    return leftRotate(root);
                }
                else{
                    root->right = rightRotate(root->right);
                    return leftRotate(root);
                }
            }

            return root;
        };
        void remove(K key){
            root = remove(root, key);
        };

        //search avl checked
        Node* search(K key, Node *ref, bool &check, vector<K> &traversedList, int opt){ // finding stage start at ref node// for BKU TREE
            if(root == nullptr){
                check = false;
                throw ("Not found");
                return root;
            };
            Node *p;
            Node *tmp;
            if(opt == 0)  p = ref;
            if(opt == 1){
              p = this->root;
              tmp = ref;
            }
            while(p){
                if(p == tmp){
                    throw ("Not found");
                    return nullptr;
                }
                if(key > p->entry->key){
                    traversedList.push_back(p->entry->key);
                    p = p->right;
                } 
                else if(key < p->entry->key){
                    traversedList.push_back(p->entry->key);
                    p = p->left;
                } 
                else{
                    check = true;
                    return p;
                }
            }
            // when not exist valid node->entry
            check = false;
            return nullptr;
        };
        V search(K key){// ?
            if(root == nullptr) throw ("Not found");

            Node *p = root;
            while(p){
                if(key > p->entry->key) p = p->right;
                else if(key < p->entry->key) p = p->left;
                else{
                    return p->entry->value;
                }
            }
            // when not exist valid node->entry
            throw ("Not found");
        };

        // traverse avl checked
        void NLR(Node* _root, void (*func)(K key, V value)){
            if (_root){
                (*func)(_root->entry->key, _root->entry->value);
                NLR(_root->left, func);
                NLR(_root->right, func);
            }
        };
        void traverseNLR(void (*func)(K key, V value)){
            NLR(this->root, func);
        };

        //clear avl checked
        void clear(Node *&root){
            if(root == nullptr) return;

            clear(root->left);
            clear(root->right);

            delete root->entry;
            root->balance = 0;
            delete root;
            root = nullptr;
        };
        void clear(){
            clear(root);
        };

        
        // test only
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

			cout << prefix + (isLeft ? "└── " : "┌── ") + "<" + to_string(_root->entry->key) + "," + to_string(_root->entry->value) + ">\n";

			if (_root->left) {
				prettyPrintTree(_root->left, prefix + (isLeft ? "    " : "|   "), true);
			}
		}
        
    };
};

                        // Le Duc Cam -1952588 //

int main() {
    /*
    BKUTree<int, int>* tree = new BKUTree<int, int>();
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++) tree->add(keys[i], keys[i]);
    //tree->traverseNLROnAVL(print);
    tree->print();
*/
    BKUTree<int, int>::AVLTree* avltree = new BKUTree<int, int>::AVLTree();
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++) avltree->add(keys[i], keys[i]);
    //tree->traverseNLROnAVL(print);
    avltree->print();
    /*
    BKUTree<int, int>* tree = new BKUTree<int, int>();
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++) tree->add(keys[i], keys[i]);
    tree->traverseNLROnSplay(printKey);
    */



   /*
    BKUTree<int, int>::SplayTree* splaytree = new BKUTree<int, int>::SplayTree();
    int keys1[] = {1, 3, 5, 7, 9, 11, 2 };
    for (int i = 0; i < 7; i++) splaytree->add(keys1[i], keys1[i]);
    //tree->traverseNLROnAVL(print);

    splaytree->print();
    splaytree->search(7);
    splaytree->print();*/
    /*
    cout<<"after remove"<<"\n";
    splaytree->remove(2);
    splaytree->print();
    splaytree->search(5);
    splaytree->print();
    
    splaytree->clear();
     splaytree->print();
    */
    /*
    BKUTree<int, int>* tree = new BKUTree<int, int>();
    int keys[] = {1, 3, 5, 7, 9, 11,2};
    for (int i = 0; i < 7; i++) tree->add(keys[i], keys[i]);
    //tree->traverseNLROnSplay(printKey);
    tree->print();
    cout<<"keys: "<<'\n';
    tree->printKeys();
    //tree->remove(9);
    //tree->print();
     vector<int> traversedList;
    cout<<"search return : "<<tree->search(3,traversedList)<<"\n";
    cout<<"splay after search"<<'\n';
    tree->print();
    cout<<"keys: "<<'\n';
    tree->printKeys();

    */
    /*
    tree->clear();
     tree->print();
    
    */
   return 0;
}