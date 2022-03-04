#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;

#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList
{
public:
    virtual void add(const T& element) = 0;
    virtual void add(int index, const T& element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(const T& item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, const T& element) = 0;
    virtual int indexOf(const T& item) = 0;
    virtual bool contains(const T& item) = 0;
    virtual string toString() = 0;
};


#endif

// STUDENT ANSWER
#ifndef FRAGMENT_LINKED_LIST
#define FRAGMENT_LINKED_LIST
template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;

protected:
    Node **fragmentPointers;
    int fragmentMaxSize;
    int count;

public:
    
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    virtual ~FragmentLinkedList();
    virtual void add(const T& element); 
    virtual void add(int index, const T& element); 
    virtual T removeAt(int index); 
    virtual bool removeItem(const T& item); 
    virtual bool empty();  
    virtual int size(); 
    virtual void clear(); 
    virtual T get(int index);
    virtual void set(int index, const T& element);
    virtual int indexOf(const T& item);
    virtual bool contains(const T& item);
    virtual string toString();
    Iterator begin(int index = 0);
    Iterator end(int index = -1);

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node *next, Node *prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;
        int index;

    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true);
        Iterator(int fragmentIndex, FragmentLinkedList<T> *pList = 0,  bool begin = true);
        Iterator &operator=(const Iterator &iterator);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        void set(const T& element);
        Iterator &operator++();
        Iterator operator++(int);
    };
};

                     // Le Duc Cam //
                       //1952588//
            ////////////////////////////////
                        //STRAT//

///// fragment LL

// add to the end method 
template <class T>
void FragmentLinkedList <T> :: add(const T &element){
    if(empty() == true){
        Node *nNode =new Node(element,nullptr,nullptr);
        this->fragmentPointers[0]= nNode;
        this->fragmentPointers[1]= nNode;
    }
    else{
        Node *pCur= this->fragmentPointers[0];
        while (pCur->next)
        {
            pCur=pCur->next;
        }
        Node* nNode = new Node(element,nullptr,pCur);
        pCur->next=nNode;
        nNode->prev=pCur;
    }
    this->count ++;
    // re-arange fragment pointer
    int numfrag=0;
    if(this->count % this->fragmentMaxSize == 0){
        numfrag=(this->count  / this->fragmentMaxSize);
    }
    else{
         numfrag=((this->count - (this->count % this->fragmentMaxSize)) / this->fragmentMaxSize) + 1;
    }
    
    //delete[] fragmentPointers;
    Node *pP=this->fragmentPointers[0];
    int k=0;
    this->fragmentPointers=new Node* [numfrag+1];// +1 for last-red pointer
    for (int i = 0; i < this->count; i++){
        if((i % this->fragmentMaxSize) == 0 ){
            this->fragmentPointers[k]=pP;
            k++;
        }
        pP=pP->next;
    }
    this->fragmentPointers[k]=pP;
}

// add to a direct position method
template <class T>
void FragmentLinkedList <T> :: add(int index,const T& element){
    // empty list
    if(empty() == true){
        Node *nNode = new Node (element,nullptr,nullptr);
        this->fragmentPointers[0]= nNode;
        this->fragmentPointers[1]= nNode;
        this->count ++;
        return;
    }
    // list not empty
    if(index <= 0){ // add to the beginning
        Node *nNode =new Node (element,this->fragmentPointers[0],nullptr);
        (this->fragmentPointers[0])->prev = nNode;
        nNode->next=this->fragmentPointers[0];
        this->fragmentPointers[0]= nNode;
    }
    else if (index >= this->count){ // add to the end
        Node *pCur = this->fragmentPointers[0];
        while (pCur->next)
        {
            pCur=pCur->next;
        }
        Node *nNode = new Node(element,nullptr,pCur);
        pCur->next= nNode;

    }
    else{ // add to the middle
        Node *pCur = this->fragmentPointers[0];
        while (index != 0 ) // when index != 0
        {
            pCur=pCur->next;
            index --;
        }
        Node *nNode = new Node (element,pCur,pCur->prev);
        pCur->prev->next= nNode;
        pCur->prev=nNode;
        
    }
    this->count ++;
    // re-arange fragment pointer
    int numfrag=0;
    if(this->count % this->fragmentMaxSize == 0){
        numfrag=(this->count  / this->fragmentMaxSize);
    }
    else{
        numfrag=((this->count - (this->count % this->fragmentMaxSize)) / this->fragmentMaxSize) + 1;
    }
    Node *pP=this->fragmentPointers[0];
    int k=0;
    this->fragmentPointers=new Node* [numfrag+1];// +1 for last-red pointer
    for (int i = 0; i < this->count; i++){
        if((i % this->fragmentMaxSize) == 0 ){
            this->fragmentPointers[k]=pP;
            k++;
        }
        pP=pP->next;
    }
    this->fragmentPointers[k]=pP;
}

