#include<iostream>
#include<cstring>

using namespace std;

class StockRecord {
    char id[12];
    char company[50];
    float stockPrice;
    float momentalPrice;
    int n;
public:
    StockRecord(char *id = "", char *company = "", float stockPrice = 0, int n = 0) {
        this->n = n;
        this->stockPrice = stockPrice;
        this->momentalPrice = 0;
        strcpy(this->id, id);
        strcpy(this->company, company);
    }

    StockRecord(const StockRecord &other) {
        this->n = other.n;
        this->stockPrice = other.stockPrice;
        this->momentalPrice = other.momentalPrice;
        strcpy(this->id, other.id);
        strcpy(this->company, other.company);
    }

    StockRecord &operator=(const StockRecord &other) {
        if (this != &other) {
            this->n = other.n;
            this->stockPrice = other.stockPrice;
            this->momentalPrice = other.momentalPrice;
            strcpy(this->id, other.id);
            strcpy(this->company, other.company);
        }
        return *this;
    }

    void setNewPrice(double c) {
        momentalPrice = c;
    }

    ~StockRecord() {}

    double value() {
        return momentalPrice * n;
    }

    double profit() {
        return 1.0 * n * (momentalPrice - stockPrice);
    }

    friend ostream &operator<<(ostream &os, StockRecord &record) {
        os << record.company << " " << record.n << " " << record.stockPrice << " "
           << record.momentalPrice << " " << record.profit() << endl;
        return os;
    }

};

class Client {
    char name[60];
    int id;
    StockRecord *companies;
    int n;
public:
    Client(char *name = "", int id = 0, StockRecord *companies = nullptr, int n = 0) {
        this->id = id;
        strcpy(this->name, name);
        this->n = n;
        this->companies = new StockRecord[n];
        for (int i = 0; i < n; ++i) {
            this->companies[i] = companies[i];
        }
    }

    Client(const Client &other) {
        this->id = other.id;
        strcpy(this->name, other.name);
        this->n = other.n;
        this->companies = new StockRecord[n];
        for (int i = 0; i < n; ++i) {
            this->companies[i] = other.companies[i];
        }
    }

    Client &operator=(const Client &other) {
        if (this != &other) {
            this->id = other.id;
            strcpy(this->name, other.name);
            this->n = other.n;
            delete[] companies;
            this->companies = new StockRecord[n];
            for (int i = 0; i < n; ++i) {
                this->companies[i] = other.companies[i];
            }
        }
        return *this;
    }

    ~Client() {
        delete[] companies;
    }

    double totalValue() {
        double sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += companies[i].value();
        }
        return sum;
    }

    Client &operator+=(const StockRecord &other) {
        StockRecord *tmp = new StockRecord[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = companies[i];
        }
        tmp[n++] = other;
        delete[] companies;
        companies = tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, Client &client) {
        os << client.id << " " << client.totalValue() << endl;
        for (int i = 0; i < client.n; ++i) {
            cout << client.companies[i];
        }
        return os;
    }
};

int main() {

    int test;
    cin >> test;

    if (test == 1) {
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    } else if (test == 2) {
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    } else if (test == 3) {
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if (flag) {
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}