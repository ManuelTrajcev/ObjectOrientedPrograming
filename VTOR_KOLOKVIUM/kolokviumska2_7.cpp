#include<iostream>
#include<string.h>

using namespace std;

class OutOfBoundException {
private:

public:
    void print() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(const char *smetka = "", int pin = 0) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    virtual int tezinaProbivanje() {
        int tmp = pin, count = 0;
        while (tmp != 0) {
            count++;
            tmp /= 10;
        }
        return count;
    }

    virtual Karticka &operator+=(int p) {
        return *this;
    }

    void setDopPin(bool t) {
        povekjePin = t;
    }

    bool getDopolnitelenPin() {
        return povekjePin;
    }

    const char *getSmetka() const {
        return smetka;
    }


};

class SpecijalnaKarticka : public Karticka {
private:
    int n;
    int *dopPins;
    const static int MAX_PINS;
public:
    SpecijalnaKarticka(const char *smetka = "", int pin = 0) : Karticka(smetka, pin) {
        this->n = 0;
        this->dopPins = nullptr;
        setDopPin(true);
    }

    int tezinaProbivanje() {
        return Karticka::tezinaProbivanje() + n;
    }

    SpecijalnaKarticka &operator+=(int p) {
        if (n == MAX_PINS) {
            throw OutOfBoundException();
        }
        int *tmp = new int[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = this->dopPins[i];
        }
        tmp[n++] = p;
        delete[] dopPins;
        dopPins = tmp;
        return *this;
    }

    ~SpecijalnaKarticka() {
        delete[] dopPins;
    }


};

const int SpecijalnaKarticka::MAX_PINS = 4;


class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka **karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(karticki[i]));
            } else this->karticki[i] = new Karticka(*karticki[i]);
        }
        this->broj = broj;
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) delete karticki[i];
    }

    static void setLIMIT(int l) {
        LIMIT = l;
    }

    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < broj; ++i) {
            if (karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << karticki[i]->getSmetka() << ": " << karticki[i]->tezinaProbivanje() << endl;
            }
        }
    }

    void dodadiDopolnitelenPin(char *s, int p) {
        for (int i = 0; i < broj; ++i) {
            if (karticki[i]->getDopolnitelenPin()) {
                if (strcmp(s, karticki[i]->getSmetka()) == 0) {
                    *(karticki[i]) += p;
                }
            }
        }
    }

};

int Banka::LIMIT = 7;


int main() {
    Karticka **niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka *[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;
        try {
            komercijalna.dodadiDopolnitelenPin(smetka, pin);
        } catch (OutOfBoundException exception) {
            exception.print();
        }
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();
    return 0;
}
