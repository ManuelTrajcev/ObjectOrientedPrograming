#include<iostream>
#include<cstring>

using namespace std;

class Patnik {
private:
    char name[100];
    int klasa;
    bool bicycle;
public:
    Patnik(char *name = "", int klasa = 1, bool bicycle = false) {
        this->klasa = klasa;
        this->bicycle = bicycle;
        strcpy(this->name, name);
    }

    Patnik(const Patnik &other) {
        this->klasa = other.klasa;
        this->bicycle = other.bicycle;
        strcpy(this->name, other.name);
    }

    Patnik &operator=(const Patnik &other) {
        if (this != &other) {
            this->klasa = other.klasa;
            this->bicycle = other.bicycle;
            strcpy(this->name, other.name);
        }
        return *this;
    }

    void print() {
        cout << name << endl;
        cout << klasa << endl;
        if (bicycle)
            cout << "1" << endl;
        else
            cout << "0" << endl;
    }

    friend ostream &operator<<(ostream &os, const Patnik &patnik) {
        os << patnik.name << endl;
        os << patnik.klasa << endl;
        os << patnik.bicycle;
        return os;
    }

    bool isBicycle() const {
        return bicycle;
    }

    int getKlasa() const {
        return klasa;
    }

    ~Patnik() {}
};

class Voz {
private:
    char endDest[100];
    Patnik *array;
    int n;
    int b;
    int current;
public:
    Voz(char *endDest = "", int b = 0) {
        this->current = 0;
        this->n = 0;
        this->array = new Patnik[n];
        this->b = b;
        strcpy(this->endDest, endDest);
    }

    Voz(const Voz &other) {
        this->current = other.current;
        this->n = other.n;
        this->b = other.b;
        strcpy(this->endDest, other.endDest);
        this->array = new Patnik[n];
        for (int i = 0; i < n; ++i) {
            this->array[i] = array[i];
        }
    }

    Voz &operator=(const Voz &other) {
        if (this != &other) {
            this->current = other.current;
            this->n = other.n;
            this->b = other.b;
            delete[] this->array;
            strcpy(this->endDest, other.endDest);
            this->array = new Patnik[n];
            for (int i = 0; i < n; ++i) {
                this->array[i] = array[i];
            }
        }
        return *this;
    }

    Voz &operator+=(const Patnik &p) {
        if (b == 0 && p.isBicycle())
            return *this;
        Patnik *tmp = new Patnik[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = array[i];
        }
        tmp[n++] = p;
        delete[] array;
        array = tmp;
        return *this;
    }


    friend ostream &operator<<(ostream &os, const Voz &voz) {
        os << voz.endDest << endl;
        for (int i = 0; i < voz.n; ++i) {
            os << voz.array[i]<<"\n\n";
        }
        return os;
    }

    void patniciNemaMesto() {
        int prvaKlasaJok = 0, vtoraKlasaJok = 0;
        for (int i = 0; i < n; ++i) {
            if (array[i].getKlasa() == 1) {
                if (array[i].isBicycle()) {
                    if ((current + 1) > b)
                        prvaKlasaJok++;
                    else
                        current++;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (array[i].getKlasa() == 2) {
                if (array[i].isBicycle()) {
                    if ((current + 1) > b)
                        vtoraKlasaJok++;
                    else
                        current++;
                }
            }
        }

        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << prvaKlasaJok << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << vtoraKlasaJok << endl;
    }

    ~Voz() {
        delete[] array;
    }
};


int main() {
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++) {
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
