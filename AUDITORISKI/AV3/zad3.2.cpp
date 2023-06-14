//Да се напише класа во која ќе се чуваат основни податоци за вработен:
//• име
//• плата
//• работна позиција (работната позиција може да биде вработен, директор или
//шеф).
//Напишете главна програма во која се читаат од стандарден влез податоци за N
//вработени, а потоа се пачати листа на вработените сортирани според висината
//на платата во опаѓачки редослед.
#include <iostream>
#include <cstring>

using namespace std;

enum Type {
    employee,
    director,
    owner
};

class Employee {
private:
    char name[50];
    char lastName[50];
    Type type;
    int salary;
public:
    Employee(char *_name = "Manuel", int _salary = 150000, Type _type = Type(0)) {
        strcpy(name, _name);
        salary = _salary;
        type = _type;
    }

    ~Employee() {
    }

    void print() {
        cout << "Employee: " << name << " Salary: " << salary << " Type: ";
        switch (type) {
            case employee:
                cout << "Basic" << endl;
                break;
            case director:
                cout << "Director" << endl;
                break;
            case owner:
                cout << "Owner" << endl;
                break;
        }
    }

    void setName(char _name[50]) {
        strcpy(name, _name);
    }

    void setSalary(int _salary) {
        salary = _salary;
    }

    void setType(Type _type) {
        type = _type;
    }

    int compareTo(Employee other) {
        int diff = salary - other.salary;
        return diff == 0 ?: (diff > 0 ? 1 : -1);
    }

    void swap(Employee &e1, Employee &e2) {
        Employee tmp = e1;
        e1 = e2;
        e2 = tmp;
    }

    int getSalary() {
        return salary;
    }
};

int main() {
    int n;
    cin >> n;
    Employee employees[50];
    char name[50];
    int salary;
    int type;
    for (int i = 0; i < n; ++i) {
        cin >> name >> salary >> type;  //type se vnesuva indeks od type 0,1,2
        employees[i].setName(name);
        employees[i].setSalary(salary);
        employees[i].setType((Type) type);
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            // if (employees[j].compareTo(employees[j + 1]) == -1) {
            if (employees[j].getSalary() < employees[j + 1].getSalary()) {      //isot kako gornoto
                swap(employees[j], employees[j + 1]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        employees[i].print();
    }
    return 0;
}