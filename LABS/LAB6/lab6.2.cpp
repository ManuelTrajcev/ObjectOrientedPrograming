#include <iostream>
#include <cstring>

using namespace std;

class Book {
private:
    char *name;
    int *isbn;
    int numPages;
public:
    Book(char *name = "", int *isbn = nullptr, int numPages = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->numPages = numPages;
        this->isbn = new int[5];
        for (int i = 0; i < 5; ++i) {
            if (isbn == nullptr)
                break;
            this->isbn[i] = isbn[i];
        }
    }

    Book(const Book &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->numPages = other.numPages;
        this->isbn = new int[5];
        for (int i = 0; i < 5; ++i) {
            this->isbn[i] = other.isbn[i];
        }
    }

    Book &operator=(const Book &other) {
        if (this != &other) {
            delete[] this->name;
            delete[] this->isbn;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            this->numPages = other.numPages;

            this->isbn = new int[5];
            for (int i = 0; i < 5; ++i) {
                this->isbn[i] = other.isbn[i];
            }
        }
        return *this;
    }

    ~Book() {
        delete[] this->name;
        delete[] this->isbn;
    }

    bool operator==(Book &book) {
        for (int i = 0; i < 5; ++i) {
            if (this->isbn[i] != book.isbn[i]) {
                return false;
            }
        }
        return true;
    }

        int getIsbn(int k) const {
        return isbn[k];
    }

    int getNumPages() const {
        return numPages;
    }
};

class BorrowABook {
private:
    char name[100];
    Book *books;
    int count;
public:
    BorrowABook(char *name) {
        strcpy(this->name, name);
        this->count = 0;
        this->books = new Book[count];
    }

    BorrowABook &operator+=(Book &book) {
        Book *tmp = new Book[count + 1];
        for (int i = 0; i < count; ++i) {
            tmp[i] = books[i];
        }
        tmp[count++] = book;
        delete[] books;
        books = tmp;
        return *this;
    }

    bool compareISBN(Book &book1, Book &book2) {
        for (int i = 0; i < 5; ++i) {
            if (book1.getIsbn(i) != book2.getIsbn(i)) {
                return false;
            }
        }
        return true;
    }

    void operator-=(Book &book) {
        int j = 0;
        Book *tmp = new Book[count + 1];
        for (int i = 0; i < count; ++i) {
            if (!(compareISBN(this->books[i], book))) {
                tmp[j++] = books[i];
            }
        }
        count = j + 1;
        delete[] books;
        books = tmp;
    }

    void printNumberOfPages(int max) {
        cout << name << endl;
        for (int i = 0; i < count; ++i) {
            if (books[i].getNumPages() > max) {
                cout << books[i];
            }
        }
    }
};

int main() {
    BorrowABook library("FINKI-Library");
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char title[100];
        int isbn[5];
        int pages;

        cin >> title;

        for (int j = 0; j < 5; j++)
            cin >> isbn[j];

        cin >> pages;

        Book nov = Book(title, isbn, pages);

        //adding a new book
        library += nov;

    }
    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin >> title;
    for (int i = 0; i < 5; i++)
        cin >> isbn[i];
    cin >> pages;

    Book greshka = Book(title, isbn, pages);

    //deleting a book
    library -= greshka;

    library.printNumberOfPages(150);

    return 0;
}