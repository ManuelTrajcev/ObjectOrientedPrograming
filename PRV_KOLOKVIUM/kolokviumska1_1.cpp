#include <iostream>
#include <cstring>

using namespace std;

enum tip {
    pop, rap, rock
};

class Pesna {
private:
    char *name;
    int minutes;
    tip t;
public:
    Pesna(char *name = "", int minutes = 0, tip t = pop) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->minutes = minutes;
        this->t = t;
    }

    Pesna(const Pesna &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->minutes = other.minutes;
        this->t = other.t;
    }

    Pesna &operator=(const Pesna &other) {
        if (this != &other) {
            delete [] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            this->minutes = other.minutes;
            this->t = other.t;
        }
        return *this;
    }

    void pecati() {
        cout << "\"" << this->name << "\"" << "-" << this->minutes << "min" << endl;
    }

    ~Pesna() {
        delete[] name;
    }

    int getMinutes() const {
        return minutes;
    }

    tip getT() const {
        return t;
    }
    friend class CD;
};

class CD {
private:
    Pesna *pesni;
    int n;
    int max;
public:
    CD(int max = 0) {
        this->n = 0;
        this->max = max;
        this->pesni = new Pesna[n];
        for (int i = 0; i < n; ++i) {
            this->pesni[i] = pesni[i];
        }
    }

    Pesna getPesna(int r)  {
        return pesni[r];
    }

    int getBroj() const {
        return n;
    }

    int getMax() const {
        return max;
    }

    CD(const CD &other) {
        this->n = other.n;
        this->max = other.max;
        this->pesni = new Pesna[n];
        for (int i = 0; i < n; ++i) {
            this->pesni[i] = other.pesni[i];
        }
    }

    CD &operator=(CD &other) {
        if (this != &other) {
            this->n = other.n;
            this->max = other.max;
            this->pesni = new Pesna[n];
            for (int i = 0; i < n; ++i) {
                this->pesni[i] = other.pesni[i];
            }
        }
        return *this;
    }

    ~CD() {
        delete[] pesni;
    }

    void dodadiPesna(const Pesna &p) {
        if(n==10)
            return;
        Pesna *tmp = new Pesna[n+1];
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += pesni[i].getMinutes();
        }
        if (sum + p.minutes < max) {
            for (int i = 0; i < n; ++i) {
                tmp[i] = pesni[i];
            }
            tmp[n] = p;
            n++;
            delete[] pesni;
            pesni = tmp;
        }
    }

    void pecatiPesniPoTip(tip t) {
        for (int i = 0; i < n; ++i) {
            if (pesni[i].getT() == t) {
                pesni[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime, minuti, (tip) kojtip);
        p.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < n; i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    }

    return 0;
}