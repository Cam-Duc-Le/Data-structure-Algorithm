#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;


class BusSystem {
    //friend class Route; 
    //friend class Trip;
public: 
    class Trip{
        string lp;
        int timeA, timeB;
        bool direction;
        Trip *next ;
        Trip(string Lp, bool Direction, int TimeA, int TimeB){
            this->lp=Lp;
            direction=Direction;
            timeA=TimeA;
            timeB=TimeB;
            next=nullptr;
        }
        friend class BusSystem;
        friend class Route;
    };
    class Route{
        string code; 
        Route *next;
        int numTrip;
        Trip *triphead;
        Route(string Code, Trip *newTrip ){
            numTrip=1;
            triphead=newTrip;
            next=nullptr;
            code=Code;
        };
        friend class Trip;
        friend class BusSystem;
    };
protected:  
    Route *routeHead;
    int tripMaxSize;
    bool setSQ=false;
public:
    // constructor
BusSystem(){ 
        this->tripMaxSize=5;
        this->routeHead=nullptr;
};
    
    // ~destructor
~BusSystem(){
        this->tripMaxSize=0;
        this->setSQ=false;
        Route *pCur= this->routeHead;
        while (pCur)
        {
            Route *temp=nullptr;
            temp=pCur;
            pCur=pCur->next;
            delete [] temp;
        }
        this->routeHead=nullptr;
};
    
    // check if string is numeric or not
bool checkNumeric(string s){
    if (s == "\0"){ //empty string
        return false;
    }
    
    for(unsigned int i=0;i<s.length();i++){  // check if N is int or string 
        if(s[i]<48 || s[i]>57){
            return false;
        }
    }
    return true;
}
    // set method
int SQ(int N){
        if(this->setSQ == true ) return -1;
        this->setSQ=true;
        this->tripMaxSize=N;
    return 1;
};

    // insert method
int INS(string Code, string Lp, bool Direction, int TimeA, int TimeB){
        if(TimeB <= TimeA) return -1;
        Route *rTemp= this->routeHead;
        // 0 route exist 
        if(rTemp == nullptr){ 
            Trip *newTrip=new Trip (Lp, Direction, TimeA, TimeB);
            this->routeHead=new Route(Code,newTrip);
            return this->routeHead->numTrip;
        }
    
        // no trip with same lp on other route
        while(rTemp){ // there some route exist with code
            if(rTemp->code == Code){ // found code 
                if(rTemp->numTrip >= this->tripMaxSize) return -1; //route with full trip
                Trip *tTemp=rTemp->triphead;
                while (tTemp){ // search through the trip from picked route
                            //check  if new trip has same lp with any  trip on other route - not done  
                    if(tTemp->lp == Lp){
                        if((TimeA <= tTemp->timeB && TimeA >= tTemp->timeA) || TimeB < tTemp->timeA ) return -1;
                    }

                            // check if bus on the same route with same timeA
                    if(TimeA == tTemp->timeA){
                        if (Direction != tTemp->direction){
                            Trip *newTrip=new Trip (Lp, Direction, TimeA, TimeB); //create  new one
                            newTrip->next=rTemp->triphead; // add to the front
                            rTemp->triphead=newTrip;    // move triphead to the front
                            rTemp->numTrip++;
                            return  rTemp->numTrip;
                        }
                        return -1; // invalid direcction when timA are equal  
                    } 

                    tTemp=tTemp->next;  
                }
                     //  when no excetional case occur 
                Trip *newTrip=new Trip (Lp, Direction, TimeA, TimeB); // add new one
                newTrip->next=rTemp->triphead; // add to the front
                rTemp->triphead=newTrip;    // move triphead to the front
                rTemp->numTrip++;
                return rTemp->numTrip;   
            }

            rTemp=rTemp->next;
        }
            //  Code has not existed  -> create new route
        Trip *newTrip=new Trip (Lp, Direction, TimeA, TimeB);
        Route *sub= new Route (Code,newTrip);
        sub->next=this->routeHead; // add new route to the front
        this->routeHead=sub;   // move routeHead to the front
        return this->routeHead->numTrip;
};

