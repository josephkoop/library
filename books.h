#ifndef BOOKS_H
#define BOOKS_H
#include <iostream>
#include "hash.h"
using namespace std;

class Hash;

class Books{

private:
    string title;
    string author;
    string genre;   //Could make this a selection list later
    int year;
    int id;
    Books* next;


public:
    static Hash titleHash;
    static Hash authorHash;
    Books();
    Books(Books*&, string, string, string, int, int*);
    string getTitle();
    string getAuthor();
    int getID();
    Books* getNext();
    void addBookInput(Books*&, int*);
    void addBook(Books*&, Books*);
    void deleteBook(Books*&);
    void bookListInput(Books*);
    void bookListTitle(Books*);
    void bookListAuthor(Books*);
    void bookListGenre(Books*);
    void bookListYear(Books*);
    void addBookPopulate(Books*&, int*);

    void insertToHashTable(Books*);
    void deleteFromHashTable(string);
    void searchHashTable();
    void displayHashTable();
};

#endif // BOOKS_H
