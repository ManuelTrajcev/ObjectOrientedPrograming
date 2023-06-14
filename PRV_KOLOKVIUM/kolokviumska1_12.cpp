#include <iostream>
#include <cstring>

using namespace std;

class Pica {
private:
    char ime[15];
    int cena;
    char *sostojki;
    int namaluvanje;
public:
    Pica(char *ime = "", int cena = 0, char *sostojki = "", int namaluvanje = 0) {
        strcpy(this->ime, ime);
        this->cena = cena;
        this->namaluvanje = namaluvanje;
        this->sostojki = new char[strlen(sostojki) + 1];
        strcpy(this->sostojki, sostojki);
    }

    Pica(const Pica &other) {
        strcpy(this->ime, other.ime);
        this->cena = other.cena;
        this->namaluvanje = other.namaluvanje;
        this->sostojki = new char[strlen(other.sostojki) + 1];
        strcpy(this->sostojki, other.sostojki);
    }

    ~Pica() {
        delete[] sostojki;
    }

    Pica &operator=(const Pica &other) {
        strcpy(this->ime, other.ime);
        this->cena = other.cena;
        this->namaluvanje = other.namaluvanje;
        delete[] this->sostojki;
        this->sostojki = new char[strlen(other.sostojki) + 1];
        strcpy(this->sostojki, other.sostojki);
        return *this;
    }

    void pecati() {
        cout << ime << " - " << sostojki << ", " << cena;
    }

    bool istiSe(const Pica &p) {
        if (strcmp(this->sostojki, p.getSostojki()) == 0) {
            return true;
        } else {
            return false;
        }
    }

    char *getSostojki() const {
        return sostojki;
    }

    int getNamaluvanje() const {
        return namaluvanje;
    }

    int getCena() const {
        return cena;
    }
};

class Picerija {
private:
    char ime[15];
    Pica *pici;
    int n;
public:
    Picerija(char *ime = "", Pica *pici = 0, int n = 0) {
        this->n = n;
        strcpy(this->ime, ime);
        this->pici = new Pica[n];
        for (int i = 0; i < n; ++i) {
            this->pici[i] = pici[i];
        }
    }

    Picerija(const Picerija &other) {
        this->n = other.n;
        strcpy(this->ime, other.ime);
        this->pici = new Pica[n];
        for (int i = 0; i < n; ++i) {
            this->pici[i] = other.pici[i];
        }
    }

    Picerija &operator=(const Picerija &other) {
        if (this != &other) {
            this->n = other.n;
            strcpy(this->ime, other.ime);
            delete[] pici;
            this->pici = new Pica[n];
            for (int i = 0; i < n; ++i) {
                this->pici[i] = other.pici[i];
            }
        }
        return *this;
    }

    void dodadi(const Pica &P) {
        int flag = 1;
        for (int i = 0; i < n; ++i) {
            if (strcmp(this->pici[i].getSostojki(), P.getSostojki()) == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            Pica *tmp = new Pica[n + 1];
            for (int i = 0; i < n; ++i) {
                tmp[i] = pici[i];
            }
            tmp[n] = P;
            n++;
            delete[] pici;
            this->pici = new Pica[n];
            pici = tmp;
        }
    }

    void piciNaPromocija() {
        for (int i = 0; i < n; ++i) {
            if (pici[i].getNamaluvanje()) {
                pici[i].pecati();
                cout << " " << pici[i].getCena() - (pici[i].getNamaluvanje() * pici[i].getCena() / 100) << endl;
            }
        }
    }

    void setIme(char string[15]) {
        strcpy(ime, string);
    }

    const char *getIme() const {
        return ime;
    }
};


int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++) {
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2.dodadi(p);

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