    // delete method
int DEL(string Code, int TimeA, int TimeB){
    int numDel=0;

        if(TimeA == -1 && TimeB == -1){ // delete all
            Route *rTemp=this->routeHead;
            while(rTemp){
                if(rTemp->code == Code){
                    Trip* tTemp=rTemp->triphead;
                    while(tTemp){
                        Trip *tmp = tTemp;
                        tTemp=tTemp->next;
                        delete tmp;
                        numDel++;
                        rTemp->numTrip --;
                    }
                }
                rTemp=rTemp->next;
            }
            return numDel;
        }
        else if(TimeA != -1 && TimeB == -1){   // delete bus at an exact time
            Route *rTemp=this->routeHead;
            while(rTemp){
                if(rTemp->code == Code){
                    Trip* tTemp=rTemp->triphead;
                    while(tTemp){
                        if(tTemp->timeA == TimeA){   // found trip need to be deleted
                            if(tTemp == rTemp->triphead){   // delete at fisrt position
                                Trip *tmp = tTemp;
                                tTemp=tTemp->next;
                                rTemp->triphead=tTemp;
                                delete tmp;
                                numDel++;
                                rTemp->numTrip--;
                            }
                            else{   // delete somewhere
                                Trip *ptr=rTemp->triphead; 
                                while(ptr->next != tTemp ){ // move ptr to the previous trip of tTemp
                                    ptr=ptr->next;
                                }
                                Trip *tmp = tTemp;
                                ptr->next=tTemp->next;
                                tTemp=tTemp->next; // move tTemp to next postion
                                delete tmp;
                                numDel++;
                                rTemp->numTrip--;
                            }
                        }
                        else{  // when not found trip's timeA = TimeA
                            tTemp=tTemp->next;
                        }
                    }
                }
                rTemp=rTemp->next;
            }
            return numDel;
        }
        else{   // normal case
            if(TimeB <= TimeA) return -1;
            Route *rTemp=this->routeHead;
            while(rTemp){
                if(rTemp->code == Code){ // found code 
                    Trip *tTemp=rTemp->triphead;
                    while (tTemp){ // search through the trip from picked route
                        if((tTemp->timeA >= TimeA) && (tTemp->timeA <= TimeB)){
                                // delete trip at 1st position
                            if(tTemp == rTemp->triphead){
                                Trip *pCur=tTemp;
                                tTemp=tTemp->next;    // move tTemp to next position
                                rTemp->triphead=tTemp;
                                delete pCur;
                                rTemp->numTrip --;
                                numDel ++;
                            }
                            else{
                                    // delete at some where 
                                Trip *ptr=rTemp->triphead; 
                                while(ptr->next != tTemp ){ // move ptr to the previous trip of tTemp
                                    ptr=ptr->next;
                                }
                                Trip *pCur=tTemp;
                                ptr->next = tTemp->next;
                                tTemp=tTemp->next; // move tTemp to next position
                                delete pCur;
                                rTemp->numTrip --;
                                numDel ++;
                            }  
                        } 
                        else{ // trip- which is not in del range 
                            tTemp=tTemp->next;
                        }  
                    }
                } // not found code then continue to search for next route
                rTemp=rTemp->next;
            }
            return numDel;
        }
    return numDel;
};

    // number of trip already started but not finish method
int CS(string Code, int Time, int Direction){
        int numCS=0;
        Route *rTemp=this->routeHead;
        while(rTemp){
            if(rTemp->code == Code){ // found code 
                Trip *tTemp=rTemp->triphead;
                if(rTemp->numTrip == 0) return numCS; // not thing in that route
                if(Direction == 3){  // query not tell anything about case of direction
                    while (tTemp){ // search through the trip from picked route
                        if((tTemp->timeA <= Time) && (tTemp->timeB > Time)){
                            numCS++;
                        }
                        tTemp=tTemp->next;
                    }
                }
                else{     //query exist case of direction
                    while (tTemp){ // search through the trip from picked route
                        if((tTemp->timeA <= Time) && (tTemp->timeB > Time) && (tTemp->direction == Direction)){
                            numCS++;
                        }
                        tTemp=tTemp->next;
                    }
                }
   
            } 
            rTemp=rTemp->next;   // not found code then continue to search for next route
        }
    return numCS;
};

