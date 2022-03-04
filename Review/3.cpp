#include <iostream>
#include <queue>
#include <string.h>
#include <map>
#include <set>
using namespace std;
class PrinterQueue{
    // your attributes
    
public:
    PrinterQueue(){};
    priority_queue<int> pq;
    pair <int,string> p;
    vector<pair<int,string>> v;
    void addNewRequest(int priority, string fileName){
        pq.push(priority);
        p= make_pair(priority,fileName);
        v.push_back(p);
    }


    void print(){
        if(!pq.empty()){
            for(auto it = v.begin(); it != v.end(); it++){
                if(it->first == pq.top()){
                    cout<<pq.top()<<"  "<<it->second<<'\n';
                    pq.pop();
                    v.erase(it);
                    break;
                }
            }
        }
        else{
            cout<<"No file to print"<<"\n";
        }
    }
};

int main(){
    PrinterQueue* myPrinterQueue = new PrinterQueue();
    myPrinterQueue->addNewRequest(1, "hello.pdf");
    // myPrinterQueue->print();
    // myPrinterQueue->print();
    myPrinterQueue->addNewRequest(2, "goodbye.pdf");
    myPrinterQueue->addNewRequest(2, "goodnight.pdf");
    myPrinterQueue->print();
    myPrinterQueue->print();
    myPrinterQueue->print();
    delete myPrinterQueue;
    return 0;
}