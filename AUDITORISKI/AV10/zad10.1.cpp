#include <iostream>
#include <cstring>

using namespace std;

class Karticka {
protected:
    char id[16];
    double saldo;
public:
    Karticka(const char *id = "", double saldo = 0) {
        strcpy(this->id, id);
        this->saldo = saldo;
    }

    void uplata(double suma) {
        saldo += suma;
    }

    virtual double isplata(double suma) {
        if (saldo >= suma) {
            saldo -= suma;
            return suma;
        }
        return 0;
    }

    virtual void print() {
        cout << "KARTICKA:";
        cout << id << " " << saldo << endl;
    }
};

class Master : public Karticka {
private:
    const static double popust1;
    static double popust2;
    double limit;
public:
    Master(const char *id = "", double saldo = 0, double limit = 0) : Karticka(id, saldo), limit(limit) {}

    void print() {
        Karticka::print();
        cout << popust1 << endl;
        cout << popust2 << endl;
    }

    double isplata(double suma) {
        double soPopust = 0;
        if (limit >= 6000) {
            soPopust = suma * (1 - popust2);
        } else {
            soPopust = suma * (1 - popust1);
        }
        if (soPopust > saldo + limit) {
            return 0;
        } else {
            saldo -= soPopust;
            return soPopust;
        }
    }
};

class Maestro : public Karticka {
private:
    const static double popust;

public:
    Maestro(const char *id = "", double saldo = 0) : Karticka(id, saldo) {}

    void print() {
        Karticka::print();
        cout << popust << endl;
    }

    double isplata(double suma) {
        return Karticka::isplata(suma * (1 - popust));
    }


};

const double Maestro::popust = 0.05;
const double Master::popust1 = 0.03;
double Master::popust2 = 0.01;

class Kasa {
private:
    int den, mesec, godina;
    double sumaGotovina, sumaKarticka;
public:
    Kasa(int den = 1, int mesec = 1, int godina = 2000, double sumaGotovina = 0, double sumaKarticka = 0) : den(den),
                                                                                                            mesec(mesec),
                                                                                                            godina(godina),
                                                                                                            sumaGotovina(
                                                                                                                    sumaGotovina),
                                                                                                            sumaKarticka(
                                                                                                                    sumaKarticka) {

    }

    void print() {
        cout << den << "." << mesec << "." << godina << endl;
        cout << sumaGotovina << endl;
        cout << sumaKarticka << endl;
    }

    void kasaPrimi(double suma) {
        sumaGotovina += suma;
    }


    void kasaPrimi(double suma, Karticka &karticka) {
        sumaKarticka += karticka.isplata(suma);
    }
};

int main() {
    Kasa s(18, 5, 2003);
    s.kasaPrimi(500);
    Karticka *m = new Maestro("1231", 5000);
    s.kasaPrimi(1000, *m);
    s.print();
    m->print();
    return 0;
}