#include<iostream>
#include<cstring>

using namespace std;

class Koncert {
protected:
    char naziv[100];
    char lokacija[100];
    static float sezonskiPopust;
    float c;
public:
    Koncert(const char *naziv = "", const char *lokacija = "", float c = 0) {
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->c = c;
    }

    virtual float cena() {
        float sum = c - (c * sezonskiPopust);
        return sum;
    }

    char *getNaziv() {
        return naziv;
    }

    static float getSezonskiPopust() {
        return sezonskiPopust;
    }

    static void setSezonskiPopust(float s) {
        sezonskiPopust = s;
    }
};

float Koncert::sezonskiPopust = 0.2;

class ElektronskiKoncert : public Koncert {
private:
    char *DJ;
    float vremetraenje;
    bool dnevna;
public:
    ElektronskiKoncert(const char *naziv = "", const char *lokacija = "", float c = 0, const char *DJ = "",
                       float vremetraenje = 0, bool dnevna = false) : Koncert(naziv, lokacija, c) {
        this->DJ = new char[strlen(DJ) + 1];
        strcpy(this->DJ, DJ);
        this->vremetraenje = vremetraenje;
        this->dnevna = dnevna;
    }

    ElektronskiKoncert(const ElektronskiKoncert &other) {
        strcpy(this->naziv, other.naziv);
        strcpy(this->lokacija, other.lokacija);
        this->c = other.c;
        this->DJ = new char[strlen(other.DJ) + 1];
        strcpy(this->DJ, other.DJ);
        this->vremetraenje = other.vremetraenje;
        this->dnevna = other.dnevna;
    }

    ElektronskiKoncert &operator=(const ElektronskiKoncert &other) {
        if (this != &other) {
            strcpy(this->naziv, other.naziv);
            strcpy(this->lokacija, other.lokacija);
            this->c = other.c;
            delete[] this->DJ;
            this->DJ = new char[strlen(other.DJ) + 1];
            strcpy(this->DJ, other.DJ);
            this->vremetraenje = other.vremetraenje;
            this->dnevna = other.dnevna;
        }
        return *this;
    }

    ~ElektronskiKoncert() {
        delete[] this->DJ;
    }

    float cena() {
        float sum = Koncert::cena();
        if (vremetraenje > 7) {
            sum += 360;
        } else if (vremetraenje > 5) {
            sum += 150;
        }
        if (dnevna) {
            sum -= 50;
        } else {
            sum += 100;
        }
        return sum;
    }
};

void najskapKoncert(Koncert **koncerti, int n) {
    int counter = 0;
    Koncert *max = koncerti[0];
    for (int i = 1; i < n; ++i) {
        if (koncerti[i]->cena() > max->cena()) {
            max = koncerti[i];
        }
        ElektronskiKoncert *casted = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if (casted) {
            counter++;
        }
    }
    cout << "Najskap koncert: " << max->getNaziv() << " " << max->cena() << endl;
    cout << "Elektronski koncerti: " << counter << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski) {
    for (int i = 0; i < n; ++i) {
        if (elektronski) {
            ElektronskiKoncert *casted = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
            if (casted) {
                if (strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                    cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                    return true;
                }
            }
        } else {
            if (strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                return true;
            }
        }
    }
    return false;
}

int main() {

    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin >> tip;
    if (tip == 1) {//Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    } else if (tip == 2) {//cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    } else if (tip == 3) {//ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust "
             << s.getSezonskiPopust() << endl;
    } else if (tip == 4) {//cena - ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;
    } else if (tip == 5) {//najskapKoncert

    } else if (tip == 6) {//prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    } else if (tip == 7) {//prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else
            cout << "Ne e pronajden" << endl;

    } else if (tip == 8) {//smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}
