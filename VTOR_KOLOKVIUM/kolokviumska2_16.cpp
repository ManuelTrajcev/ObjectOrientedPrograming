#include <iostream>
#include <cstring>
#include <bits/stdc++.h>


using namespace std;

class Transport {
protected:
    char destination[50];
    int price;
    int distance;
public:
    Transport(char *destination = "", int price = 0, int distance = 0) {
        this->price = price;
        this->distance = distance;
        strcpy(this->destination, destination);
    }

    virtual void cenaTransport() = 0;

    bool operator<(const Transport &rhs) const {
        return price < rhs.price;
    }

    const char *getDestination() const {
        return destination;
    }

    int getPrice() const {
        return price;
    }

    int getDistance() const {
        return distance;
    }

};

class AvtomobilTransport : public Transport {
private:
    bool driver;
public:
    AvtomobilTransport(char *destination = "", int price = 0, int distance = 0, bool driver = false) : Transport(
            destination, price,
            distance), driver(driver) {
        cenaTransport();

    }

    void cenaTransport() {
        if (driver) {
            price += price * 0.2;
        }
    }

};

class KombeTransport : public Transport {
private:
    int capacity;
public:
    KombeTransport(char *destination = "", int price = 0, int distance = 0, int capacity = 0) : Transport(destination,
                                                                                                          price,
                                                                                                          distance),
                                                                                                capacity(capacity) {
        cenaTransport();
    }

    void cenaTransport() {
        price -= capacity * 200;
    }


};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &nov) {
    Transport *tmp = ponudi[0];
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            int jot = ponudi[j]->getPrice();
            int jot1 = ponudi[j + 1]->getPrice();
            if (jot > jot1) {
                tmp = ponudi[j];
                ponudi[j] = ponudi[j + 1];
                ponudi[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (ponudi[i]->getPrice() > nov.getPrice())
            cout << ponudi[i]->getDestination() << " " << ponudi[i]->getDistance() << " " << ponudi[i]->getPrice()
                 << endl;
    }
}

int main() {

    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++) {

        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1) {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);

        } else {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }


    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++) delete ponudi[i];
    delete[] ponudi;
    return 0;
}