//remove at direct index    
template <class T>
T FragmentLinkedList <T> :: removeAt(int index){
    // empty list // invalid index
    if(empty()== true || index < 0 || index +1  > this->count){
       throw out_of_range("The index is out of range!");
    }
    // 
    Node *temp = this->fragmentPointers[0];
    if (index == 0){ // delete at the beginning
        this->fragmentPointers[0]=this->fragmentPointers[0]->next;
        this->fragmentPointers[0]->prev=nullptr;
        temp->next=nullptr;
    }
    else if(index +1 == this->count){ // delete at the end
        while (temp->next)
        {
            temp=temp->next;
        }
        temp->prev->next =nullptr;
        temp->prev = nullptr;
    }
    else { // delete at the middle
        while(index){
            temp=temp->next;
            index --;
        }
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
    }
    this->count--;
    T *sub= new T(temp->data);
    delete [] temp;
     // re-arange fragment pointer
    int numfrag=0;
    if(this->count % this->fragmentMaxSize == 0){
        numfrag=(this->count  / this->fragmentMaxSize);
    }
    else{
        numfrag=((this->count - (this->count % this->fragmentMaxSize)) / this->fragmentMaxSize) + 1;
    }
    Node *pP=this->fragmentPointers[0];
    int k=0;
    this->fragmentPointers=new Node* [numfrag+1];// +1 for last-red pointer
    for (int i = 0; i < this->count; i++){
        if((i % this->fragmentMaxSize) == 0 ){
            this->fragmentPointers[k]=pP;
            k++;
        }
        pP=pP->next;
    }
    this->fragmentPointers[k]=pP;
return (*sub);
} 

// remove Item method
template <class T>
bool FragmentLinkedList <T> :: removeItem(const T &item){
    if(empty()== true){ // notthing to remove
        return false;
    }
    // 
    Node *temp = this->fragmentPointers[0];
    // item at the beginning
    if (item == this->fragmentPointers[0]->data){ 
        this->fragmentPointers[0]=this->fragmentPointers[0]->next;
        this->fragmentPointers[0]->prev=nullptr;
        this->count--;
        delete [] temp;
         // re-arange fragment pointer
         
        int numfrag=0;
        if(this->count % this->fragmentMaxSize == 0){
            numfrag=(this->count  / this->fragmentMaxSize);
        }
        else{
            numfrag=((this->count - (this->count % this->fragmentMaxSize)) / this->fragmentMaxSize) + 1;
        }
        Node *pP=this->fragmentPointers[0];
        int k=0;
        this->fragmentPointers=new Node* [numfrag+1];// +1 for last-red pointer
        for (int i = 0; i < this->count; i++){
            if((i % this->fragmentMaxSize) == 0 ){
                this->fragmentPointers[k]=pP;
                k++;
            }
            pP=pP->next;
        }
         this->fragmentPointers[k]=pP;
        return true;
    }

    // item somewhere 
    
    while (temp->next){
        Node *sub =nullptr;
        if(temp->next!=nullptr){
            if (temp->data==item){
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
                this->count--;
                sub=temp;
            }
        }
        else{ // item at the end
            if (temp->data==item){
                temp->prev->next=nullptr;
                this->count--;
                sub=temp;
            }
            else
            {
                return false;
            }
        }
        temp=temp->next;
        delete [] sub;
    }
    
    delete [] temp;
     // re-arange fragment pointer
   
    int numfrag=0;
    if(this->count % this->fragmentMaxSize == 0){
        numfrag=(this->count  / this->fragmentMaxSize);
    }
    else{
        numfrag=((this->count - (this->count % this->fragmentMaxSize)) / this->fragmentMaxSize) + 1;
    }
    Node *pP=this->fragmentPointers[0];
    int k=0;
    this->fragmentPointers=new Node* [numfrag+1];// +1 for last-red pointer
    for (int i = 0; i < this->count; i++){
        if((i % this->fragmentMaxSize) == 0 ){
            this->fragmentPointers[k]=pP;
            k++;
        }
        pP=pP->next;
    }
    this->fragmentPointers[k]=pP;
    return true;
}

