#include <iostream>
#include <cstring>

using namespace std;


class GeometriskoTelo {
protected:
    int visina;
public:
    GeometriskoTelo(int visina = 0) : visina(visina) {}

    virtual void pecati() {
        cout << visina;
    }

    int getVisina() {
        return visina;
    }

    virtual float volumen() = 0;
};

class Cilinder : public GeometriskoTelo {
private:
    int r;
public:
    Cilinder(int visina = 0, int r = 0) : GeometriskoTelo(visina) {
        this->r = r;
    }

    float volumen() {
        return 3.14 * r * r * visina;
    }

    void pecati() {
        cout << "Cilider so visina ";
        GeometriskoTelo::pecati();
        cout << " i radius " << r << endl;
    }

};

class Konus : public GeometriskoTelo {
private:
    int r;
public:
    Konus(int visina = 0, int r = 0) : GeometriskoTelo(visina), r(r) {}


    float volumen() {
        return (3.14 * r * r * visina) / 3.0;
    }

    void pecati() {
        cout << "Konus so visina ";
        GeometriskoTelo::pecati();
        cout << " i radius " << r << endl;
    }

};

class Kvadar : public GeometriskoTelo {
private:
    int a, b;
public:
    Kvadar(int visina = 0, int a = 0, int b = 0) : GeometriskoTelo(visina), a(a), b(b) {}

    float volumen() {
        return a * b * visina;
    }

    void pecati() {
        cout << "Kvadar so visina ";
        GeometriskoTelo::pecati();
        cout << ",sirina " << a << " i dolzina" << b << endl;
    }
};

void teloSoNajgolemVolumen(GeometriskoTelo *niza[], int n) {
    int maxIndex = 0;
    float maxVolumen = niza[0]->volumen();
    for (int i = 1; i < n; ++i) {
        if (niza[i]->volumen() > maxVolumen) {
            maxVolumen = niza[i]->volumen();
            maxIndex = i;
        }
    }
    niza[maxIndex]->pecati();
}

int main() {
    int n;
    cin >> n;
    GeometriskoTelo **p = new GeometriskoTelo *[n];
    //1 = cilinder, 2 = konus, 3 = kvadar
    for (int i = 0; i < n; ++i) {
        int type;
        int visina, radius, a, b;
        cin >> type;
        if (type == 1) {
            cin >> visina >> radius;
            p[i] = new Cilinder(visina, radius);
        } else if (type == 2) {
            cin >> visina >> radius;
            p[i] = new Konus(visina, radius);
        } else {
            cin >> visina >> a >> b;
            p[i] = new Kvadar(visina, a, b);
        }
    }
    teloSoNajgolemVolumen(p, n);
    return 0;
}