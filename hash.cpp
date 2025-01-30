#include "hash.h"
#include <iostream>
#include <vector>
#include <list>
#include "books.h"
using namespace std;

Hash::Hash() {}

Hash::Hash(int tableSize) : size(tableSize){
    table.resize(size);
}

void Hash::insertHashBook(Books* book, char key){
    int index;
    if(key == 'a'){
        index = hashFunction(book->getAuthor());
        table[index].push_back(book);
    }else{
        int index = hashFunction(book->getTitle());
        table[index].push_back(book);
    }
    //cout << "Inserting book at index: " << index << endl;

}

void Hash::deleteHashBook(const string& title, char key){
    int index;
    index = hashFunction(title);
    auto& bucket = table[index];
    for(auto i = bucket.begin(); i != bucket.end(); ++i){
        if((key == 'a' && (*i)->getAuthor() == title) ||
            (key == 't' && (*i)->getTitle() == title)){
            bucket.erase(i);
            return;
        }
    }
}

Books* Hash::searchHashBook(const string& title, char key){
    int index;
    index = hashFunction(title);
    for(Books* book : table[index]){
        if((key == 'a' && book->getAuthor() == title) ||
            (key == 't' && book->getTitle() == title)){
            return book;
        }
    }
    return NULL;
}

void Hash::displayHashBook(char key){
    if(key == 'a'){
        for(int i = 0; i < size; ++i){
            cout << "Bucket " << i << ": ";
            for(Books* book : table[i]){
                cout << book->getAuthor() << " -> ";
            }
            cout << endl;
        }
    }else{
        for(int i = 0; i < size; ++i){
            cout << "Bucket " << i << ": ";
            for(Books* book : table[i]){
                cout << book->getTitle() << " -> ";
            }
            cout << endl;
        }
    }
}
