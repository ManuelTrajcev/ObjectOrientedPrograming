#include <iostream>
#include <cstring>

using namespace std;


class Employee {
protected:
    char name[50];
    int year;
public:
    Employee(const char *name = "", int year = 0) {
        strcpy(this->name, name);
        this->year = year;
    }
};

class Payable {
protected:
    double salary;
public:
    Payable(double salary = 0) : salary(salary) {

    }

    virtual double calculateSalary() = 0;

    virtual void displayInfo() = 0;
};

class Developer : public Employee, public Payable {
private:
    char programLanguage[20];
public:
    Developer(const char *name = "", int year = 0, double salary = 0, const char *programLanguage = "") : Employee(name,
                                                                                                                   year),
                                                                                                          Payable(salary) {
        strcpy(this->programLanguage, programLanguage);
    }

    double calculateSalary() {
        return salary * 0.9;
    }

    void displayInfo() {
        cout<<"--Developer Information--"<<endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << year << endl;
        cout << "Salary: $" << calculateSalary() << endl;
        cout << "Programing Language: " << programLanguage << endl;
    }
};

class Manager : public Employee, public Payable {
private:
    int departaments;
public:
    Manager(const char *name = "", int year = 0, double salary = 0, int departaments = 0) : Employee(name, year),
                                                                                            Payable(salary),
                                                                                            departaments(
                                                                                                    departaments) {}

    double calculateSalary() {
        return salary * (1 + departaments * 0.05);
    }

    void displayInfo() {
        cout<<"--Manager Information--"<<endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << year << endl;
        cout << "Salary: $" << calculateSalary() << endl;
        cout << "Number of Departments: " << departaments << endl;
    }
};

double biggestSalary(Payable **p, int n) {
    Payable *max = p[0];
    for (int i = 1; i < n; ++i) {
        if (p[i]->calculateSalary() > max->calculateSalary()) {
            max = p[i];
        }
    }
    return max->calculateSalary();
}

int main() {
    Payable *payable[5];
    Developer developers[5];
    Manager managers[5];
    int j = 0, k = 0;
    for (int i = 0; i < 5; i++) {
        char name[50];
        int age;
        double salary;
        cin >> name >> age >> salary;
        if (i % 2 == 0) {
            char programmingLanguage[50];
            cin >> programmingLanguage;
            developers[j] = Developer(name, age, salary, programmingLanguage);
            developers[j].displayInfo();
            payable[i] = &developers[j];
            j++;
        } else {
            int numberOfDepartments;
            cin >> numberOfDepartments;
            managers[k] = Manager(name, age, salary, numberOfDepartments);
            managers[k].displayInfo();
            payable[i] = &managers[k];
            k++;
        }
    }
    cout << endl << "Biggest Salary: " << biggestSalary(payable, 5);
    return 0;
}