// check empty or not
template <class T>
bool FragmentLinkedList <T> ::  empty(){
    if(this->count==0) return 1;
    return 0;
}

// size method 
template <class T>
int FragmentLinkedList <T> :: size(){
    return this->count;
}

// clear method
template <class T>
void FragmentLinkedList <T> :: clear(){
    this->count=0;
    if(empty()){
        return;
    }
    
    Node *pCur= this->fragmentPointers[0];
    
    while (pCur->next)
    {
        Node *temp = nullptr;
        temp=pCur;
        pCur=pCur->next;
        delete [] temp;
    }
    delete [] pCur;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
}

//get method
template <class T>
T FragmentLinkedList <T>:: get(int index){
    // invalid index
    static T aa;
    if(index < 0 || empty()== true || index >= this->count){
        aa=-1;
        return aa;
    }
    // exist list
    Node *pCur = this->fragmentPointers[0];
    while (index)
    {
        pCur=pCur->next;
        index --;
    }
    return pCur->data;
}

//set method
template <class T>
void FragmentLinkedList <T> :: set(int index, const T &element){
    // invalid case
    if(index < 0 || index >= this->count || empty()){
        return ;
    }
    // normal case
    Node *pCur=this->fragmentPointers[0];
    while (index)
    {
        pCur=pCur->next;
        index--;
    }
    pCur->data= element;
}

// find index of item
template <class T>
int FragmentLinkedList <T> :: indexOf(const T &item){
    if(empty()){
        return -1;
    }
    int index=0;
    Node *pCur=this->fragmentPointers[0];
    while (pCur)
    {
        if(pCur->data == item ){
            return index;
        }
        index ++;
        pCur=pCur->next;
    }
    // not found
    return -1;
}

// check if the list contain item ?
template <class T>
bool FragmentLinkedList <T> :: contains(const T&item){
    if (empty()) {
        return false;
    }
    Node *pCur=this->fragmentPointers[0];
    while (pCur)
    {
        if(pCur->data == item ){
            return true;
        }
        pCur=pCur->next;
    }
    return false;
}

// ~destructor
template <class T>
FragmentLinkedList <T> :: ~FragmentLinkedList(){
    this->count=0;
    if(empty()){
        return;
    }
    Node *pCur= this->fragmentPointers[0];
    while (pCur)
    {
        Node *temp= nullptr;
        temp=pCur;
        pCur=pCur->next;
        delete [] temp;
    }
    this->fragmentPointers=nullptr;
}

// iterator begin --
template <typename T>
typename FragmentLinkedList<T> :: Iterator FragmentLinkedList<T> ::begin(int index){
   int numfrag=0;
    if(this->count % this->fragmentMaxSize == 0){
        numfrag=(this->count  / this->fragmentMaxSize);
    }
    else{
        numfrag=((this->count - (this->count % this->fragmentMaxSize)) / this->fragmentMaxSize) + 1;
    }
    if (index  >= numfrag){
        throw out_of_range("The index is out of range!");
    }
    
    Iterator *temp=new Iterator(index,this,true);
    return *temp;
}

// iterator end -- 
template <typename T>
typename FragmentLinkedList<T> :: Iterator FragmentLinkedList<T> ::end(int index){
    int numfrag=0;
    if(this->count % this->fragmentMaxSize == 0){
        numfrag=(this->count  / this->fragmentMaxSize);
    }
    else{
        numfrag=((this->count - (this->count % this->fragmentMaxSize)) / this->fragmentMaxSize) + 1;
    }
    if (index  >= numfrag){
        throw out_of_range("The index is out of range!");
    }

    Iterator temp(index,this,false);
    return temp;
}



////// ITERATOR

// iterator constructor-1st
template <typename T>
FragmentLinkedList <T> :: Iterator :: Iterator(FragmentLinkedList<T> *pList, bool begin){
    this->pList=pList;
    if(begin==true){
        this->pNode=pList->fragmentPointers[0];
        this->index=0;
    }
    else{
        this->index=pList->size();
        this->pNode=nullptr;
    }
    
}

