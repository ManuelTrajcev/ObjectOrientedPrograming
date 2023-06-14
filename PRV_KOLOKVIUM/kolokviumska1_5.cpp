#include <iostream>
#include <cstring>

using namespace std;

class Gitara {
private:
    char seriskiBroj[25];
    float nabavna;
    int proizvodstvo;
    char tip[50];
public:
    Gitara(char *tip = "", char *seriskiBroj = "", int proizvodstvo = 0, float nabavna = 0) {
        this->nabavna = nabavna;
        this->proizvodstvo = proizvodstvo;
        strcpy(this->tip, tip);
        strcpy(this->seriskiBroj, seriskiBroj);
    }

    Gitara(const Gitara &other) {
        this->nabavna = other.nabavna;
        this->proizvodstvo = other.proizvodstvo;
        strcpy(this->tip, other.tip);
        strcpy(this->seriskiBroj, other.seriskiBroj);
    }

    Gitara &operator=(const Gitara &other) {
        if (this != &other) {
            this->nabavna = other.nabavna;
            this->proizvodstvo = other.proizvodstvo;
            strcpy(this->tip, other.tip);
            strcpy(this->seriskiBroj, other.seriskiBroj);
        }
        return *this;
    }

    bool daliIsti(Gitara &g) {
        if (strcmp(this->seriskiBroj, g.seriskiBroj) == 0)
            return true;
        else
            return false;
    }

    void pecati() {
        cout << seriskiBroj << " " << tip << " " << nabavna << endl;
    }

    const char *getSeriski() const {
        return seriskiBroj;
    }

    float getNabavna() const {
        return nabavna;
    }

    int getGodina() const {
        return proizvodstvo;
    }

    const char *getTip() const {
        return tip;
    }

    ~Gitara() {}
};

class Magacin {
private:
    char ime[50];
    char lokacija[60];
    Gitara *gitari;
    int brObjekti;
    int otvaranjeGod;
public:
    Magacin(char *ime = "", char *lokacija = "", int otvaranjeGod = 0, Gitara *gitari = nullptr, int brObjekti = 0) {
        strcpy(this->ime, ime);
        strcpy(this->lokacija, lokacija);
        this->otvaranjeGod = otvaranjeGod;
        this->brObjekti = brObjekti;
        this->gitari = new Gitara[brObjekti];
        for (int i = 0; i < brObjekti; ++i) {
            this->gitari[i] = gitari[i];
        }
    }

    Magacin(const Magacin &other) {
        strcpy(this->ime, other.ime);
        strcpy(this->lokacija, other.lokacija);
        this->otvaranjeGod = other.otvaranjeGod;
        this->brObjekti = other.brObjekti;
        this->gitari = new Gitara[brObjekti];
        for (int i = 0; i < brObjekti; ++i) {
            this->gitari[i] = other.gitari[i];
        }
    }

    Magacin &operator=(const Magacin &other) {
        if (this != &other) {
            strcpy(this->ime, other.ime);
            strcpy(this->lokacija, other.lokacija);
            this->otvaranjeGod = other.otvaranjeGod;
            this->brObjekti = other.brObjekti;
            delete[] gitari;
            this->gitari = new Gitara[brObjekti];
            for (int i = 0; i < brObjekti; ++i) {
                this->gitari[i] = other.gitari[i];
            }
        }
        return *this;
    }

    ~Magacin() {
        delete[] gitari;
    }

    double vrednost() {
        double sum = 0;
        for (int i = 0; i < brObjekti; ++i) {
            sum += gitari[i].getNabavna();
        }
        return sum;
    }

    void dodadi(const Gitara &d) {
        Gitara *tmp = new Gitara[brObjekti + 1];
        for (int i = 0; i < brObjekti; ++i) {
            tmp[i] = gitari[i];
        }
        tmp[brObjekti++] = d;
        delete[] gitari;
        gitari = tmp;
    }

    void prodadi(Gitara p) {
        Gitara *tmp = new Gitara[brObjekti - 1];
        int j = 0;
        for (int i = 0; i < brObjekti; ++i) {
            if (!gitari[i].daliIsti(p)) {
                tmp[j] = gitari[i];
                j++;
            }
        }
        delete[] gitari;
        gitari = tmp;
        brObjekti = j;
    }

    void pecati(bool daliNovi) {
        cout << ime << " " << lokacija << endl;
        if (daliNovi) {
            for (int i = 0; i < brObjekti; ++i) {
                if (gitari[i].getGodina() > otvaranjeGod) {
                    gitari[i].pecati();
                }
            }
        } else {
            for (int i = 0; i < brObjekti; ++i) {
                gitari[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50], tip[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin >> tip;
        cin >> seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip, seriski, godina, cena);
        cout << g.getTip() << endl;
        cout << g.getSeriski() << endl;
        cout << g.getGodina() << endl;
        cout << g.getNabavna() << endl;
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1");
        kb.pecati(false);
    } else if (testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2005);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip, seriski, godina, cena);
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    } else if (testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2012);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    } else if (testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            cout << "gitara dodadi" << endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        Magacin kb3;
        kb3 = kb;
        kb3.pecati(true);
    } else if (testCase == 6) {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1", "Lokacija1", 2011);
        cin >> n;
        Gitara brisi;
        for (int i = 0; i < n; i++) {
            cin >> tip;
            cin >> seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip, seriski, godina, cena);
            if (i == 2)
                brisi = g;
            kb.dodadi(g);
        }
        cout << kb.vrednost() << endl;
        kb.prodadi(brisi);
        cout << "Po brisenje:" << endl;
        cout << kb.vrednost();
        Magacin kb3;
        kb3 = kb;
    }
    return 0;
}
