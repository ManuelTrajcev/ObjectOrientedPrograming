#include<iostream>
#include<string.h>

using namespace std;

class BadInputException {
private:
public:
    void msg() {
        cout << "Greshna opisna ocenka" << endl;
    }
};

class StudentKurs {
protected:
    char ime[30];
    int finalenIspit;
    bool daliUsno;
    static int MAX;
public:
    StudentKurs(const char *ime = "", int finalenIspit = 0) {
        strcpy(this->ime, ime);
        this->finalenIspit = finalenIspit;
        this->daliUsno = false;
    }

    virtual int ocenka() {
        return finalenIspit;
    }

    friend ostream &operator<<(ostream &os, StudentKurs &kurs) {
        os << kurs.ime << " --- " << kurs.ocenka();
        return os;
    }

    virtual StudentKurs &operator+=(char *oc) {
        return *this;
    }

    bool getDaliUsno() {
        return daliUsno;
    }

    const char *getIme() const {
        return ime;
    }

    static void setMAX(int m) {
        MAX = m;
    }

    virtual void a(){}
};

int StudentKurs::MAX = 10;

class StudentKursUsno : public StudentKurs {
private:
    char *usna;
public:
    StudentKursUsno(const char *ime = "", int finalenIspit = 0, const char *usna = "") : StudentKurs(ime,
                                                                                                     finalenIspit) {
        this->usna = new char[strlen(usna) + 1];
    }

    int ocenka() {
        if (strcmp(usna, "odlicen") == 0 && finalenIspit < MAX) {
            finalenIspit += 2;
        } else if (strcmp(usna, "dobro") == 0 && finalenIspit < MAX) {
            finalenIspit += 1;
        } else if (strcmp(usna, "losho") == 0) {
            finalenIspit -= 1;
        }
        return finalenIspit;
    }

    StudentKursUsno &operator+=(char *oc) override {
        char tmp[20];
        int i = 0;
        strcpy(tmp, oc);
        while (tmp[i] != '\0') {
            i++;
            if (!isalpha(tmp[i])) {
                throw BadInputException();
            }
        }
        this->usna = new char[strlen(oc) + 1];
        strcpy(this->usna, usna);
        return *this;
    }

     void a(){}

};


class KursFakultet {
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs **studenti, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()) {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno *>(studenti[i]));
            } else this->studenti[i] = new StudentKurs(*studenti[i]);
        }
        this->broj = broj;
    }

    void pecatiStudenti() {
        cout << "Kursot " << naziv << " go polozile:" << endl;
        for (int i = 0; i < broj; ++i) {
            if (studenti[i]->ocenka() > 5) {
                cout << *(studenti[i]) << endl;
            }
        }
    }

    KursFakultet postaviOpisnaOcenka(char *ime, char *opisnaOcenka) {
        for (int i = 0; i < broj; ++i) {
            if (strcmp(studenti[i]->getIme(), ime) == 0) {
                *studenti[i] += opisnaOcenka;
            }
        }
        return *this;
    }
};

int main() {

    StudentKurs **niza;
    int n, m, ocenka;
    char ime[30], opisna[10];
    bool daliUsno;
    cin >> n;
    niza = new StudentKurs *[n];
    for (int i = 0; i < n; i++) {
        cin >> ime;
        cin >> ocenka;
        cin >> daliUsno;
        if (!daliUsno)
            niza[i] = new StudentKurs(ime, ocenka);
        else
            niza[i] = new StudentKursUsno(ime, ocenka);
    }

    KursFakultet programiranje("OOP", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> ime >> opisna;
        try {
            programiranje.postaviOpisnaOcenka(ime, opisna);
        } catch (BadInputException exception) {
            exception.msg();
        }
    }

    StudentKurs::setMAX(9);
    programiranje.pecatiStudenti();

}
