#include <iostream>
#include <cstring>

using namespace std;

class Card {
protected:
    char id[16];
    double balance;
    double limit;
public:
    Card(const char *id = "", double limit = 0, double balance = 0) {
        strcpy(this->id, id);
        this->limit = limit;
        this->balance = balance;
    }

    virtual void deposit(double amount) {
        this->balance = amount;
    }

    virtual bool withdraw(double amount) {
        if (balance + limit >= amount) {
            balance -= amount;
            return true;
        } else {
            return false;
        }
    }

    virtual void print() {
        cout << id << " Balance: " << balance << " Limit: " << limit << endl;
    }
};

class MaestroCard : public Card {
private:
    const static float DISCOUNT;
public:
    MaestroCard(const char *id = "", double limit = 0, double balance = 0) : Card(id, limit, balance) {

    }

    bool withdraw(double amount) {
        amount *= (1 - DISCOUNT);
        return Card::withdraw(amount);
    }

    void print() {
        cout << "MAESTRO: ";
        Card::print();
    }

};

class MasterCard : public Card {
private:
    const static float DISCOUNT_BASIC;
    static float DISCOUNT_PREMIUM;
public:
    MasterCard(const char *id = "", double limit = 0, double balance = 0) : Card(id, limit, balance) {

    }

    static void setDISCOUNT_BASIC(float discount) {
        DISCOUNT_PREMIUM = discount;
    }

    bool withdraw(double amount) {
        if (limit >= 6000) {
            amount *= (1 - DISCOUNT_PREMIUM);
        } else {
            amount *= (1 - DISCOUNT_BASIC);
        }
        return Card::withdraw(amount);
    }

    void print() {
        cout << "MASTER: ";
        Card::print();
    }
};

const float MaestroCard::DISCOUNT = 0.05;
const float MasterCard::DISCOUNT_BASIC = 0.03;
float MasterCard::DISCOUNT_PREMIUM = 0.1;

int main() {
    Card **cards = new Card *[4];
    cards[0] = new MasterCard("12345", 8000, 1000);
    cards[1] = new MasterCard("54321", 4000, 5000);
    cards[2] = new MaestroCard("5512421", 2000, 2000);
    cards[3] = new MaestroCard("1622421", 0, 10000);
    for (int i = 0; i < 4; ++i) {
        cards[i]->print();
    }
    MasterCard::setDISCOUNT_BASIC(0.15);
    for (int i = 0; i < 4; ++i) {
        cout << cards[i]->withdraw(8000) << endl;
        cards[i]->print();
    }
    return 0;
}