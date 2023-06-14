#include <iostream>
#include <cstring>

using namespace std;

class FudblaskaEkipa {
protected:
    char coach[100];
    int goals[10];
public:
    FudblaskaEkipa(const char *coach = "", int *goals = nullptr) {
        strcpy(this->coach, coach);
        if (goals != nullptr)
            for (int i = 0; i < 10; ++i) {
                this->goals[i] = goals[i];
            }
    }

    virtual int uspeh() = 0;

    virtual void print() = 0;

    friend ostream &operator<<(ostream &os, FudblaskaEkipa &fe) {
        fe.print();
        os << fe.coach << endl;
        os << fe.uspeh() << endl;
        return os;
    }

    FudblaskaEkipa &operator+=(int g) {
        int tmp[10];
        for (int i = 0; i < 9; ++i) {
            tmp[i] = goals[i + 1];
        }
        tmp[9] = g;
        for (int i = 0; i < 10; ++i) {
            goals[i] = tmp[i];
        }
        return *this;
    }

    bool operator>(FudblaskaEkipa *rhs) {
        if (this->uspeh() > rhs->uspeh()) {
            return true;
        } else {
            return false;
        }
    }


};

class Klub : public FudblaskaEkipa {
private:
    char name[100];
    int tit;
public:
    Klub(char *coach, int *goals, char *name, int tit) : FudblaskaEkipa(coach, goals) {
        strcpy(this->name, name);
        this->tit = tit;
    }

    int uspeh() {
        int sum = 0;
        for (int i = 0; i < 10; ++i) {
            sum += goals[i];
        }
        sum *= 3;
        sum += (tit * 1000);
        return sum;
    }

    void print() {
        cout << name << endl;
    }
};

class Reprezentacija : public FudblaskaEkipa {
private:
    char country[100];
    int participated;
public:
    Reprezentacija(char *coach, int *goals, char *country, int participated) : FudblaskaEkipa(coach, goals) {
        strcpy(this->country, country);
        this->participated = participated;
    }

    int uspeh() {
        int sum = 0;
        for (int i = 0; i < 10; ++i) {
            sum += goals[i];
        }
        sum *= 3;
        sum += (participated * 50);
        return sum;
    }

    void print() {
        cout << country << endl;
    }

};

void najdobarTrener(FudblaskaEkipa **fe, int n) {
    FudblaskaEkipa *max = fe[0];
    for (int i = 0; i < n; ++i) {
        if (*fe[i] > max) {
            max = fe[i];
        }
    }
    cout << *max;
}


int main() {
    int n;
    cin >> n;
    FudblaskaEkipa **ekipi = new FudblaskaEkipa *[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete[] ekipi;
    return 0;
}