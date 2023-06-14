#include <cstring>
#include <iostream>

using namespace std;

class Ucesnik {
private:
    char *name;
    bool gender;
    int age;
public:
    Ucesnik(char *name = "", bool gender = true, int age = 0) {
        this->gender = gender;
        this->age = age;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Ucesnik(const Ucesnik &other) {
        this->gender = other.gender;
        this->age = other.age;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }

    Ucesnik &operator=(const Ucesnik &other) {
        if (this != &other) {
            this->gender = other.gender;
            this->age = other.age;
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
        }
        return *this;
    }

    ~Ucesnik() {
        delete[] name;
    }

    friend ostream &operator<<(ostream &o, Ucesnik &u) {
        o << u.name << endl;
        if (u.gender) {
            o << "mashki" << endl;
        } else {
            o << "zhenski" << endl;
        }
        o << u.age << endl;
        return o;
    }

    bool operator>(const Ucesnik &other) {
        if (this->age < other.age)
            return true;
        else
            return false;
    }

    int getAge() const {
        return age;
    }
};

class Maraton {
private:
    char location[100];
    Ucesnik *array;
    int count;
public:
    Maraton(char *location = "", Ucesnik *array = nullptr, int count = 0) {
        this->count = count;
        strcpy(this->location, location);
        this->array = new Ucesnik[count];
        for (int i = 0; i < count; ++i) {
            this->array[i] = array[i];
        }
    }

    Maraton(const Maraton &other) {
        this->count = other.count;
        strcpy(this->location, other.location);
        this->array = new Ucesnik[other.count];
        for (int i = 0; i < other.count; ++i) {
            this->array[i] = other.array[i];
        }
    }

    ~Maraton() {
        delete[] array;
    }

    Maraton &operator+=(Ucesnik &ucesnik) {
        Ucesnik *tmp = new Ucesnik[count + 1];
        for (int i = 0; i < count; ++i) {
            tmp[i] = array[i];
        }
        tmp[count++] = ucesnik;
        delete[] array;
        array = tmp;
        return *this;
    }

    float prosecnoVozrast() {
        float avg = 0;
        for (int i = 0; i < count; ++i) {
            avg += array[i].getAge();
        }
        return avg / count;
    }

    void pecatiPomladi(Ucesnik &u) {
        for (int i = 0; i < count; ++i) {
            if (array[i] > u) {
                cout << array[i];
            }
        }
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik *[n];
    for (int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for (int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete[] u;
    return 0;
}