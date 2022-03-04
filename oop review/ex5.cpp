#include <iostream>
#include <string.h>
using namespace std;

class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;

public:
    Book()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero publishingYear and null pointer
         */
        publishingYear=0;
        title=NULL;
        authors=NULL;
    }

    Book(const char* title, const char* authors, int publishingYear)
    {
        /*
         * STUDENT ANSWER
         */
        int size=strlen(title);
        this->title=new char [size+1];
        strcpy(this->title,title);
        size=strlen(authors);
        this->authors=new char [size+1];
        strcpy(this->authors,authors);
        this->publishingYear=publishingYear;
    }

    Book(const Book &book)
    {
        /*
         * STUDENT ANSWER
         * TODO: deep copy constructor
         */
        int size=strlen(book.getTitle() );
        this->title=new char [size+1];
        strcpy(this->title,book.getTitle() );
        size=strlen(book.getAuthors());
        this->authors=new char [size+1];
        strcpy(this->authors,book.getAuthors() );
        this->publishingYear=book.getPublishingYear();
    }
    
    void setTitle(const char* title)
    {
        /*
         * STUDENT ANSWER
         */
        int size=strlen(title);
        this->title=new char [size+1];
        strcpy(this->title,title);
    }
    

    void setAuthors(const char* authors)
    {
        /*
         * STUDENT ANSWER
         */
        int size=strlen(authors);
        this->authors=new char [size+1];
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
        delete [] title;
        delete [] authors;
        publishingYear = 0;
    }

    void printBook(){
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
};
int main(){
    /*Book book1("Giai tich 1","Nguyen Dinh Huy",2000);
    book1.printBook();
    cout<<'\n'<<'\n';*/
    Book book1("Giai tich 1","Nguyen Dinh Huy",2000);
    Book book2 = book1;
    book2.printBook();
return 0;
}
