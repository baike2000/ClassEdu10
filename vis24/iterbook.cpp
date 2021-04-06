#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>

using namespace std;

class Book
{
public:
    string Name;
    Book(string name)
    {
        Name = name;
    }
};

class IBookIterator
{
public:
    virtual bool HasNext() = 0;
    virtual Book* Next() = 0;
};

class IBookNumerable
{
public:
    virtual IBookIterator* CreateNumerator() = 0;
    virtual int Count() = 0;
    virtual Book* Get(int i) = 0;
};

class LibraryNumerator : public IBookIterator
{
    IBookNumerable* aggregate;
    int index = 0;
public:
    LibraryNumerator(IBookNumerable* a)
    {
        aggregate = a;
    }
    bool HasNext()
    {
        return index < aggregate->Count();
    }

    Book* Next()
    {
        return aggregate->Get(index++);
    }
};

class Library : public IBookNumerable
{
private:
    vector<Book*> books;
public:
    Library()
    {
        books = 
        {
            new Book ("Война и мир"),
            new Book ("Отцы и дети"),
            new Book ("Вишневый сад")
        };
    }
    int Count() 
    {
        return books.size(); 
    }

    Book* Get(int index)
    {
        return books[index];
    }
    IBookIterator* CreateNumerator()
    {
        return new LibraryNumerator(this);
    }
};



class Reader
{
public:
    void SeeBooks(Library* library)
    {
        IBookIterator* iterator = library->CreateNumerator();
        while (iterator->HasNext())
        {
            Book* book = iterator->Next();
            cout << book->Name << endl;
        }
    }
};

int main()
{
    Library* library = new Library();
    Reader* reader = new Reader();
    reader->SeeBooks(library);
	return 0;
}