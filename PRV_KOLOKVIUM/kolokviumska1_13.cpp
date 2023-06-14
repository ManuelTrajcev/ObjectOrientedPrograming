#include<iostream>
#include<cstring>

using namespace std;

class Zichara {
private:
    char *place;
    int price;
public:
    Zichara(const char *place = "", int price = 0) {
        this->price = price;
        this->place = new char[strlen(place) + 1];
        strcpy(this->place, place);
    }

    Zichara(const Zichara &other) {
        this->price = other.price;
        this->place = new char[strlen(other.place) + 1];
        strcpy(this->place, other.place);
    }

    Zichara &operator=(const Zichara &other) {
        if (this != &other) {
            this->price = other.price;
            delete[] this->place;
            this->place = new char[strlen(other.place) + 1];
            strcpy(this->place, other.place);
        }
        return *this;
    }

    ~Zichara() {
        delete[] this->place;
    }

    int getPrice() const {
        return price;
    }
};

class PlaninarskiDom {
private:
    char name[15];
    int pricePerSeason[2];
    char klasa;
    bool haveZicara;
    Zichara *zichara;
    int n;
public:
    PlaninarskiDom(const char *name = "", int *pricePerSeason = nullptr, char klasa = 'a') {
        strcpy(this->name, name);
        this->klasa = klasa;
        this->haveZicara = false;
        this->zichara = nullptr;
        this->n = 0;
        if (pricePerSeason != nullptr) {
            for (int i = 0; i < 2; ++i) {
                this->pricePerSeason[i] = pricePerSeason[i];
            }
        }
    }

    PlaninarskiDom(const PlaninarskiDom &other) {
        strcpy(this->name, other.name);
        this->klasa = other.klasa;
        this->haveZicara = other.haveZicara;
        this->zichara = other.zichara;
        this->n = other.n;
        this->zichara = new Zichara[n];
        for (int i = 0; i < n; ++i) {
            this->zichara[i] = other.zichara[i];
        }
        for (int i = 0; i < 2; ++i) {
            this->pricePerSeason[i] = other.pricePerSeason[i];
        }
    }

    PlaninarskiDom &operator=(const PlaninarskiDom &other) {
        if (this != &other) {
            strcpy(this->name, other.name);
            this->klasa = other.klasa;
            this->haveZicara = other.haveZicara;
            this->zichara = other.zichara;
            this->n = other.n;
            this->zichara = new Zichara[n];
            for (int i = 0; i < n; ++i) {
                this->zichara[i] = other.zichara[i];
            }
            for (int i = 0; i < 2; ++i) {
                this->pricePerSeason[i] = other.pricePerSeason[i];
            }
        }
        return *this;
    }

    void setZichara(Zichara z) {
        haveZicara = true;
        Zichara *tmp = new Zichara[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = this->zichara[i];
        }
        tmp[n++] = z;
        delete[] zichara;
        zichara = tmp;
    }

    friend ostream &operator<<(ostream &os, const PlaninarskiDom &dom) {
        os << dom.name << " klasa:" << dom.klasa;
        if (dom.haveZicara) {
            os << " so Zichara";
        }
        os << endl;
        return os;
    }

    bool operator<=(char c) const {
        if (klasa >= c) {
            return true;
        } else {
            return false;
        }
    }

    PlaninarskiDom &operator--() {
        if (klasa == 'F') {
            return *this;
        } else {
            this->klasa++;
            return *this;
        }
    }

    void presmetajDnevenPrestoj(int day, int month, int &cena) {
        cena = 0;
        if (day < 1 || day > 31 || month < 1 || month > 12) {
            throw (1);
        } else {
            if (month >= 4 && month < 9) {
                cena += pricePerSeason[0];
            } else {
                cena += pricePerSeason[1];
            }
            if (haveZicara) {
                cena += zichara[0].getPrice();
            }
            return;
        }
    }
};

int main() {

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15], mestoZichara[30], klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin >> imePlaninarskiDom;
    for (int i = 0; i < 2; i++) cin >> ceni[i];
    cin >> klasa;
    cin >> daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin >> mestoZichara >> dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom, ceni, klasa);
        Zichara r(mestoZichara, dnevnakartaZichara);
        pom.setZichara(r);
        p = pom;
    } else {
        PlaninarskiDom *pok = new PlaninarskiDom(imePlaninarskiDom, ceni, klasa);
        p = *pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena = 0;
    int den, mesec;
    cin >> den >> mesec;
    try {
        p.presmetajDnevenPrestoj(den, mesec, cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout << "Informacii za PlaninarskiDomot:" << endl;
        cout << p;
        if (p <= 'D')
            cout << "Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout << "Cenata za " << den << "." << mesec << " e " << cena; //се печати цената за дадениот ден и месец
    }
    catch (int) {
        cout << "Mesecot ili denot e greshno vnesen!";
    }
}


