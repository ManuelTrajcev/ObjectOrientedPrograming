#include <iostream>
#include <string.h>

using namespace std;

struct employee {
    char name[100];
    char position[100];
    double baseSalary;

    void read() {
        cin >> name >> position >> baseSalary;
    }

    void print() {
        cout << "Name:" << name << "\nPosition:" << position << "\nBase salary:" << calculateSalary() << endl;
    }

    double calculateSalary() {
        if (strcmp(position, "TA") == 0) {
            return 1.1 * baseSalary;
        }
        if (strcmp(position, "Assistant Professor") == 0) {
            return 1.5 * baseSalary;
        }
        if (strcmp(position, "Associate") == 0) {
            return 1.9 * baseSalary;
        } else {
            return 2.4 * baseSalary;
        }

    }
};

int main() {
    employee employee1;
    employee1.read();
    employee1.print();
    return 0;
}