#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class NegativnaVrednost {
private:
public:
    void show() {
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas {
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    double cena;
public:
    Oglas(const char *naslov = "", const char *kategorija = "", const char *opis = "", double cena = 0) {
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
        this->cena = cena;
    }

    Oglas(const Oglas &other) {
        strcpy(this->naslov, other.naslov);
        strcpy(this->kategorija, other.kategorija);
        strcpy(this->opis, other.opis);
        this->cena = other.cena;
    }

    Oglas &operator=(const Oglas &other) {
        if (this != &other) {
            strcpy(this->naslov, other.naslov);
            strcpy(this->kategorija, other.kategorija);
            strcpy(this->opis, other.opis);
            this->cena = other.cena;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Oglas &oglas) {
        os << oglas.naslov << endl;
        os << oglas.opis << endl;
        os << oglas.cena << " evra" << endl;
        return os;
    }

    bool operator>(Oglas &oglas1) {
        return cena > oglas1.cena;
    }

    double getCena() const {
        return cena;
    }

    const char *getKategorija() const {
        return kategorija;
    }
};

class Oglasnik {
private:
    char ime[20];
    Oglas *oglasi;
    int n;
public:
    Oglasnik(const char *ime = "") {
        strcpy(this->ime, ime);
        this->n = 0;
        this->oglasi = new Oglas[n];
    }

    Oglasnik(const Oglasnik &other) {
        strcpy(this->ime, other.ime);
        this->n = other.n;
        this->oglasi = new Oglas[other.n];
        for (int i = 0; i < n; ++i) {
            this->oglasi[i] = other.oglasi[i];
        }
    }

    friend ostream &operator<<(ostream &os, Oglasnik &o) {
        os << o.ime << endl;
        for (int i = 0; i < o.n; ++i) {
            os << o.oglasi[i] << endl;
        }
        return os;
    }

    Oglasnik &operator+=(Oglas &add) {
        if (add.getCena() < 0) {
            throw NegativnaVrednost();
        }
        Oglas *tmp = new Oglas[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = oglasi[i];
        }
        tmp[n++] = add;
        delete[] oglasi;
        oglasi = tmp;
        return *this;
    }

    ~Oglasnik() {
        delete[] oglasi;
    }

    void oglasOdKategorija(const char *k) {
        for (int i = 0; i < n; ++i) {
            if (strcmp(oglasi[i].getKategorija(), k) == 0) {
                cout << oglasi[i] << endl;
            }
        }
    }

    void najniskaCena() {
        Oglas min = oglasi[0];
        for (int i = 0; i < n; ++i) {
            if (min > oglasi[i]) {
                min = oglasi[i];
            }
        }
        cout << min;
    }
};


int main() {

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost neg) {
                neg.show();
            }
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasOdKategorija(k);

    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost neg) {
                neg.show();
            }
        }
        cout << ogl;

    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            } catch (NegativnaVrednost neg) {
                neg.show();
            }
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasOdKategorija(k);
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    }

    return 0;
}
