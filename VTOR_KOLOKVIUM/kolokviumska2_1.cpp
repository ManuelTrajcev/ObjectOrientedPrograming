#include <iostream>
#include <cstring>

using namespace std;

class Book {
protected:
    char ISBN[20];
    char name[50];
    char author[30];
    float price;
public:
    Book(char *isbn, char *name, char *author, float price) {
        this->price = price;
        strcpy(this->ISBN, isbn);
        strcpy(this->name, name);
        strcpy(this->author, author);
    }

    Book(const Book &other) {
        this->price = other.price;
        strcpy(this->ISBN, other.ISBN);
        strcpy(this->name, other.name);
        strcpy(this->author, other.author);
    }

    Book &operator=(const Book &other) {
        if (this != &other) {
            this->price = other.price;
            strcpy(this->ISBN, other.ISBN);
            strcpy(this->name, other.name);
            strcpy(this->author, other.author);
        }
        return *this;
    }

    virtual float bookPrice() {
        return price;
    }

    ~Book() {}

    friend ostream &operator<<(ostream &os, const Book &book) {
        os << book.ISBN << ": " << book.name << ", " << book.author << " " << book.price << endl;
        return os;
    }

    void setISBN(char *ISBN) {
        strcpy(this->ISBN, ISBN);
    }

    bool operator<(const Book &rhs) const {
        return price < rhs.price;
    }

    bool operator>(const Book &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Book &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Book &rhs) const {
        return !(*this < rhs);
    }

    virtual int bookType() {
        int type;
        return type;
    }

    float getPrice() const {
        return price;
    }
};

class OnlineBook : public Book {
private:
    char *url;
    int size;
public:
    OnlineBook(char *isbn, char *name, char *author, float price, char *url, int size) : Book(isbn, name, author,
                                                                                              price) {
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
        this->size = size;
        if (size > 20) {
            price += price * 0.2;
        }
        bookPrice();
    }


    float bookPrice() {
        if (size <= 20) {
            Book::bookPrice();
        } else {
            price += price * 0.2;
        }
        return price;
    }

    char *getUrl() const {
        return url;
    }

    virtual int bookType() {
        int type = 1;
        return type;
    }
};

class PrintBook : public Book {
private:
    float mass;
    bool available;
public:
    PrintBook(char *isbn, char *name, char *author, float price, float mass, bool available) : Book(isbn, name, author,
                                                                                                    price) {
        this->mass = mass;
        this->available = available;
        bookPrice();
    }

    float bookPrice() {
        if (mass <= 0.7) {
            Book::bookPrice();
        } else {
            price += price * 0.15;
        }
        return price;
    }

    float getMass() const {
        return mass;
    }

    virtual int bookType() {
        int type = 2;
        return type;
    }
};

void mostExpensiveBook(Book **books, int n) {
    int countOnline = 0;
    int countPrint = 0, index = 0;
    int maxPrice = 0;
    for (int i = 0; i < n; ++i) {
        if (books[i]->bookType() == 1) {
            countOnline++;
        } else {
            countPrint++;
        }
        if (books[i]->getPrice() > maxPrice) {
            maxPrice = books[i]->getPrice();
            index = i;
        }
    }
    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << countOnline << endl;
    cout << "Total number of print books: " << countPrint << endl;
    cout << "The most expensive book is:" << endl;
    cout << *books[index];
}

int main() {

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}