    // number of trip already stopped  method
int CE(string Code, int Time, int Direction){
    int numCE=0;
    Route *rTemp=this->routeHead;
        while(rTemp){
            if(rTemp->code == Code){ // found code 
                Trip *tTemp=rTemp->triphead;
                if(rTemp->numTrip == 0) return numCE;
                if(Direction == 3){  // query not tell anything about case of direction
                    while (tTemp){ // search through the trip from picked route
                        if(( tTemp->timeB < Time)){
                            numCE++;
                        }
                        tTemp=tTemp->next;
                    }
                }
                else{     //query exist case of direction
                    while (tTemp){ // search through the trip from picked route
                        if((tTemp->timeB < Time) && (tTemp->direction == Direction)){
                            numCE++;
                        }
                        tTemp=tTemp->next;
                    }
                }
                
            } 
            rTemp=rTemp->next;   // not found code then continue to search for next route
        }
    return numCE;
};

    // trip with nearest starting time 
string GS(string Code, int Time, int Direction) {
    string result;
    int arr[this->tripMaxSize+1];
    int i=0,min=2147483646,remind=0;
    Route *rTemp=this->routeHead;
        while(rTemp){
            if(rTemp->code == Code){ // found code 
                if(rTemp->numTrip == 0) return "-1";  // invalid case when no trip exist in the route
                Trip *tTemp=rTemp->triphead;
                if(Direction == 3){  // query not tell anything about case of direction
                    while (tTemp){ // search through the trip from picked route
                        if(Time >= tTemp->timeA){
                            arr[i]=Time - tTemp->timeA;
                            if(arr[i] == min){
                                if(tTemp->direction == 0) {
                                    min=arr[i];
                                    remind=i;
                                }
                            }
                            if(arr[i] < min){   //case entirely smaller 
                                min=arr[i];
                                remind=i;    
                            } 
                        }
                        i++;
                        tTemp=tTemp->next;
                    }
                    if (min == 2147483646 ) return "-1";   // none of these trips has valid time 
                }
                else{     //query exist case of direction
                    while (tTemp){ // search through the trip from picked route
                        if(tTemp->direction == Direction){
                            if(Time >= tTemp->timeA){
                                arr[i]=Time - tTemp->timeA;
                                if(arr[i] < min){   //case entirely smaller 
                                    min=arr[i];
                                    remind=i;    
                                } 
                            }  
                        }
                        i++;
                        tTemp=tTemp->next;
                    }
                    if (min == 2147483646 ) return "-1"; // none of these trips has valid time
                }
                break;  // exist while loop to keep rTemp
            } 
            rTemp=rTemp->next;   // not found code then continue to search for next route
        }
    if(rTemp == nullptr) return "-1"; 
    Trip *subTemp=rTemp->triphead;
    while (remind>0){
        subTemp=subTemp->next;
        remind--;
    }
    return subTemp->lp;
};

