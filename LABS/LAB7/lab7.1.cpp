#include <iostream>
#include <cstring>

using namespace std;

class Kvadrat {
protected:
    double a;
public:
    Kvadrat(double a = 0) : a(a) {

    }

    Kvadrat(const Kvadrat &other) : a(a) {
        this->a = other.a;
    }


    double plostina() {
        return a * a;
    }

    double perimentar() {
        return 4 * a;
    }

    void pecati() {
        cout << "Kvadrat so dolzina a=" << a << " ima plostina P=" << plostina() << " i perimetar L=" <<
             perimentar() << endl;
    }
};

class Pravoagolnik : public Kvadrat { //da se vmetni nasleduvanjeto
private:
    double x;
    double y;

public:

    Pravoagolnik(double a = 0, double x = 0, double y = 0) : Kvadrat(a), x(x), y(y) {}


    Pravoagolnik(const Kvadrat &k, double x = 0, double y = 0) : Kvadrat(k) {
        this->x = x;
        this->y = y;
    }


    double plostina() {
        return (a + x) * (a + y);
    }

    double perimentar() {
        return 2 * (a + x) + 2 * (a + y);
    }

    void pecati() {
        if ((a + x) == (a + y)) {
            cout << "Kvadrat so dolzina a=" << a+x << " ima plostina P=" << plostina() << " i perimetar L=" <<
                 perimentar() << endl;
            return;
        }
        cout << "Pravoagolnik so strani: " << a + x << " i " << a + y << " ima plostina P=" << plostina()
             << " i perimetar L="
             <<
             perimentar() << endl;
    }

};

int main() {
    int n;
    double a, x, y;
    Kvadrat *kvadrati;
    Pravoagolnik *pravoagolnici;

    cin >> n;

    kvadrati = new Kvadrat[n];
    pravoagolnici = new Pravoagolnik[n];

    for (int i = 0; i < n; i++) {
        cin >> a;

        kvadrati[i] = Kvadrat(a);
    }

    for (int i = 0; i < n; i++) {
        cin >> x >> y;

        pravoagolnici[i] = Pravoagolnik(kvadrati[i], x, y);
    }

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "===Testiranje na klasata Kvadrat===" << endl;
        for (int i = 0; i < n; i++)
            kvadrati[i].pecati();
    } else {
        cout << "===Testiranje na klasata Pravoagolnik===" << endl;
        for (int i = 0; i < n; i++)
            pravoagolnici[i].pecati();
    }
}