#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

class SMS {
protected:
    float basePrice;
    char mob[20];
    static const int DDV;
public:
    SMS(const char *mob = "", float basePrice = 0) {
        this->basePrice = basePrice;
        strcpy(this->mob, mob);
    }

    virtual float SMS_cena() = 0;

    friend ostream &operator<<(ostream &os, SMS &sms) {
        os << "Tel: " << sms.mob << " - cena: " << sms.SMS_cena() << "den." << endl;
        return os;
    }
};

class RegularSMS : public SMS {
private:
    bool roaming;
    char msg[2000];
    static int RS;
public:
    RegularSMS(const char *mob = "", float basePrice = 0, const char *msg = "", bool roaming = false) : SMS(mob,
                                                                                                            basePrice),
                                                                                                        roaming(roaming) {
        strcpy(this->msg, msg);
    }

    float SMS_cena() {
        float m = strlen(msg);
        m /= 160;
        int p = ceil(m);
        basePrice *= p;
        if (roaming) {
            basePrice += basePrice * RS / 100;
        } else {
            basePrice += (DDV * basePrice / 100);
        }

        return basePrice;
    }

    static void set_rProcent(int p) {
        RS = p;
    }
};

class SpecialSMS : public SMS {
private:
    bool charity;
    static int SS;
public:
    SpecialSMS(const char *mob = "", float basePrice = 0, bool charity = false) : SMS(mob, basePrice),
                                                                                  charity(charity) {
    }

    float SMS_cena() {
        if (charity) {
            return basePrice;
        } else {
            basePrice += (basePrice * SS / 100);
        }
        return basePrice;
    }

    static void set_sProcent(int p) {
        SS = p;
    }
};

const int SMS::DDV = 18;
int RegularSMS::RS = 300;
int SpecialSMS::SS = 150;

void vkupno_SMS(SMS **poraka, int n) {
    float sumR = 0, sumS = 0;
    int counterR = 0, counterS = 0;
    for (int i = 0; i < n; ++i) {
        RegularSMS *casted = dynamic_cast<RegularSMS *>(poraka[i]);
        if (casted) {
            counterR++;
            sumR += poraka[i]->SMS_cena();
        } else {
            counterS++;
            sumS += poraka[i]->SMS_cena();
        }
    }
    cout << "Vkupno ima " << counterR << " regularni SMS poraki i nivnata cena e: " << sumR << endl;
    cout << "Vkupno ima " << counterS << " specijalni SMS poraki i nivnata cena e: " << sumS << endl;
}

int main() {

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2) {
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3) {
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            } else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4) {
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5) {
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
