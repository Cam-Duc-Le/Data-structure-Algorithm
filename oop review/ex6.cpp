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

    friend bool checkAuthor(Book book, const char* author)
    {
        /*
         * STUDENT ANSWER
         * TODO: returns true if the author is on the book's authors list, otherwise it returns false
         */
        char * a;
        a = strtok (book.getAuthors(),",");
        if(strcmp(author,a)==0){
            		return true;
        }
        while (a)
        {
			if(strcmp(author,a+1)==0){
               	return true;
           	}  	
            a = strtok (NULL, ",");
        }
        return false;
    }
};

int main(){
    Book book1("Giai tich 1","Nguyen Dinh Huy, Nguyen Thi Xuan Anh",2000);
    cout << checkAuthor(book1,"Nguyen Thi Xuan Anh")<<'\n';
    Book book2("Giai tich 1","Nguyen Dinh Huy, Nguyen Thi Xuan Anh",2000);
    cout << checkAuthor(book2,"Nguyen Dinh Huy");

return 0;
}
