#include <iostream>
#include <cstring>

using namespace std;

class DisciplinaryAction {
private:
    char *name;
    int index;
    char *reason;
public:
    DisciplinaryAction(char *name = "", int index = 0, char *reason = "") {
        this->name = new char[strlen(name) + 1];
        this->reason = new char[strlen(reason) + 1];
        strcpy(this->name, name);
        strcpy(this->reason, reason);
        this->index = index;
    }

    DisciplinaryAction(const DisciplinaryAction &other) {
        this->name = new char[strlen(other.name) + 1];
        this->reason = new char[strlen(other.reason) + 1];
        strcpy(this->name, other.name);
        strcpy(this->reason, other.reason);
        this->index = other.index;
    }

    DisciplinaryAction &operator=(const DisciplinaryAction &other) {
        delete[] this->name;
        delete[] this->reason;
        this->name = new char[strlen(other.name) + 1];
        this->reason = new char[strlen(other.reason) + 1];
        strcpy(this->name, other.name);
        strcpy(this->reason, other.reason);
        this->index = other.index;
    }

    ~DisciplinaryAction() {
        delete[] name;
        delete[] reason;
    }

    int getIndex() const {
        return index;
    }

    void setIndex(int index) {
        DisciplinaryAction::index = index;
    }

    void print() {
        cout << "Student: " << this->name << endl;
        cout << "Student's index: " << this->index << endl;
        cout << "Reason: " << this->reason << endl;
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

        cin >> name >> index >> reason;

        arr[i] = DisciplinaryAction(name, index, reason);
    }

    cout << "-- Testing operator = & print() --\n";
    arr[0].print();

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    arr[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    merka.print();

    /// Testing if z is OK

    cout << "\n-- Testing if z was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        arr[i].print();

    return 0;
}