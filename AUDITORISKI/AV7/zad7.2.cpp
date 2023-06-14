#include <iostream>
#include <cstring>

using namespace std;


class DebitAccount {
protected:
    char name[100];
    long number;
    double balance;
public:
    DebitAccount(char *name = "", long number = 0, double balance = 0) : number(number), balance(balance) {
        strcpy(this->name, name);
    }

    DebitAccount(const DebitAccount &other) {
        strcpy(this->name, other.name);
        this->number = other.number;
        this->balance = other.balance;
    }

    friend ostream &operator<<(ostream &os, const DebitAccount &account) {
        os << "Name: " << account.name << "\nAccount Number: " << account.number << "\nBalance: " << account.balance
           << endl;
        return os;
    }

    ~DebitAccount() {}

    void deposit(double amount) {
        balance += amount;
        cout << "You have deposited: " << amount << ", New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (balance - amount >= 0) {
            balance -= amount;
            cout << "You have withdrawn: " << amount << ", New Balance: " << balance << endl;
        } else {
            cout << "Transaction declined" << endl;
        }
    }
};

class CreditAccount : public DebitAccount {
private:
    double limit;
    double interest;
public:
    CreditAccount(const DebitAccount &other, double limit, double interest) : DebitAccount(other), limit(limit),
                                                                              interest(interest) {

    }

    ~CreditAccount() {}

    CreditAccount(char *name, long number, double balance, double limit, double interest) : DebitAccount(name, number,
                                                                                                         balance),
                                                                                            limit(limit),
                                                                                            interest(interest) {

    }

    void withdraw(double amount) {
        double tmp = balance;
        if (balance - amount >= 0) {
            DebitAccount::withdraw(amount);
        } else {
            if (balance > 0) {
                amount -= balance;
                balance = 0;
            }
            amount += amount * interest;
            if (amount <= limit) {
                balance -= amount;
                cout << "You have withdrawn: " << amount << ", New Balance: " << balance << endl;
            } else {
                balance = tmp;
                cout << "Transaction declined" << endl;
            }
        }
    }

    friend ostream &operator<<(ostream &os, const CreditAccount &account) {
        os << static_cast<const DebitAccount &>(account) << "Limit: " << account.limit << " Interest: "
           << account.interest;
        return os;
    }

};

int main() {
    char name[100];
    long number;
    double balance;
    cout << "Insert Name, Acc Number and Balance:" << endl;
    cin >> name >> number >> balance;
    DebitAccount acc(name, number, balance);
    CreditAccount creditAcc(acc, 1000, 0.05);
    creditAcc.deposit(2000);
    creditAcc.withdraw(400);
    creditAcc.withdraw(1000);
    creditAcc.withdraw(2800);
    cout << creditAcc;
    return 0;
}