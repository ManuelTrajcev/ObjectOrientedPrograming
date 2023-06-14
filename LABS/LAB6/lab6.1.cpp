#include <iostream>
#include <cstring>

using namespace std;

class DisciplinaryAction {
private:
    char *name;
    int index;
    char *reason;
    int num;
public:
    DisciplinaryAction(char *name = "", int index = 0, char *reason = "", int num = 0) {
        this->index = index;
        this->num = num;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->reason = new char[strlen(reason) + 1];
        strcpy(this->reason, reason);
    }

    DisciplinaryAction(const DisciplinaryAction &other) {
        this->index = other.index;
        this->num = other.num;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->reason = new char[strlen(other.reason) + 1];
        strcpy(this->reason, other.reason);
    }

    ~DisciplinaryAction() {
        delete[] name;
        delete[] reason;
    }

    DisciplinaryAction &operator=(const DisciplinaryAction &other) {
        if (this != &other) {
            this->index = other.index;
            this->num = other.num;
            delete[] name;
            delete[] reason;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            this->reason = new char[strlen(other.reason) + 1];
            strcpy(this->reason, other.reason);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const DisciplinaryAction &action) {
        os << "Student: " << action.name << endl;
        os << "Student's index: " << action.index << endl;
        os << "Reason: " << action.reason << endl;
        os << "Sessions: " << action.num << endl;
        return os;
    }

    DisciplinaryAction &operator++() {
        num++;
        return *this;
    }

    DisciplinaryAction &operator++(int) {
        DisciplinaryAction tmp = *this;
        num++;
        return tmp;
    }

    bool operator<(const DisciplinaryAction &rhs) const {
        return num < rhs.num;
    }

    bool operator>(const DisciplinaryAction &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const DisciplinaryAction &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const DisciplinaryAction &rhs) const {
        return !(*this < rhs);
    }

    void setIndex(int index) {
        DisciplinaryAction::index = index;
    }

};


/// Do NOT edit the main() function

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}