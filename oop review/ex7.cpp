#include <iostream>
#include <string.h>
using namespace std;

class Book
{
private:
    char *title;
    char *authors;
    int publishingYear;

public:
    Book()
    {
        /*
         * STUDENT ANSWER
         */
        title=NULL;
        authors=NULL;
        publishingYear=0;
    }

    Book(const char *title, const char *authors, int publishingYear)
    {
        /*
         * STUDENT ANSWER
         */
        this->title=new char [ strlen(title) +1];
        strcpy(this->title, title);
        this->authors=new char[strlen(authors)+1];
        strcpy(this->authors,authors);
        this->publishingYear=publishingYear;
    }

    void setTitle(const char *title){
        this->title=new char[strlen(title)+1];
        strcpy(this-> title,title);
    }

    void setAuthors(const char* authors)
    {
        /*
         * STUDENT ANSWER
         */
        this->authors=new char [strlen(authors)+1];
        strcpy(this->authors,authors);
    }

    void setPublishingYear(int publishingYear)
    {
        /*
         * STUDENT ANSWER
         */
        this->publishingYear=publishingYear;
    }

    char* getTitle() const
    {
        /*
         * STUDENT ANSWER
         */
        return title;
    }

    char* getAuthors() const
    {
        /*
         * STUDENT ANSWER
         */
        return authors;
    }

    int getPublishingYear() const
    {
        /*
         * STUDENT ANSWER
         */
        return publishingYear;
    }

    ~Book()
    {
        /*
         * STUDENT ANSWER
         */
        delete [] this->authors;
        delete [] this->title;
        publishingYear=0;
    }

    friend class Printer;
};
class Printer
{
public:
    static void printBook(const Book book)
    {
        /*
         * STUDENT ANSWER
         */
        cout<<book.getTitle()<<'\n';
         
        char * a;
        a = strtok (book.getAuthors(),",");
        bool b=true;
        while (a)
        {
        	if(b){
        		cout<<a<<'\n';
        		b=false;
			}
        	else{
        		cout<<(a+1)<<'\n';
			}
            a = strtok (NULL, ",");
        }
        
        cout<<book.getPublishingYear();
    }
};
int main(){
   Book book1("Giai tich 1", "Nguyen Dinh Huy, Nguyen Thi Xuan Anh", 2000);
    Printer::printBook(book1);
    cout<<"\n"<<'\n';
    Book book2("Introduction to Algorithms", "Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein", 1990);
    Printer::printBook(book2);

return 0;
}
