#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <mutex>
#include <unordered_set>

using namespace std;

enum class BookStatus {AVAILABLE, ISSUED, RESERVED, LOST};

class Book{
    private:
        string isbn;
        string title;
        string subject;
    public:
        Book(string isbn, string title, string subject) 
            : isbn(isbn), title(title), subject(subject) {}
        
        string getIsbn() const { return isbn; }
        string getTitle() const { return title; }
        string getSubject() const { return subject; }
};

class Shelf{
    private:
        int shelfId;
        vector<int> bookItemIds;
    public:
        Shelf(int id) : shelfId(id) {}
        int getShelfId() const { return shelfId; }
};

class BookItem{
    private:
        int bookItemId;
        Book* book;
        BookStatus bookStatus;
        Shelf* shelf;
    public:
        BookItem(int id, Book* b, Shelf* s) 
            : bookItemId(id), book(b), bookStatus(BookStatus::AVAILABLE), shelf(s) {}
        
        int getBookItemId() const { return bookItemId; }
        Book* getBook() const { return book; }
        BookStatus getStatus() const { return bookStatus; }
        void setStatus(BookStatus status) { bookStatus = status; }
        Shelf* getShelf() const { return shelf; }
};


class Inventory {
    private:
        map<Book*, int> bookItems;
        mutex inventoryMutex;
    public:
        void addBookItem(Book* book){
            lock_guard<mutex> lock(inventoryMutex);
            if(bookItems.find(book) != bookItems.end()){ 
                bookItems[book]++;
            }else{
                bookItems[book] = 1;
            }
        }

        void removeBookItem(Book* book){
            lock_guard<mutex> lock(inventoryMutex);
            if(bookItems.find(book) == bookItems.end()){
                cout << "Book not found in inventory" << endl;
                return;            
            }else{
                bookItems[book]--;
                if(bookItems[book] == 0) {
                    bookItems.erase(book);
                }
            }
        }

        int fetchNumberOfBooks(Book* book){
            lock_guard<mutex> lock(inventoryMutex);
            if(bookItems.find(book) == bookItems.end()){
                return 0;
            }else{
                return bookItems[book];
            }
        }
};

class Inventory{
    private:
        unordered_map<Book*, int> books;
        mutex inventoryMutex;

    public:
        void addBookItem(Book* book){
            //lock the books map using mutex Lock of the inventory
            if(books.find(book) == books.end()){
                books[book] = 0;
            }else{
                books[book]++;
            }
        }

        void removeBook(Book* book){
            if(book)
        }
}

class Catalog {
    private:
        unordered_set<string> bookIsbnSet;
        vector<Book*> books; // vector of all books that are there.
        mutex catalogMutex;
    public:
        void addBook(Book* book) {
            lock_guard<mutex> lock(catalogMutex);
            bookIsbnSet.insert(book->getIsbn());
            books.push_back(book);
        }
        
        Book* searchByIsbn(string isbn) {
            lock_guard<mutex> lock(catalogMutex);
            for(Book* book : books) {
                if(book->getIsbn() == isbn) return book;
            }
            return nullptr;
            }
        
        vector<Book*> searchByTitle(string title) {
            lock_guard<mutex> lock(catalogMutex);
            vector<Book*> results;
            for(Book* book : books) {
                if(book->getTitle() == title) results.push_back(book);
            }
            return results;
        }
};

class User{
    protected:
        int userId;
        string firstName;
        string lastName;
        string email;
    public:
        User(int id, string first, string last, string mail)
            : userId(id), firstName(first), lastName(last), email(mail) {}
        
        virtual ~User() {}
        
        int getUserId() const { return userId; }
        string getFirstName() const { return firstName; }
        string getLastName() const { return lastName; }
        string getEmail() const { return email; }
};

class BorrowedBooks {
    private:
        BookItem* bookItem;
        time_t borrowDate;
        time_t dueDate;
        time_t returnDate;
    public:
        BorrowedBooks(BookItem* item) 
            : bookItem(item), borrowDate(time(0)), returnDate(0) {
            dueDate = borrowDate + (14 * 24 * 3600);
        }
        
        BookItem* getBookItem() const { return bookItem; }
        time_t getBorrowDate() const { return borrowDate; }
        time_t getDueDate() const { return dueDate; }
        time_t getReturnDate() const { return returnDate; }
        void setReturnDate() { returnDate = time(0); }
};

class Member : public User{
    private:
        int maxBooksAllowed = 5;
        vector<BorrowedBooks*> borrowedBooks;
    public:
        Member(int id, string first, string last, string mail)
            : User(id, first, last, mail) {}
        
        bool borrowBook(BookItem* bookItem) {
            if(borrowedBooks.size() >= maxBooksAllowed) {
                cout << "Maximum books limit reached" << endl;
                return false;
            }
            BorrowedBooks* borrowed = new BorrowedBooks(bookItem);
            borrowedBooks.push_back(borrowed);
            bookItem->setStatus(BookStatus::ISSUED);
            return true;
        }
        
        bool returnBook(BookItem* bookItem) {
            for(auto it = borrowedBooks.begin(); it != borrowedBooks.end(); it++) {
                if((*it)->getBookItem() == bookItem) {
                    (*it)->setReturnDate();
                    bookItem->setStatus(BookStatus::AVAILABLE); 
                    borrowedBooks.erase(it);
                    return true;
                }
            }
            return false;
        }
        
        int getNumberOfBorrowedBooks() const { return borrowedBooks.size(); }
};

class Librarian : public User{
    public:
        Librarian(int id, string first, string last, string mail)
            : User(id, first, last, mail) {}
        
        void addBookItem(Inventory& inventory, Book* book){
            inventory.addBookItem(book);
            cout << "Book added to inventory" << endl;
        }
        
        void removeBookItem(Inventory& inventory, Book* book){
            inventory.removeBookItem(book);
            cout << "Book removed from inventory" << endl;
        }
        
        void addBookToCatalog(Catalog& catalog, Book* book) {
            catalog.addBook(book);
            cout << "Book added to catalog" << endl;
        }
};
