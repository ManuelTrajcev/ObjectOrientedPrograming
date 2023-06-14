#include <iostream>
#include <cstring>

#define MAX 100

using namespace std;

enum typeC {
    standard, loyal, vip
};

string types[3] = {"standard", "loyal", "vip"};

class UserExistsException {
public:
    void showMessage() {
        cout << "The user already exists in the list!" << endl;
    }
};

class Customer {
protected:
    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int discountPlus;
    int numProducts;
public:
    Customer() {
        this->tC = 0;
        this->numProducts = 0;
        strcpy(this->name, "name");
        strcpy(this->email, "email");
        discount = 0;
    }

    Customer(char *name, char *email, int tC, int numProducts) {
        this->tC = tC;
        this->numProducts = numProducts;
        strcpy(this->name, name);
        strcpy(this->email, email);
        if (tC == 0) {
            discount = 0;
        } else if (tC == 1) {
            discount = 10;
        } else {
            discount = 30;
        }
    }

    Customer(const Customer &other) {
        this->tC = other.tC;
        this->numProducts = other.numProducts;
        strcpy(this->name, other.name);
        strcpy(this->email, other.email);
        if (tC == 0) {
            discount = 0;
        } else if (tC == 1) {
            discount = 10;
        } else {
            discount = 30;
        }
    }

    Customer &operator=(const Customer &other) {
        if (this != &other) {
            this->tC = other.tC;
            this->numProducts = other.numProducts;
            strcpy(this->name, other.name);
            strcpy(this->email, other.email);
            if (tC == 0) {
                discount = 0;
            } else if (tC == 1) {
                discount = 10;
            } else {
                discount = 30;
            }
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Customer &customer) {
        os << customer.name << endl;
        os << customer.email << endl;
        os << customer.numProducts << endl;
        os << types[customer.tC] << " " << customer.discount << endl;
        return os;
    }

    void setDiscount1(int discount) {
        this->discount = discount;
    }

    const char *getEmail() const {
        return email;
    }

    int getNumProducts() const {
        return numProducts;
    }

    int getTc() const {
        return tC;
    }

    void setTc(int tC) {
        this->tC = tC;
        if (tC == 0) {
            discount = 0;
        } else if (tC == 1) {
            discount = 10;
        } else {
            discount = 30;
        }
    }
};

class FINKI_bookstore {
private:
    Customer *customer;
    int n;
public:
    FINKI_bookstore(Customer *customer = nullptr, int n = 0) {
        this->n = n;
        this->customer = new Customer[n];
        for (int i = 0; i < n; ++i) {
            this->customer[i] = customer[i];
        }
    }

    FINKI_bookstore(const FINKI_bookstore &other) {
        this->n = other.n;
        this->customer = new Customer[n];
        for (int i = 0; i < n; ++i) {
            this->customer[i] = other.customer[i];
        }
    }

    FINKI_bookstore &operator=(const FINKI_bookstore &other) {
        if (this != &other) {
            this->n = other.n;
            delete[] this->customer;
            this->customer = new Customer[n];
            for (int i = 0; i < n; ++i) {
                this->customer[i] = other.customer[i];
            }
        }
        return *this;
    }

//    ~FINKI_bookstore() {
//        delete[] this->customer;
//    }

    FINKI_bookstore &operator+=(Customer &other) {
        int flag = 1;
        for (int i = 0; i < n; ++i) {
            if (strcmp(customer[i].getEmail(), other.getEmail()) == 0) {
                throw UserExistsException();
            }
        }
        if (flag) {
            Customer *tmp = new Customer[n + 1];
            for (int i = 0; i < n; ++i) {
                tmp[i] = customer[i];
            }
            tmp[n++] = other;
//            delete[] customer; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            customer = tmp;
        }
        return *this;
    }

    void setCustomers(Customer *customers, int k) {
        delete[] customer;
        this->customer = customers;
        this->n = k;
    }

    friend ostream &operator<<(ostream &os, FINKI_bookstore &bookstore) {
        for (int i = 0; i < bookstore.n; ++i) {
            os << bookstore.customer[i];
        }
        return os;
    }

    void update() {
        for (int i = 0; i < n; ++i) {
            if (customer[i].getTc() == 0) {
                if (customer[i].getNumProducts() > 5) {
                    customer[i].setTc(customer[i].getTc() + 1);
                }
            } else if (customer[i].getTc() == 1) {
                if (customer[i].getNumProducts() > 10) {
                    customer[i].setTc(customer[i].getTc() + 1);
                }
            }
        }
    }

};

int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc += c;

        cout << fc;
    }
//
    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try {
            fc += c;
        } catch (UserExistsException exception) {
            exception.showMessage();
        }

        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
