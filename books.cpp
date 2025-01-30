#include "books.h"
#include "history.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

Books::Books(){};

Books::Books(Books*& head, string title2, string author2, string genre2, int year2, int* idp){
    Books* newBook = new Books();
    newBook->title = title2;
    newBook->author = author2;
    newBook->genre = genre2;
    newBook->year = year2;
    newBook->next = NULL;
    newBook->id = ++(*idp);
    addBook(head, newBook);
}

Hash Books::titleHash(19);
Hash Books::authorHash(19);

string Books::getTitle(){
    return title;
}

string Books::getAuthor(){
    return author;
}

int Books::getID(){
    return id;
}

Books* Books::getNext(){
    return next;
}

void Books::bookListInput(Books* head){
    cout << "Would you like to view by title(t), author (a), genre (g), or year (y): ";
    char decision = 'T';
    cin >> decision;
    switch (decision){
    case 'a':
    case 'A':
        bookListAuthor(head);
        break;
    case 'g':
    case 'G':
        bookListGenre(head);
        break;
    case 'y':
    case 'Y':
        bookListYear(head);
        break;
    default:
        bookListTitle(head);
    }
}

void Books::bookListTitle(Books* head){
    cout << endl;
    Books* current = head;
    while (current != NULL) {
        cout << endl << "Book ID: " << current->id << endl
             << "Title: " << current->title << endl << "Author: "
             << current->author << endl << "Genre: " << current->genre
             << endl << "Year: " << current->year << endl;
        current = current->next;
    }
    cout << endl;
}

void Books::bookListAuthor(Books* head){
    vector<Books*> reorder;
    Books* current = head;
    while(current){
        reorder.push_back(current);
        current = current->next;
    }
    sort(reorder.begin(), reorder.end(), [](Books* a, Books* b){
        return a->author < b->author;
    });
    for(const auto& book : reorder){
        cout << endl << "Book ID: " << book->id << endl
             << "Author: " << book->author << endl << "Title: "
             << book->title << endl << "Genre: " << book->genre
             << endl << "Year: " << book->year << endl;
    }
}

void Books::bookListGenre(Books* head){
    vector<Books*> reorder;
    Books* current = head;
    while(current){
        reorder.push_back(current);
        current = current->next;
    }
    sort(reorder.begin(), reorder.end(), [](Books* a, Books* b){
        return a->genre < b->genre;
    });
    for(const auto& book : reorder){
        cout << endl << "Book ID: " << book->id << endl
             << "Genre: " << book->genre << endl << "Title: "
             << book->title << endl << "Author: " << book->author
             << endl << "Year: " << book->year << endl;
    }
}

void Books::bookListYear(Books* head){
    vector<Books*> reorder;
    Books* current = head;
    while(current){
        reorder.push_back(current);
        current = current->next;
    }
    sort(reorder.begin(), reorder.end(), [](Books* a, Books* b){
        return a->year < b->year;
    });
    for(const auto& book : reorder){
        cout << endl << "Book ID: " << book->id << endl
             << "Year: " << book->year << endl << "Title: "
             << book->title << endl << "Author: " << book->author
             << endl << "Genre: " << book->genre << endl;
    }
}

void Books::addBookInput(Books*& head, int* idp){
    string title3, author3, genre3;
    int year3;
    cout << endl << "Enter book title: ";
    cin.ignore();
    getline(cin, title3);
    cout << "Enter book author: ";
    getline(cin, author3);
    cout << "Enter book genre: ";
    getline(cin, genre3);
    cout << "Enter book year: ";
    cin >> year3;
    Books(head, title3, author3, genre3, year3, idp);
}

void Books::addBook(Books*& head, Books* newBook1){
    if(!head || newBook1->title < head->title){
        newBook1->next = head;
        head = newBook1;
    }else{
        Books* current = head;
        while(current->next && newBook1->title > current->next->title){
            current = current->next;
        }
        newBook1->next = current->next;
        current->next = newBook1;
    }
    insertToHashTable(newBook1);
    History::reservations.push_back(list<string>());
}

void Books::deleteBook(Books*& head){
    int id4;
    cout << "Enter book ID: ";
    cin >> id4;
    if(!head){
        cout << "Book not found." << endl;
        return;
    }
    if(head->id == id4){
        cout << head->title << " has been deleted." << endl;
        Books* temp = head;
        head = head->next;

        deleteFromHashTable(temp->title);

        delete temp;
        return;
    }
    Books* current = head;
    Books* previous = NULL;
    while(current && current->id != id4){
        previous = current;
        current = current->next;
    }
    if(!current){
        cout << "Book not found." << endl;
        return;
    }
    cout << current->title << " has been deleted." << endl;
    previous->next = current->next;

    deleteFromHashTable(current->title);

    delete current;
}

void Books::addBookPopulate(Books*& head, int* idp){
    Books(head, "The Hunger Games", "Suzanne Collins", "Dystopian", 2008, idp);
    Books(head, "The Lord of the Rings", "J.R.R. Tolkien", "Fantasy", 1954, idp);
    Books(head, "To Kill a Mockingbird", "Harper Lee", "Fiction", 1960, idp);
    Books(head, "1984", "George Orwell", "Dystopian", 1949, idp);
    Books(head, "Pride and Prejudice", "Jane Austen", "Romance", 1925, idp);
    Books(head, "The Great Gatsby", "F. Scott Fitzgerald", "Classic", 2008, idp);
    Books(head, "Harry Potter and the SS", "J.K. Rowling", "Fantasy", 1997, idp);
    Books(head, "Moby-Dick", "Herman Melville", "Adventure", 1851, idp);
    Books(head, "The Catcher in the Rye", "J.D. Salinger", "Fiction", 1951, idp);
    //Books(head, "Brave New World", "Aldous Huxley", "Dystopian", 1932, idp);
}






void Books::insertToHashTable(Books* book5){
    titleHash.insertHashBook(book5, 't');
    authorHash.insertHashBook(book5, 'a');
}
void Books::deleteFromHashTable(string title5){
    titleHash.deleteHashBook(title5, 't');
    authorHash.deleteHashBook(title5, 'a');
}

void Books::searchHashTable(){
    Books* searchBook;
    char input;
    string input2;
    cout << "Search by title(t) or author(a): ";
    cin >> input;
    if(input == 'a' || input == 'A'){
        cout << "Enter book author: ";
        cin.ignore();
        getline(cin, input2);
        searchBook = authorHash.searchHashBook(input2, 'a');
    }else{
        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, input2);
        searchBook = titleHash.searchHashBook(input2, 't');
    }
    if(searchBook != NULL){
        cout << endl << "Book ID: " << searchBook->id << endl <<
            "Title: " << searchBook->title << endl <<
            "Author: " << searchBook->author << endl <<
            "Genre: " << searchBook->genre << endl <<
            "Year: " << searchBook->year << endl;
    }else{
        cout << "Book not found." << endl;
    }
}

void Books::displayHashTable(){
    titleHash.displayHashBook('t');
    authorHash.displayHashBook('a');
}

