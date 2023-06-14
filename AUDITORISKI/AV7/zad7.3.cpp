#include <iostream>
#include <cstring>

using namespace std;


class Nedviznina {
protected:
    char *adresa;
    int kvadratura;
    int cenaZaKv;
public:
    Nedviznina(char *adresa="", int kvadratura=0, int cenaZaKv=0) {
        this->kvadratura = kvadratura;
        this->cenaZaKv = cenaZaKv;
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
    }

    int cena() {
        return cenaZaKv * kvadratura;
    }

    void pecati() {
        cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cenaZaKv << endl;
        cout << "Danokot za: " << adresa << ", e: " << danokNaImot();
    }

    float danokNaImot() {
        return cena() * 0.05;
    }

    friend istream &operator>>(istream &is, Nedviznina &nedviznina) {
        is >> nedviznina.adresa >> nedviznina.kvadratura >>
           nedviznina.cenaZaKv;
        return is;
    }
};

class Vila : public Nedviznina {
private:
    int danokNaLuksuz;
public:
    Vila(char *adresa="", int kvadratura=0, int cenaZaKv=0, int danokNaLuksuz=0) : Nedviznina(adresa, kvadratura, cenaZaKv),
                                                                          danokNaLuksuz(danokNaLuksuz) {

    }

    void pecati() {
        cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po Kvadrat: " << cenaZaKv << ", Danok na luksuz: "
             << danokNaLuksuz << endl;
        cout << "Danokot za: " << adresa << ", e: " << danokNaImot();
    }

    float danokNaImot() {
        return cena() * 0.05 * danokNaLuksuz / 100;
    }

    friend istream &operator>>(istream &is, Vila &vila) {
        is >> vila.adresa >> vila.kvadratura >>
           vila.cenaZaKv >> vila.danokNaLuksuz;
        return is;
    }
};


int main() {
    char adresa[50];
    int kvadratura;
    int cenaZaKv;
    int danokNaLukus;
    Nedviznina nd;
    cin >> nd;
    nd.pecati();
    nd.danokNaImot();
    cin >> adresa >> kvadratura >> cenaZaKv >> danokNaLukus;
    Vila v(adresa, kvadratura, cenaZaKv, danokNaLukus);
    v.pecati();
    v.danokNaImot();
    return 0;
}