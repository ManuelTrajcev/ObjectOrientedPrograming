#include<iostream>
#include<string.h>

using namespace std;

class Delo {
private:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(char *ime = "", int godina = 0, char *zemja = "") {
        this->godina = godina;
        strcpy(this->ime, ime);
        strcpy(this->zemja, zemja);
    }

    Delo(const Delo &other) {
        this->godina = other.godina;
        strcpy(this->ime, other.ime);
        strcpy(this->zemja, other.zemja);
    }

    Delo &operator=(const Delo &other) {
        if (this != &other) {
            this->godina = other.godina;
            strcpy(this->ime, other.ime);
            strcpy(this->zemja, other.zemja);
        }
        return *this;
    }

    bool operator==(const Delo &rhs) const {
        if (strcmp(this->ime, rhs.ime)) {
            return false;
        } else {
            return true;
        }
    }

    const char *getIme() const {
        return ime;
    }

    int getGodina() const {
        return godina;
    }

    void setGodina(int godina) {
        Delo::godina = godina;
    }

    const char *getZemja() const {
        return zemja;
    }

    const char getZemja(int i) const {
        return zemja[i];
    }

};

class Pretstava {
protected:
    Delo delo;
    int karti;
    char data[15];
public:
    Pretstava(const Delo &delo = nullptr, int karti = 0, char *data = "") {
        this->delo = delo;
        this->karti = karti;
        strcpy(this->data, data);
    }

    virtual int cena() = 0;

    const Delo &getDelo() const {
        return delo;
    }

    void setDelo(const Delo &delo) {
        Pretstava::delo = delo;
    }

    int getKarti() const {
        return karti;
    }

    void setKarti(int karti) {
        Pretstava::karti = karti;
    }

    const char *getData() const {
        return data;
    }
};

class Opera : public Pretstava {
private:

public:
    Opera(const Delo &delo = nullptr, int karti = 0, char *data = "") : Pretstava(delo, karti, data) {
    }

    int cena() {
        int cena = 0;

        if (delo.getGodina() / 1000 == 2) {
            cena += 75;
        } else {
            if (delo.getGodina() / 100 == 19) {
                cena += 50;
            } else if (delo.getGodina() / 100 == 18) {
                cena += 75;
            } else {
                cena += 100;
            }
        }

        if (strcmp(delo.getZemja(), "Rusija") == 0) {
            cena += 150;
        } else if (strcmp(delo.getZemja(), "Italija") == 0) {
            cena += 100;
        } else {
            cena += 80;
        }
        return cena;
    }
};

class Balet : public Pretstava {
private:
    static int cenaBalet;

public:

    Balet(const Delo &delo = nullptr, int karti = 0, char *data = "") : Pretstava(delo, karti, data) {
    }

    int getCenaBalet() const {
        return cenaBalet;
    }

    static void setCenaBalet(int cena) {
        cenaBalet = cena;
    }

    int cena() {
        int cena = 0;

        if (delo.getGodina() / 1000 == 2) {
            cena += 75;
        } else {
            if (delo.getGodina() / 100 == 19) {
                cena += 50;
            } else if (delo.getGodina() / 100 == 18) {
                cena += 75;
            } else {
                cena += 100;
            }
        }

        if (strcmp(delo.getZemja(), "Rusija") == 0) {
            cena += 150;
        } else if (strcmp(delo.getZemja(), "Italija") == 0) {
            cena += 100;
        } else {
            cena += 80;
        }

        cena += cenaBalet;

        return cena;
    }
};

int prihod(Pretstava **p, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += p[i]->cena() * p[i]->getKarti();
    }
    return sum;
}

int brojPretstaviNaDelo(Pretstava **p, int n, Delo &d) {
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        if (strcmp(p[i]->getDelo().getIme(), d.getIme()) == 0) {
            counter++;
        }
    }
    return counter;
}

//citanje na delo
Delo readDelo() {
    char ime[50];
    int godina;
    char zemja[50];
    cin >> ime >> godina >> zemja;
    return Delo(ime, godina, zemja);
}

//citanje na pretstava
Pretstava *readPretstava() {
    int tip; //0 za Balet , 1 za Opera
    cin >> tip;
    Delo d = readDelo();
    int brojProdadeni;
    char data[15];
    cin >> brojProdadeni >> data;
    if (tip == 0) return new Balet(d, brojProdadeni, data);
    else return new Opera(d, brojProdadeni, data);
}

int Balet::cenaBalet = 150;

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout << "======TEST CASE 1=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->getDelo().getIme() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->getDelo().getIme() << endl;
        }
            break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout << "======TEST CASE 2=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->cena() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->cena() << endl;
        }
            break;

        case 3:
            //Testiranje na operator ==
        {
            cout << "======TEST CASE 3=======" << endl;
            Delo f1 = readDelo();
            Delo f2 = readDelo();
            Delo f3 = readDelo();

            if (f1 == f2) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;
            if (f1 == f3) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;

        }
            break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout << "======TEST CASE 4=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();

            }
            cout << prihod(pole, n);
        }
            break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout << "======TEST CASE 5=======" << endl;
            int cenaBalet;
            cin >> cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
        }
            break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout << "======TEST CASE 6=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }

            Delo f = readDelo();
            cout << brojPretstaviNaDelo(pole, n, f);
        }
            break;

    };


    return 0;
}
