#include <iostream>
#include <cstring>

using namespace std;

class Ucenik {
private:
    char *ime;
    float prosek;
    int godina;
public:
    Ucenik(char *ime = "", float prosek = 0, int godina = 1) {
        this->prosek = prosek;
        this->godina = godina;
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
    }

    Ucenik(const Ucenik &other) {
        this->prosek = other.prosek;
        this->godina = other.godina;
        this->ime = new char[strlen(other.ime) + 1];
        strcpy(this->ime, other.ime);
    }

    Ucenik &operator=(const Ucenik &other) {
        if (this != &other) {
            this->prosek = other.prosek;
            this->godina = other.godina;
            delete[] ime;
            this->ime = new char[strlen(other.ime) + 1];
            strcpy(this->ime, other.ime);
        }
        return *this;
    }

    ~Ucenik() {
        delete[] ime;
    }

    Ucenik operator++() {
        godina++;
        return *this;
    }

    Ucenik operator++(int) {
        Ucenik u(*this);
        godina++;
        return u;
    }

    float getProsek() const {
        return prosek;
    }

    friend ostream &operator<<(ostream &o, const Ucenik &u) {
        return o << "Ime: " << u.ime << ", godina: " << u.godina << ", prosek: " << u.prosek << endl;
    }

    friend bool operator>(const Ucenik &u1, const Ucenik &u2);
};

bool operator>(const Ucenik &u1, const Ucenik &u2) {
    return u1.prosek > u2.prosek;
}

class Paralelka {
private:
    Ucenik *ucenici;
    int n;
public:
    Paralelka(Ucenik *ucenici = nullptr, int n = 0) {
        this->n = n;
        this->ucenici = new Ucenik[n];
        for (int i = 0; i < n; ++i) {
            this->ucenici[i] = ucenici[i];
        }
    }

    Paralelka(const Paralelka &other) {
        this->n = other.n;
        this->ucenici = new Ucenik[n];
        for (int i = 0; i < n; ++i) {
            this->ucenici[i] = other.ucenici[i];
        }
    }

    Paralelka &operator=(const Paralelka &other) {
        if (this != &other) {
            this->n = other.n;
            delete[] ucenici;
            this->ucenici = new Ucenik[n];
            for (int i = 0; i < n; ++i) {
                this->ucenici[i] = other.ucenici[i];
            }
        }
        return *this;
    }

    ~Paralelka() {
        delete[] ucenici;
    }

    Paralelka &operator+=(Ucenik &u) {
        Ucenik *tmp = new Ucenik[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = ucenici[i];
        }
        tmp[n++] = u;
        delete[] ucenici;
        ucenici = tmp;
        return *this;
    }

    Paralelka &operator++() {
        for (int i = 0; i < n; ++i) {
            ucenici[i]++;
        }
        return *this;
    }

    Paralelka operator++(int) {
        Paralelka p(*this);
        for (int i = 0; i < n; ++i) {
            ucenici[i]++;
        }
        return p;
    }

    friend ostream &operator<<(ostream &o, Paralelka &p) {
        o << "Vo ovaa paralelka se ucenicite:" << endl;
        for (int i = 0; i < p.n; ++i) {
            o << p.ucenici[i];
        }
        return o;
    }

    void nagradi() {
        for (int i = 0; i < n; ++i) {
            if (ucenici[i].getProsek() == 10.0) {
                cout << ucenici[i];
            }
        }
    }

    void najvisokProsek() {
        Ucenik max = ucenici[0];
        for (int i = 0; i < n; ++i) {
            if (ucenici[i] > max) {
                max = ucenici[i];
            }
        }
        cout << "Najvisok prosek ima: " << max;
    }
};

int main() {
    Ucenik u1("Martina Martinovska", 9.5, 3);
    Ucenik u2("Darko Darkoski", 7.3, 2);
    Ucenik u3("Angela Angelovska", 10, 3);

    Paralelka p;
    p += u1;
    p += u2;
    p += u3;

    cout << p;
    cout << "Nagradeni:" << endl;
    p.nagradi();
    cout << endl;
    p.najvisokProsek();
    cout << endl;

    u2++;
    cout << p;
    cout << endl;
    p++;
    cout << p;

    return 0;
}