    // trip with nearest stopping time
string GE(string Code, int Time, int Direction){
    string result;
    int arr[this->tripMaxSize+1];
    int i=0,min=2147483646,remind=0;
    Route *rTemp=this->routeHead;
        while(rTemp){
            if(rTemp->code == Code){ // found code 
                if(rTemp->numTrip == 0) return "-1";  // invalid case when no trip exist in the route
                Trip *tTemp=rTemp->triphead;
                if(Direction == 3){  // query not tell anything about case of direction
                    while (tTemp){ // search through the trip from picked route
                        if(Time >= tTemp->timeB){
                            arr[i]=Time - tTemp->timeB;
                            if(arr[i] == min){
                                if(tTemp->direction == 0) {
                                    min=arr[i];
                                    remind=i;
                                }
                            }
                            if(arr[i] < min){   //case entirely smaller 
                                min=arr[i];
                                remind=i;    
                            }
                        }
                        i++;
                        tTemp=tTemp->next;
                    }
                    if (min == 2147483646 ) return "-1"; // none of these trips has valid time
                }
                else{     //query exist case of direction
                    while (tTemp){ // search through the trip from picked route
                        if(tTemp->direction == Direction){
                            if(Time >= tTemp->timeB){
                                arr[i]=Time - tTemp->timeB;
                                if( arr[i] < min){
                                    min= arr[i];
                                    remind=i;
                                }           
                            }
                        }
                        i++;
                        tTemp=tTemp->next;
                    }
                    if (min == 2147483646 ) return "-1"; // none of these trips has valid time
                }
                break; // exist while loop to keep rTemp
            } 
            rTemp=rTemp->next;   // not found code then continue to search for next route
        }
    if(rTemp == nullptr) return "-1"; 
    Trip *subTemp=rTemp->triphead;
    while (remind>0){
        subTemp=subTemp->next;
        remind--;
    }
    return subTemp->lp;
};

string query(string instruction) {
        // TODO: Your implementation
                         // split string fisrt
             ///////////////////////////////////////////
        // check space character at the end ?
        char tempP[instruction.length()+1]; 
        strcpy(tempP,instruction.c_str());// copy to a temp string fisrt
        if((int)tempP[instruction.length()-1] == 32){ // check if last character is a space or not
            return "-1";
        }
       // check space character at the begining or in the middle
        stringstream sstr(instruction);
        string tok;
        string sub[10];
        int i=0,count =0;   //count how many sub string
        while(std::getline(sstr, tok, ' ')) { // split then copy to token
            if (tok =="\0"){  // case when exist abundant space
                return "-1";
            }
            else{
                sub[i] = tok ; // save to temporary array
                count ++;           
            }  
            i++;
        }

                                    // run query 
        ////////////////////////////////////////////////////////////////////////////////////
        if(sub[0]=="SQ"){
            if(checkNumeric(sub[1]) == false) return "-1";  // invalid instruction where N is not int
            int convertedNum=std::stoi( sub[1] ); // convert "number" from string type to int 
            if (SQ(convertedNum)==1) return"1";
            return "-1";
        }

        else if(sub[0]=="INS"){
            string Code=sub[1];
            string Lp=sub[2];
            bool Direction=0; // ???? direction
            int TimeA,TimeB;
            if(count == 6){   // case when direction provided
                if(std::stoi(sub[3]) == 1 || std::stoi(sub[3]) == 0){    //when input has valid case : 0 or 1
                    if(checkNumeric(sub[4]) == false || checkNumeric(sub[5]) == false) return"-1";   // invalid when time contain word
                        Direction=std::stoi( sub[3] );
                        TimeA=std::stoi( sub[4] );
                        TimeB=std::stoi( sub[5] );
                }
                else{
                    return "-1";
                }
            }
            else{        // case when query not exist direction or direction=0    (when i <=4 )
                if(checkNumeric(sub[3]) == false || checkNumeric(sub[4]) == false)  return"-1";  // invalid when time contain word
                TimeA=std::stoi( sub[3] );
                TimeB=std::stoi( sub[4] );    
            }
            
            int ins=0;
            ins=INS( Code,  Lp,  Direction, TimeA, TimeB );
            string result= std::to_string(ins);
            return result;
        }

        else if(sub[0]=="DEL"){
            string Code=sub[1];
            int del=-1;
            if(checkNumeric(sub[2])==true && checkNumeric(sub[3])==true ){ //exist valid timeA and timeB
                int TimeA=std::stoi( sub[2] );
                int TimeB=std::stoi( sub[3] );
                del=DEL( Code, TimeA, TimeB );
            }
            else if(checkNumeric(sub[2])==true && checkNumeric(sub[3])==false ){ // only exist valid timeA          
                int TimeA=std::stoi( sub[2] );
                del=DEL( Code, TimeA, -1 );
            }
            else if(checkNumeric(sub[2])==false && checkNumeric(sub[3])==false ){ // only exist valid timeA
                del=DEL( Code, -1, -1 );
            }
            
            string result= std::to_string(del);
            return result;
        }

        else if(sub[0]=="CS"){ 
            string Code=sub[1];
            int Direction=3;
            int cs=0;
            if(checkNumeric(sub[2]) == false || count < 3) return "-1";   // check if time  valid ?   -> invalid case
            int Time=std::stoi( sub[2] );   //convert time to int
            if(count == 4){   // case is provided
                if( std::stoi(sub[3]) == 0 || std::stoi(sub[3]) == 1){  // case when direction exist
                    Direction=std::stoi(sub[3]);
                    cs=CS(Code,Time,Direction);
                }
                else{
                    return "-1";
                }
            }
            else{
                cs=CS(Code,Time,Direction);
            }
            string result= std::to_string(cs);
            return result;
        }

        else if(sub[0]=="CE"){
            string Code=sub[1];
            int Direction=3;
            int ce=0;
            if(checkNumeric(sub[2]) == false || count < 3) return "-1";   // check if time ?  and invalid case
            int Time=std::stoi( sub[2] );      //convert time to int
            if(count == 4 ){
                if( std::stoi(sub[3]) == 0 || std::stoi(sub[3]) == 1 ){  // case when direction exist
                    Direction=std::stoi(sub[3]);
                    ce=CE(Code,Time,Direction);
                }
                else{
                    return "-1";
                }
            }
            else{
                ce=CE(Code,Time,Direction);
            }
            string result= std::to_string(ce);
            return result;
        }
       
        else if(sub[0]=="GS"){
            string Code=sub[1];
            int Direction=3;
            if(checkNumeric(sub[2]) == false || count < 3) return "-1";   // check if time < 0 ?   -> invalid case
            int Time=std::stoi( sub[2] );
            if(count == 4){
                if( std::stoi(sub[3]) == 0 || std::stoi(sub[3]) == 1 ){  // case when direction exist
                    Direction=std::stoi(sub[3]);
                    return GS(Code,Time,Direction);
                }
                else{
                    return "-1";
                }
            }
            else{
                return GS(Code,Time,Direction);
            }
        }
       
        else if(sub[0]=="GE"){
            string Code=sub[1];
            int Direction=3;
            if(checkNumeric(sub[2]) == false || count < 3) return "-1";   // check if time valid?   -> invalid case
            int Time=std::stoi( sub[2] );
            if( count == 4){
                if( std::stoi(sub[3]) == 0 || std::stoi(sub[3]) == 1 ){  // case when direction exist
                    Direction=std::stoi(sub[3]);
                    return GE(Code,Time,Direction);
                }
                else{
                    return"-1";
                }
            }
            else{
                return GE(Code,Time,Direction);
            }
        }
        
        else{
            return"-1";
        }
}
};
int main(){
    
    BusSystem* bs = new BusSystem();
    cout << bs->query("SQ 500") << endl;
    cout << bs->query("SQ 5") << endl;
    cout << bs->query("INS 50 50D1-23342 1 1234 5678") << endl;
    cout << bs->query("INS 50 50D1-23343 1 2000 7777") << endl;
    cout << bs->query("INS 50 50D1-23344 1 2500 7777") << endl;
    cout << bs->query("CS 50 2134") << endl;
    cout << bs->query("CE 50 6000 1") << endl;
    cout << bs->query("GS 50 1000 1") << endl;
    cout << bs->query("GE 50 5679") << endl;
    cout << bs->query("DEL 50 2000 5000") << endl;
    //wrong case
    cout<<"\n";
    cout << bs->query("SS 50 2134") << endl;
    cout << bs->query("CE 50 ") << endl;
    cout << bs->query("INS 50 50D1-23342 1 1234 5678") << endl;
    cout << bs->query("INS 50 50D1-23349 4 8234 9678") << endl;
    cout << bs->query("GE 50 5679 5") << endl;
    cout << bs->query("GS 50 5679 4") << endl;
    cout << bs->query("CE 50 5679 9") << endl;
    cout << bs->query("GE 50") << endl;
// case to test runtime
    cout<<"\n"<<"runtime test"<<"\n";
    BusSystem BS;

    clock_t begin = clock();

    ifstream input("test_0.txt");
    ofstream output("test_0.out");

    for (string instruction; getline(input,instruction); ){
        output << BS.query(instruction) << '\n';
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "[*] Execution time: " << elapsed_secs << "s\n";
    
    if (elapsed_secs <= 1.00){
        cout << "[+] You're fast enough. Good job :^\n";
    }
    else{
        cout << "[-] Exceeded runtime limit :(\n";

    }

    input.close();
    output.close();

    return 0;
}