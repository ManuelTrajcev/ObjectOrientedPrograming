#include <iostream>
#include <cstring>

using namespace std;

class HotelReservation {
protected:
    int days;
    int guests;
    char contact[50];
public:
    HotelReservation(char *contact, int days, int guests) : days(days), guests(guests) {
        strcpy(this->contact, contact);
    }

    virtual double price() {
        return guests * days * 25;
    }

    virtual double price(int deposit) {
        return deposit - price();
    }
};

class HalfBoardHotelReservation : public HotelReservation {
public:
    HalfBoardHotelReservation(char *contact, int days, int guests) : HotelReservation(contact, days, guests) {

    }

    double price() {
        return HotelReservation::price() * 1.2;
    }

    double price(int deposit) {
        return deposit - price();
    }

};

class Hotel {
private:
    char name[20];
    double balance;
public:
    Hotel(char *name, double balance) : balance(balance) {
        strcpy(this->name, name);
    }

    double depositeReservation(HotelReservation &reservation, double deposit) {
        double totalPrice = reservation.price();
        balance += totalPrice;
        return reservation.price(deposit);
    }

    friend ostream &operator<<(ostream &os, const Hotel &hotel) {
        os << "Name: " << hotel.name << " Balance: " << hotel.balance << endl;
        return os;
    }

    double getBalance() const {
        return balance;
    }
};

int main() {
    Hotel hotel("FINKI", 1000);
    int n;
    cin >> n;
    HotelReservation **reservations = new HotelReservation *[n];
    for (int i = 0; i < n; ++i) {
        int type; //1 = normal, 2 = half
        char contact[30];
        int days, guests, deposit;
        cin >> type >> contact >> days >> guests >> deposit;
        if (type == 1) {
            reservations[i] = new HotelReservation(contact, days, guests);
        } else {
            reservations[i] = new HalfBoardHotelReservation(contact, days, guests);
        }
        cout << "Name: " << contact << " Days: " << days << " Guests: " << guests << " Price: "
             << reservations[i]->price() << endl;

        cout << "Change from payment: " << hotel.depositeReservation(*reservations[i], deposit) << endl;
    }
    cout << "Hotel state after all payments:  " << hotel.getBalance();
    return 0;
}