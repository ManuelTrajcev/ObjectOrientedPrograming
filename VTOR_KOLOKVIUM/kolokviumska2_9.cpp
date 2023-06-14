#include <iostream>
#include <cstring>

using namespace std;

class Exception {
public:
    void print() {
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }

};

class StudentNotFound {
private:
    int ind;
public:
    StudentNotFound(int ind) : ind(ind) {
    }

    void print() {
        cout << "Ne postoi PhD student so indeks " << ind << endl;
    }
};

class Trud {
private:
    char vid;
    int godina;
    static int C;
    static int J;
public:
    Trud(const char vid = 'C', int godina = 0) : vid(vid), godina(godina) {

    }

    friend istream &operator>>(istream &is, Trud &t) {
        is >> t.vid >> t.godina;
        return is;
    }


    char getVid() const {
        return vid;
    }

    int getGodina() const {
        return godina;
    }

    static void setC(int c);

    static void setJ(int j);

    static int getC();

    static int getJ();
};

class Student {
protected:
    char name[30];
    int index;
    int yearOfStart;
    int grades[20];
    int passedExams;
public:
    Student(const char *name = "", int index = 0, int yearOfStart = 0, int *grades = 0, int passedExams = 0) {
        strcpy(this->name, name);
        this->index = index;
        this->yearOfStart = yearOfStart;
        this->passedExams = passedExams;
        for (int i = 0; i < passedExams; ++i) {
            this->grades[i] = grades[i];
        }
    }

    virtual double rang() {
        double avg = 0;
        for (int i = 0; i < passedExams; ++i) {
            avg += grades[i];
        }
        return avg / passedExams;
    }

    friend ostream &operator<<(ostream &os, Student &student) {
        os << student.index << " " << student.name << " " << student.yearOfStart << " " << student.rang() << endl;
        return os;
    }

    int getIndex() const {
        return index;
    }

    virtual Student &operator+=(Trud t) {
        return *this;
    }

};

class PhDStudent : public Student {
private:
    Trud *trudovi;
    int n;
public:
    PhDStudent(char *name, int index, int yearOfStart, int *grades, int passedExams, Trud *trudovi, int n) : Student(
            name, index, yearOfStart, grades, passedExams) {
        this->n = n;
        this->trudovi = new Trud[n];
        for (int i = 0; i < n; ++i) {
            this->trudovi[i] = trudovi[i];
        }
    }

    double rang() {
        double avg = Student::rang();
        for (int i = 0; i < n; ++i) {
            char zn = trudovi[i].getVid();
            if (zn == 'c' || zn == 'C') {
                avg += trudovi[i].getC();
            } else {
                avg += trudovi[i].getJ();
            }

        }
        return avg;
    }

    PhDStudent &operator+=(Trud t) {
        if (t.getGodina() < yearOfStart) {
            throw Exception();
        }
        Trud *tmp = new Trud[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = trudovi[i];
        }
        tmp[n++] = t;
        delete[] trudovi;
        trudovi = tmp;
        return *this;
    }
};

int Trud::C = 1;
int Trud::J = 3;

void Trud::setC(int c) {
    C = c;
}

void Trud::setJ(int j) {
    J = j;
}

int Trud::getC() {
    return C;
}

int Trud::getJ() {
    return J;
}

void addTrud(int indeks, Trud t, Student **niza, int m) {
    for (int i = 0; i < m; ++i) {
        if (niza[i]->getIndex() == indeks) {
            PhDStudent *casted = dynamic_cast<PhDStudent *>(niza[i]);
            if (casted) {
                *(niza[i]) += t;
                return;
            }
        }
    }
    throw StudentNotFound(indeks);
}


int main() {
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        try {
            addTrud(indeks, t, niza, m);
        } catch (Exception e) {
            e.print();
        } catch (StudentNotFound s) {
            s.print();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        try {
            addTrud(indeks, t, niza, m);
        } catch (Exception e) {
            e.print();
        } catch (StudentNotFound s) {
            s.print();
        }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            try {
                trud[j] = t;
                if (t.getGodina() < god) {
                    throw Exception();
                }
            } catch (Exception e) {
                j--;
                n_tr--;
                e.print();
            }
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        try {
            addTrud(indeks, t, niza, m);
        } catch (Exception e) {
            e.print();
        } catch (StudentNotFound s) {
            s.print();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        Trud::setC(conf);
        Trud::setJ(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}