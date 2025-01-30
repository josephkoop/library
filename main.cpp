#include <iostream>
#include <vector>
#include "books.h"
#include "hash.h"
#include "history.h"
using namespace std;

int main()
{
    int id = 0;
    int* idp = &id;

    Books b;
    Books* head = NULL;

    int id2 = 0;
    int* idp2 = &id2;

    History h;
    History* head2 = NULL;


    b.addBookPopulate(head, idp);

    int decision;
    cout << "Welcome to the library!" << endl;
    while(decision != 0){
        cout << "What would you like to do? Press 1 to to view possible actions. ";
        cin >> decision;
        if(decision == 1){
            cout << "View book list = 2, Search for a book = 3, "
                    "Add a book = 4, Delete a book = 5, "
                    "Borrow a Book = 6, Return a book = 7, "
                    "Display record history = 8, Exit Program = 0.";
            cin >> decision;
        }
        //system("cls");
        switch (decision){
        case 2:
            b.bookListInput(head);
            break;
        case 3:
            b.searchHashTable();
            break;
        case 4:
            b.addBookInput(head, idp);
            break;
        case 5:
            b.deleteBook(head);
            break;
        case 6:
            h.addRecord(head2, head, idp2);
            break;
        case 7:
            h.returnBook(head2);
            break;
        case 8:
            h.displayHistory(head2, head);
            break;
        case 9:
            b.displayHashTable();
        }
    }

    return 0;
}
