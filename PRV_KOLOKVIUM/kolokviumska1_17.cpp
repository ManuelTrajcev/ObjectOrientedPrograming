#include <iostream>
#include <cstring>

using namespace std;

enum Tip {
    LINUX, UNIX, WINDOWS
};

class OperativenSistem {
private:
    char *name;
    float version;
    Tip t;
    float size;
public:
    OperativenSistem(char *name = "", float version = 0, Tip t = UNIX, float size = 0) {
        this->version = version;
        this->t = t;
        this->size = size;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    OperativenSistem(const OperativenSistem &other) {
        this->version = other.version;
        this->t = other.t;
        this->size = other.size;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }

    ~OperativenSistem() {
        delete[] name;
    }

    OperativenSistem &operator=(const OperativenSistem &other) {
        if (this != &other) {
            this->version = other.version;
            this->t = other.t;
            this->size = other.size;
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
        }
        return *this;
    }

    void pecati() {
        cout << "Ime: " << name << " Verzija: " << version
             << " Tip: " << t << " Golemina:" << size << "GB" << endl;
    }

    bool ednakviSe(const OperativenSistem &os) {
        if ((strcmp(this->name, os.name) == 0) && (this->version == os.version) && (this->t == os.t) &&
            (this->size == size)) {
            return true;
        } else {
            return false;
        }
    }

    int sporediVerzija(const OperativenSistem &os) {
        if (this->version == os.version) {
            return 0;
        } else if (this->version > os.version) {
            return -1;
        } else {
            return 1;
        }
    }

    bool istaFamilija(const OperativenSistem &sporedba) {
        if ((strcmp(this->name, sporedba.name) == 0) && (this->t == sporedba.t)) {
            return true;
        } else {
            return false;
        }
    }

    float getVersion() const {
        return version;
    }
};

class Repozitorium {
private:
    char name[20];
    OperativenSistem *os;
    int n;
public:
    Repozitorium(char *name = "", int n = 0) {
        this->n = n;
        strcpy(this->name, name);
        this->n = n;
        os = new OperativenSistem[n];
        for (int i = 0; i < n; ++i) {
            this->os[i] = os[i];
        }
    }

    Repozitorium(const Repozitorium &other) {
        this->n = other.n;
        strcpy(this->name, other.name);
        this->n = other.n;
        os = new OperativenSistem[n];
        for (int i = 0; i < n; ++i) {
            this->os[i] = other.os[i];
        }
    }

    ~Repozitorium() {
        delete[] os;
    }

    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << name << endl;
        for (int i = 0; i < n; ++i) {
            os[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem) {
        int flag = 0;
        for (int i = 0; i < n; ++i) {
            if (this->os[i].ednakviSe(operativenSistem)) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            int j = 0;
            OperativenSistem *tmp;
            tmp = new OperativenSistem[n - 1];
            for (int i = 0; i < n; ++i) {
                if (!this->os[i].ednakviSe(operativenSistem)) {
                    tmp[j] = os[i];
                    j++;
                }
            }
            delete[] os;
            os = tmp;
            n--;
        }
    }

    void dodadi(const OperativenSistem &nov) {
        for (int i = 0; i < n; ++i) {
            if (this->os[i].istaFamilija(nov)) {
                if (os[i].sporediVerzija(nov) == 1) {
                    this->os[i] = nov;
                    return;
                }
            }
        }
        OperativenSistem *tmp;
        tmp = new OperativenSistem[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = os[i];
        }
        tmp[n] = nov;
        n++;
        delete[] os;
        os = tmp;
    }
};

int main() {
    char repoName[20];
    cin >> repoName;
    Repozitorium repozitorium = Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin >> brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i < brojOperativniSistemi; i++) {
        cin >> ime;
        cin >> verzija;
        cin >> tip;
        cin >> golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin >> ime;
    cin >> verzija;
    cin >> tip;
    cin >> golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
    cout << "=====Brishenje na operativen sistem=====" << endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}