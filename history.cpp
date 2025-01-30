#include "history.h"
#include "books.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <list>
#include <vector>
using namespace std;

History::History() {}

vector<list<string>> History::reservations;

void History::addRecord(History*& head2, Books* booksHead, int* idp2){  //Could create deletion method later
    string customerName;
    cout << "Enter customer name: ";
    cin >> customerName;
    History* newRecord = new History();
    cout << "Enter the book ID: ";
    cin >> newRecord->bid;

    Books* current = booksHead;
    int check0 = -1;
    while(check0 != 0){
        check0 = 0;
        current = booksHead;
        while(current->getID() != newRecord->bid && current != NULL){
            current = current->getNext();
        }
        if(current == NULL){
            cout << "Invalid book ID. Please enter a valid book ID: ";
            cin >> newRecord->bid;
            check0 = -1;
            continue;
        }
    }
    if(!reservations[newRecord->bid].empty()){
        string frontName = reservations[newRecord->bid].front();
        char decision;
        if(customerName != frontName){
            cout << "Book is on the waiting list. Would you like to be added to the waiting list? (Y or N): ";
            cin >> decision;
            if(decision == 'y' || decision == 'Y'){
                reservations[newRecord->bid].push_back(customerName);
            }
            delete newRecord;
            return;
        }
    }else{
        reservations[newRecord->bid].push_back(customerName);
    }


    cout << "Enter the borrow date (DDMMYYYY): ";
    string dateInput;
    cin >> dateInput;

    int check1 = -1;
    int check2 = -1;
    int check3 = -1;
    while(check1 != 0 || check2 != 0 || check3 != 0){
        check1 = 0;
        check2 = 0;
        check3 = 0;
        if(dateInput.length() != 8){
            cout << "Invalid input. Please enter exactly 8 digits (DDMMYYYY): ";
            cin >> dateInput;
            check1 = -1;
            continue;
        }
        for(char c : dateInput){
            if(!isdigit(c)){
                cout << "Invalid input. Enter digits only (DDMMYYYY): ";
                cin >> dateInput;
                check2 = -1;
                break;
            }
        }
        int day = (dateInput[0] - '0') * 10 + (dateInput[1] - '0');
        int month = (dateInput[2] - '0') * 10 + (dateInput[3] - '0');
        int century = (dateInput[4] - '0') * 10 + (dateInput[5] - '0');
        int year = (dateInput[6] - '0') * 10 + (dateInput[7] - '0');
        if(day > 31 || day < 1 || month > 12 || month < 1 || century != 20 || year < 24 || year > 25){
            cout << "Invalid input. Ensure date range is correct (DDMMYYYY): ";
            cin >> dateInput;
            check3 = -1;
        }
    }

    for(int i = 0; i < 8; ++i){
        newRecord->dateBorrowed[i] = dateInput[i] - '0';
    }

    for(int i = 0; i < 8; ++i){
        newRecord->dateReturned[i] = 0;
    }
    newRecord->hid = ++(*idp2);
    newRecord->next = head2;
    head2 = newRecord;
}

void History::returnBook(History* head2){       //This does allow you to overwrite a previous return date
    int enterID;
    cout << "Enter record ID: ";
    cin >> enterID;

    int check0 = -1;
    while(check0 != 0){
        check0 = 0;
        while(head2 != NULL && head2->hid != enterID){
            head2 = head2->next;
        }
        if(head2 == NULL){          //Entering a decimal causes an infinite loop
            cout << "Please enter valid record ID: ";
            cin >> enterID;
            check0 = -1;
        }
    }
    cout << "Enter return date: (DDMMYYYY)";
    string dateInput;
    cin >> dateInput;

    int check1 = -1;
    int check2 = -1;
    int check3 = -1;
    while(check1 != 0 || check2 != 0 || check3 != 0){
        check1 = 0;
        check2 = 0;
        check3 = 0;
        if(dateInput.length() != 8){
            cout << "Invalid input. Please enter exactly 8 digits (DDMMYYYY): ";
            check1 = -1;
            cin >> dateInput;
            continue;
        }
        for(char c : dateInput){
            if(!isdigit(c)){
                cout << "Invalid input. Enter digits only (DDMMYYYY): ";
                check2 = -1;
                cin >> dateInput;
                continue;
            }
        }
        int day = (dateInput[0] - '0') * 10 + (dateInput[1] - '0');
        int month = (dateInput[2] - '0') * 10 + (dateInput[3] - '0');
        int century = (dateInput[4] - '0') * 10 + (dateInput[5] - '0');
        int year = (dateInput[6] - '0') * 10 + (dateInput[7] - '0');
        if(day > 31 || day < 1 || month > 12 || month < 1 || century != 20 || year < 24 || year > 25){
            cout << "Invalid input. Ensure date range is correct (DDMMYYYY): ";
            check3 = -1;
            cin >> dateInput;
        }
    }

    for(int i = 0; i < 8; ++i){
        head2->dateReturned[i] = dateInput[i] - '0';
    }

    int day1 = head2->dateBorrowed[0] * 10 + head2->dateBorrowed[1];
    int month1 = head2->dateBorrowed[2] * 10 + head2->dateBorrowed[3];
    int year1 = head2->dateBorrowed[4] * 1000 + head2->dateBorrowed[5] * 100 + head2->dateBorrowed[6] * 10 + head2->dateBorrowed[7];

    int day2 = head2->dateReturned[0] * 10 + head2->dateReturned[1];
    int month2 = head2->dateReturned[2] * 10 + head2->dateReturned[3];
    int year2 = head2->dateReturned[4] * 1000 + head2->dateReturned[5] * 100 + head2->dateReturned[6] * 10 + head2->dateReturned[7];

    tm tm1 = {};
    tm1.tm_mday = day1;
    tm1.tm_mon = month1 - 1;
    tm1.tm_year = year1 - 1900;

    tm tm2 = {};
    tm2.tm_mday = day2;
    tm2.tm_mon = month2 - 1;
    tm2.tm_year = year2 - 1900;

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    if(time1 == -1 || time2 == -1){
        cout << "Error calculating date difference." << endl;
        return;
    }

    double differenceInSeconds = difftime(time2, time1);
    int differenceInDays = differenceInSeconds / (60 * 60 * 24);

    float lateFee;
    int overdue = max(0, differenceInDays - 14);
    lateFee = min(overdue, 21) * 0.25;

    char confirmation;
    cout << "The cost is $3.00 for the book and $"
         << lateFee << " in late fees. Confirm payment received by pressing P.";
    cin >> confirmation;

    reservations[head2->bid].pop_front();
}

void History::displayHistory(History* head2, Books* booksHead){  //Here we can use other functions without making objects. Maybe try this approach for hash class.
    while(head2 != NULL){
        int currentBid = head2->bid;
        string bookTitle = "Unknown Title";
        Books* currentBook = booksHead;
        while(currentBook != NULL){
            if(currentBook->getID() == currentBid){
                bookTitle = currentBook->getTitle();
                break;
            }
            currentBook = currentBook->getNext();
        }
        cout << endl << "Record ID: " << head2->hid << endl << "Book ID: " << currentBid << endl
            << "Title: " << bookTitle << endl << "Date Borrowed: ";

        for(int i = 0; i < 8; ++i){
            cout << head2->dateBorrowed[i];
        }

        cout << endl << "Date Returned: ";
        for(int i = 0; i < 8; ++i){
            cout << head2->dateReturned[i];
        }
        cout << endl;

        head2 = head2->next;
    }
}
