#ifndef HISTORY_H
#define HISTORY_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "books.h"
using namespace std;

class History{

private:
    int hid;
    int bid;
    int dateBorrowed[8];
    int dateReturned[8];
    History* next;
public:
    static vector<list<string>> reservations;
    void addRecord(History*&, Books*, int*);
    void returnBook(History*);
    void displayHistory(History*, Books*);
    History();
};

#endif // HISTORY_H