// iterator constructor-2nd
template <typename T>
FragmentLinkedList <T> :: Iterator :: Iterator(int fragmentIndex ,FragmentLinkedList<T> *pList , bool begin){
    if(begin==true){ // point to the begining of the fragment
        this->pList=pList;
        this->pNode=pList->fragmentPointers[fragmentIndex];
        this->index=fragmentIndex*(pList->fragmentMaxSize);
    }
    else{   //case begin =false;
        this->pList=pList;
        int numfrag=0;
        if(pList->count%pList->fragmentMaxSize == 0){
             numfrag=((pList->count - (pList->count % pList->fragmentMaxSize)) / pList->fragmentMaxSize);
        }
        else{
             numfrag=((pList->count - (pList->count % pList->fragmentMaxSize)) / pList->fragmentMaxSize) +1 ;
        }
        
        if (fragmentIndex  >= numfrag){ // invalid case
            throw out_of_range("The index is out of range!");
        }

        if (fragmentIndex == -1){ // case index=-1 -> point to NULL
            this->pNode=nullptr;
            this->index=pList->size();
        }
        else {  // normal case
            this->pNode=pList->fragmentPointers[fragmentIndex];
            this->index=fragmentIndex*(pList->fragmentMaxSize) ;
            int size=pList->fragmentMaxSize;
            while ((size!=0) && (this->pNode->next)) // case fragment has maxsize
            {
                this->pNode=this->pNode->next;
                size--;
            }
            if(this->pNode->next==nullptr){ // case last fragment is not full-sized
                this->pNode=this->pNode->next;
                this->index=fragmentIndex*(pList->fragmentMaxSize) + (pList->count % pList->fragmentMaxSize) ;
            }
        }
    }

}


// operator =
template <typename T>
typename FragmentLinkedList <T> :: Iterator &FragmentLinkedList<T>::Iterator::operator=(const Iterator &iterator){
    this->pList = iterator.pList;
    this->pNode = iterator.pNode;
    this->index = 0;
    Node *temp=this->pList->fragmentPointers[0];
    while(temp != iterator.pNode){
        temp=temp->next;
        this->index ++;
    }
    return *this;
}

//  operator !=
template <typename T>
bool FragmentLinkedList<T>::Iterator::operator!=(const Iterator &iterator){
	if(this->pNode == iterator.pNode && this->index == iterator.index){
        return false;
    }
    return true;
}

// operator *()
template <typename T>
T &FragmentLinkedList <T> :: Iterator :: operator*(){
    
    if(this->pNode==nullptr){
        throw std::out_of_range("Segmentation fault!");
    }
    return this->pNode->data;
}

// remove method for iterator -- not done -- index ? 
template <typename T>
void FragmentLinkedList <T> :: Iterator :: remove(){
    if (this->pList->empty()){
        return;
    }
    
    if(this->pList->count==1){
        this->pList->count --;
        this->index= -1;
        this->pNode= nullptr;
                //re-arrange
                this->pList->fragmentPointers = new Node *[2];
                this->pList->fragmentPointers[0] = nullptr;
                this->pList->fragmentPointers[1] = nullptr;
        return;
    } 
    else if (this->pNode == this->pList->fragmentPointers[0]){
        this->pList->count --;
        this->index= -1;
        this->pNode=nullptr;
        //re-arrange
        int numfrag=0;
        if(this->pList->count % this->pList->fragmentMaxSize == 0){
            numfrag=(this->pList->count  / this->pList->fragmentMaxSize);
        }
        else{
            numfrag=((this->pList->count - (this->pList->count % this->pList->fragmentMaxSize)) / this->pList->fragmentMaxSize) + 1;
        }
        Node *pP=this->pList->fragmentPointers[0];
        int k=0;
        this->pList->fragmentPointers=new Node* [numfrag+1];// +1 for last-red pointer
        for (int i = 0; i < this->pList->count; i++){
            if((i % this->pList->fragmentMaxSize) == 0 ){
              this->pList->fragmentPointers[k]=pP;
                k++;
            }
            pP=pP->next;
        }
        this->pList->fragmentPointers[k]=pP;

        return;
    }
    else{
        this->pList->count --;
        this->index --;
        this->pNode->prev->next=this->pNode->next;
        this->pNode->next->prev=this->pNode->prev;
        Node *temp= this->pNode;
        this->pNode=this->pNode->prev;
        //re-arrange
        int numfrag=0;
         if(this->pList->count % this->pList->fragmentMaxSize == 0){
            numfrag=(this->pList->count  / this->pList->fragmentMaxSize);
        }
        else{
            numfrag=((this->pList->count - (this->pList->count % this->pList->fragmentMaxSize)) / this->pList->fragmentMaxSize) + 1;
        }
        Node *pP=this->pList->fragmentPointers[0];
        int k=0;
        this->pList->fragmentPointers=new Node* [numfrag+1];// +1 for last-red pointer
        for (int i = 0; i < this->pList->count; i++){
            if((i % this->pList->fragmentMaxSize) == 0 ){
                this->pList->fragmentPointers[k]=pP;
                k++;
            }
            pP=pP->next;
        }
        this->pList->fragmentPointers[k]=pP;
        delete [] temp;
        return;
    }
    return;
}

