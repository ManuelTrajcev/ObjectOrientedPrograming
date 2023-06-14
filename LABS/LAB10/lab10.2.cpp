#include <iostream>
#include <cstring>

using namespace std;

class InvalidTimeException {
private:

public:
    void print() {
        cout << "The time is not valid" << endl;
    }
};

class Race {
private:
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
public:
    Race(const char *city = "", int year = 0, int month = 0, float bestTime = 0, float length = 0) : year(year),
                                                                                                     month(month),
                                                                                                     bestTime(bestTime),
                                                                                                     length(length) {
        strcpy(this->city, city);
    }

    virtual float heaviness() {
        return bestTime / length;
    }

    friend ostream &operator<<(ostream &os, Race &race) {
        os << race.city << " " << race.month << "." << race.year << " "
           << race.heaviness() << endl;
        return os;
    }
};

class CarRace : public Race {
private:
    float *bestTimes;
    int n;
    int m;
    static float CAR_COEF;
public:
    CarRace(const char *city = "", int year = 0, int month = 0, float bestTime = 0, float length = 0,
            const float *bestTimes = nullptr, int n = 0, int m = 0) : Race(city,
                                                                           year,
                                                                           month,
                                                                           bestTime,
                                                                           length),
                                                                      n(n),
                                                                      m(m) {

        this->bestTimes = new float[n];
        for (int i = 0; i < n; ++i) {
            this->bestTimes[i] = bestTimes[i];
        }
    }

    void setNumberLaps(int num) {
        this->n = num;
    }

    static void setKoeficient(float carCoef) {
        CAR_COEF = carCoef;
    }

    float avg() {
        float sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += bestTimes[i];
        }
        return sum / n * CAR_COEF;
    }

    float heaviness() {

        if (m > 15) {
            return (Race::heaviness() + avg()) + 0.1 * (Race::heaviness() + avg());
        }
        return Race::heaviness() + avg();
    }

    CarRace &operator+=(float newTime) {
        float *tmp = new float[n + 1];
        if (newTime < 10) {
            throw InvalidTimeException();
        }
        for (int i = 0; i < n; ++i) {
            tmp[i] = this->bestTimes[i];
        }
        tmp[n++] = newTime;
        delete[] bestTimes;
        bestTimes = tmp;
        return *this;
    }
};

float CarRace::CAR_COEF = 0.3;


int main() {
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int izbor;
    int numberLaps;

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        Race t(city, year, month, bestTime, length);
        cout << t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        CarRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        CarRace mgt2;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (izbor == 1) {
                niza[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje novo najdobro vreme za prvata CarRace
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++) {
            CarRace *nn = dynamic_cast<CarRace *>(niza[i]);
            if (nn != 0) {
                flag = 0;
                (*nn) += best;
                break;
            }
        }


        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        CarRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(0);
        float vreme1, vreme2;
        cin >> vreme1 >> vreme2;
        try {
            mgt += vreme1;
            mgt += vreme2;
        }
        catch (InvalidTimeException e) {
            e.print();
        }
        cout << mgt;
    }

    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (izbor == 1) {
                niza[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        CarRace::setKoeficient(0.7);
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }


    return 0;
}