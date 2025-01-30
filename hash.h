#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "books.h"
using namespace std;

class Books;

class Hash{
private:
    vector<list<Books*>> table;
    const int size = 19;

    int hashFunction(const string& title) const{
        int hash = 0;
        for(char ch : title){
            hash += ch;
        }
        return hash % size;
    }
public:
    Hash();
    Hash(int);
    void insertHashBook(Books*, char);
    void deleteHashBook(const string&, char);
    Books* searchHashBook(const string&, char);
    void displayHashBook(char);
};

#endif // HASH_H