// set method for iterator
template <typename T>
void FragmentLinkedList <T> :: Iterator :: set(const T &element){
    this->pNode->data= element;
}

// operator ++ (prefix) ex: ++c
template <typename T>
typename FragmentLinkedList <T> :: Iterator &FragmentLinkedList<T>::Iterator::operator++(){
    this->pNode=this->pNode->next;
    this->index++;
    return *this;
}

// operator ++ (postfix) ex: c++
template <typename T>
typename FragmentLinkedList <T> :: Iterator FragmentLinkedList <T> :: Iterator::operator++(int){
    Iterator sub=*this;
    this->pNode=this->pNode->next;
    this->index++;
    
    return sub;
}



// return the list in the form of string
template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->fragmentPointers[0];

    if (this->count == 0)
        ss << "]";

    // TODO
    if(this->count > 0){
        ss << ptr->data;
        while (ptr->next)
        {
            ptr=ptr->next;
            ss <<" - "<<ptr->data;
        }
        ss << "]";
    }
    // END: TODO

    return ss.str();
}

#endif
// END: STUDENT ANSWER

int main()
{
    // TESTCASE INPUT
    // === Example
        
        FragmentLinkedList <int> fList(5);
        for(int i = 0; i < 20 ; i++)
            fList.add(i, i * i);
        //
        string s;
        s=fList.toString();
        cout<<s<<"\n";
        int b=fList.size();
        cout<<"initial size: "<< b <<"\n";
        // check: //begin //end // != // c++ and ++c  // *() // constructure // 
        
        for(FragmentLinkedList<int>::Iterator it = fList.begin(2); it != fList.end(); it++)
            cout << *it << "  *  ";
        cout << '\n';
        
        // not checked
        // check : set // remove // ++i // begin(index) 
        FragmentLinkedList <int> :: Iterator itsub = fList.begin(1);
        itsub.remove();// remove at the beginning -25 
        itsub++; ++itsub;
        itsub.remove();// remove somewhere -49
        itsub.set(27); // 27 replace 36
        for( itsub ; itsub != fList.end(3); ++itsub)
            cout << *itsub << "  ";
        int size=fList.size();
        cout<<" size after delete 2 times: " <<size <<"\n";
        cout << '\n';
      
      
    // === END: Example
    // END: TESTCASE INPUT

/*
    //delcare 
    FragmentLinkedList <int> cc(5);
    string s;
    //
    for(int i=0;i<5;i++) cc.add(1);
    s=cc.toString();
    cout<<s;
    //
    int size=cc.size();
    cout<<"size: "<<size<<'\n';
    //
    bool empty=cc.empty();
   cout<<"empty?: "<<empty<<'\n';
   //
   cc.set(2,3);cc.set(1,2);
   s=cc.toString();
    cout<<s;
   //
   cout<<"\n";
   int index=cc.get(2);
   cout<<"value at index 2: "<<index<<'\n';
   int indexof=cc.indexOf(1);
   cout<<"index of 1: "<<indexof<<'\n';
    bool contain=cc.contains(3);
    cout<<"contain 3? :"<<contain<<'\n';
   //
    cc.removeAt(4);  s=cc.toString();  cout<<s;
    size=cc.size();
    cout<<"size: "<<size<<'\n';
    //
    cc.removeItem(1);  s=cc.toString(); cout<<s;
    size=cc.size();
    cout<<"size: "<<size<<'\n';
    //
    cc.add(2,9);  size=cc.size();   s=cc.toString();
    cout<<s<<"size: "<<size <<'\n';
    cc.add(0,0);  size=cc.size();   s=cc.toString();
    cout<<s<<"size: "<<size<<"\n";
    cc.add(12,7);  size=cc.size();   s=cc.toString();
    cout<<s<<"size: "<<size<<'\n';

    
    // destroy ll
    cc.~FragmentLinkedList();
    size=cc.size();
    cout<<"size after ll destroyed: "<<size<<'\n';
    empty=cc.empty();
    cout<<"empty?: "<<empty<<'\n';
*/
    return 0;
}
