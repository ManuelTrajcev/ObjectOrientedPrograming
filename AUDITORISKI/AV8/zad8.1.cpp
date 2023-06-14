#include <iostream>
#include <cstring>

using namespace std;

class Publikacija {
private:
    char naziv[100];
protected:
    int godina;
public:
    const char *getNaziv() {
        return naziv;
    }

public:
    Publikacija(char *naziv, int godina) : godina(godina) {
        strcpy(this->naziv, naziv);
    }

    int getGodina() const {
        return godina;
    }

    void pecati() {
        cout << "Naziv: " << naziv << " - " << godina << endl;
    }
};

class Kniga : public Publikacija {
private:
    int brojStrani;
public:
    Kniga(char *naziv, int godina, int brojStrani) : Publikacija(naziv, godina), brojStrani(brojStrani) {

    }

    void pecatiGodina() {
        cout << "Godina: " << godina << endl;
    }

    void brStrani() {
        cout << "Broj na strani: " << brojStrani << endl;
    }

    void pecatiNaziv() {
        Publikacija::pecati();
    }
};

class Vesnik : protected Publikacija {
private:
    int broj;
public:
    Vesnik(char *naziv, int godina, int broj) : Publikacija(naziv, godina), broj(broj) {

    }

    void pecatiGodinaVesnik() {
        cout << getGodina();
    }

    void pecatiNazivVesnik() {
        cout << getNaziv();
    }

    void pecatiBroj() {
        cout << broj << endl;
    }
};

class DnevenVesnik : private Vesnik {
private:
    int den;
    int mesec;
public:
    DnevenVesnik(char *naziv, int godina, int broj, int den, int mesec) : Vesnik(naziv, godina, broj), den(den),
                                                                          mesec(mesec) {

    }

    using Vesnik::pecati;

    using Vesnik::pecatiBroj;


};

int main() {
    Publikacija p("Tabernakul", 1992);
    p.pecati(); // public - функција
    Kniga *k = new Kniga("ProsvetnoDelo", 1900, 123);
    k->pecati(); //pecati e public во Kniga
    k->pecatiGodina(); // public - функција
    // cout<<k->getNaziv(); // грешка! protected - функција
    Vesnik *s = new Vesnik("Tea", 2013, 30);
    // s->pecati(); //грешка! protected - функција
    // cout<<s->getGodina(); // грешка! protected - функција
    s->pecatiNazivVesnik(); // public - функција
    DnevenVesnik d("Vest", 2, 3, 2014, 25);
    d.pecati(); //public-функција
    // d.pecatiNazivVesnik(); // грешка! private - функција
    // cout<<d.getNaziv(); // грешка! private – функција
    return 0;
}