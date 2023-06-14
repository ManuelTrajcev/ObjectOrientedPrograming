#include <iostream>
#include <cstring>

using namespace std;

class Vozac {
protected:
    char name[100];
    int age;
    int numRaces;
    bool veteran;
public:
    Vozac(char *name, int age, int numRaces, bool veteran) {
        this->age = age;
        this->numRaces = numRaces;
        this->veteran = veteran;
        strcpy(this->name, name);
    }

    friend ostream &operator<<(ostream &os, const Vozac &vozac) {

        os << vozac.name << "\n" << vozac.age << "\n" << vozac.numRaces << "\n";
        if (vozac.veteran) {
            os << "VETERAN\n";
        }
        return os;
    }

    virtual float zarabotuvackaPoTrka() = 0;

    bool operator==(Vozac &rhs) {
        return zarabotuvackaPoTrka() == rhs.zarabotuvackaPoTrka();
    }

    ~Vozac() {}

    virtual float danok() {
        return 1.0;
    }

};

class Avtomobilist : public Vozac {
private:
    float price;
public:
    Avtomobilist(char *name, int age, int numRaces, bool veteran, float price) : Vozac(name, age, numRaces, veteran),
                                                                                 price(price) {}

    float zarabotuvackaPoTrka() {
        float zarabotuvacka = price / 5;
        return zarabotuvacka;
    }

    float danok() {
        if (numRaces > 10) {
            return zarabotuvackaPoTrka() * 0.15;
        } else {
            return zarabotuvackaPoTrka() * 0.1;
        }
    }

};


class Motociklist : public Vozac {
private:
    int power;
public:
    Motociklist(char *name, int age, int numRaces, bool veteran, int power) : Vozac(name, age, numRaces, veteran),
                                                                              power(power) {}

    float zarabotuvackaPoTrka() {
        float zarabotuvacka = power * 20;
        return zarabotuvacka;
    }

    float danok() {
        if (veteran) {
            return zarabotuvackaPoTrka() * 0.25;
        } else {
            return zarabotuvackaPoTrka() * 0.2;
        }
    }

};

int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *vozac) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (vozaci[i]->zarabotuvackaPoTrka() == vozac->zarabotuvackaPoTrka()) {
            count++;
        }
    }
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}