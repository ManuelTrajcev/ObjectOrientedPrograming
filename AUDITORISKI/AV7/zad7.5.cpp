#include <iostream>
#include <cstring>

using namespace std;

class Lekar {
protected:
    int faksimil;
    char ime[10];
    char prezime[10];
    float pocetnaPlata;
public:
    Lekar(int faksimil, char *ime, char *prezime, float pocetnaPlata) : faksimil(faksimil),
                                                                        pocetnaPlata(pocetnaPlata) {
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
    }

    void pecati() {
        cout << faksimil << " " << ime << " " << prezime << endl;
        cout << "Osnovnata plata na lekarot e: " << plata() << endl;
    }

    float plata() {
        return pocetnaPlata;
    }
};

class MaticenLekar : public Lekar{
private:
    int pacienti;
    float *kotizacii;
public:
    MaticenLekar(int faksimil, char *ime, char *prezime, float pocetnaPlata, int pacienti, float *kotizacii) : Lekar(
            faksimil, ime, prezime, pocetnaPlata){
        this->pacienti = pacienti;
        this->kotizacii = new float[pacienti];
        for (int i = 0; i < pacienti; ++i) {
            this->kotizacii[i] = kotizacii[i];
        }
    }

    float avgKotizacii(){
        float sum = 0;
        for (int i = 0; i < pacienti ; ++i) {

        }
    }

    void pecati() {
        Lekar :: plata();
        cout << avgKotizacii()<<endl;
    }
};

int main() {

    return 0;
}