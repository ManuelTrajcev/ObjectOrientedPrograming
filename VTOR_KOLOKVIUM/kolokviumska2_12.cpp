#include <iostream>
#include <cstring>

using namespace std;

enum tip {
    smartfon, kompjuter
};

char *enumValues[2]{
        "Mobilen", "Laptop"
};

class InvalidProductionDate {
public:
    void message() {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device {
    char ime[100];
    tip tipDevice;
    static float potrebniCasovi;
    int godina;
public:
    Device(const char *ime = "", tip tipDevice = smartfon, int godina = 0) {
        strcpy(this->ime, ime);
        this->tipDevice = tipDevice;
        this->godina = godina;
    }

    Device(const Device &other) {
        strcpy(this->ime, other.ime);
        this->tipDevice = other.tipDevice;
        this->godina = other.godina;
    }

    Device &operator=(const Device &other) {
        if (this != &other) {
            strcpy(this->ime, other.ime);
            this->tipDevice = other.tipDevice;
            this->godina = other.godina;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Device &device) {
        os << device.ime << endl;
        os << enumValues[device.tipDevice] << " ";
        if (device.godina > 2015) {
            if (device.tipDevice == 1) {
                os << device.potrebniCasovi + 4;
            } else {
                os << device.potrebniCasovi + 2;
            }
        } else if (device.tipDevice == 1) {
            os << device.potrebniCasovi + 2;
        } else {
            os << device.potrebniCasovi;
        }
        os << endl;
        return os;
    }

    int getGodina() const {
        return godina;
    }

    static void setPocetniCasovi(float potrebniCasovi);
};

float Device::potrebniCasovi = 1;

void Device::setPocetniCasovi(float potrebniCasovi) {
    Device::potrebniCasovi = potrebniCasovi;
}


class MobileServis {
private:
    char adresa[100];
    Device *devices;
    int n;
public:
    MobileServis(const char *adresa = "") {
        this->n = 0;
        strcpy(this->adresa, adresa);
        this->devices = new Device[n];
    }

    MobileServis(const MobileServis &other) {
        strcpy(this->adresa, other.adresa);
        this->n = other.n;
        this->devices = new Device[other.n];
        for (int i = 0; i < n; ++i) {
            this->devices[i] = other.devices[i];
        }
    }

    MobileServis &operator=(const MobileServis &other) {
        if (this != &other) {
            strcpy(this->adresa, other.adresa);
            delete[] devices;
            this->devices = new Device[other.n];
            for (int i = 0; i < n; ++i) {
                this->devices[i] = other.devices[i];
            }
        }
        return *this;
    }

    MobileServis &operator+=(Device &add) {
        if (add.getGodina() > 2019 || add.getGodina() < 2000) {
            throw InvalidProductionDate();
        } else {
            Device *tmp = new Device[n + 1];
            for (int i = 0; i < n; ++i) {
                tmp[i] = devices[i];
            }
            tmp[n++] = add;
            delete[] devices;
            devices = tmp;
            return *this;
        }
    }

    void pecatiCasovi() {
        cout << "Ime: " << adresa << endl;
        float sum = 0;
        for (int i = 0; i < n; ++i) {
            cout << devices[i];
        }
    }

    ~MobileServis() {
        delete[] devices;
    }
};

int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try {
                t += tmp;
            } catch (InvalidProductionDate e) {
                e.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

