#include <iostream>
#include <cstring>

using namespace std;

class Employee {
protected:
    char *name;
    int salary;
    int bonus;
    int experience;
public:
    Employee(char *name = "", int salary = 0, int bonus = 0, int experience = 0) {
        this->salary = salary;
        this->bonus = bonus;
        this->experience = experience;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Employee(const Employee &other) {
        this->salary = other.salary;
        this->bonus = other.bonus;
        this->experience = other.experience;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }

    Employee &operator=(const Employee &other) {
        if (this != &other) {
            this->salary = other.salary;
            this->bonus = other.bonus;
            this->experience = other.experience;
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
        }
        return *this;
    }

    ~Employee() {
        delete[] name;
    }

    double getTotalSalary() {
        return salary + bonus * experience;
    }

    void print() {
        cout << "Employee name: " << name << endl;
        cout << "Salary: " << salary << endl;
        cout << "Experience: " << experience << endl;
    }
};

class Manager : public Employee {
private:
    char *oddel;
    int managerBonus;
public:
    Manager(char *name = "", int salary = 0, int bonus = 0, int experience = 0, char *oddel = "", int menagerBonus = 0)
            : Employee(name, salary,
                       bonus,
                       experience) {
        this->oddel = new char[strlen(oddel) + 1];
        strcpy(this->oddel, oddel);
        this->managerBonus = menagerBonus;
    }

    Manager(const Employee &other, char *oddel, int menagerBonus) : Employee(other) {
        this->oddel = new char[strlen(oddel) + 1];
        strcpy(this->oddel, oddel);
        this->managerBonus = menagerBonus;
    }

    Manager(const Manager &other) {
        this->salary = other.salary;
        this->bonus = other.bonus;
        this->experience = other.experience;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->oddel = new char[strlen(oddel) + 1];
        strcpy(this->oddel, oddel);
        this->managerBonus = other.managerBonus;

    }

    Manager &operator=(const Manager &other) {

        if (this != &other) {
            this->salary = other.salary;
            this->bonus = other.bonus;
            this->experience = other.experience;
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            this->oddel = new char[strlen(oddel) + 1];
            strcpy(this->oddel, oddel);
            this->managerBonus = other.managerBonus;
        }
        return *this;
    }

    ~Manager() {
        delete[] oddel;
    }

    double getTotalManagerBonus(){

    }

    double getTotalSalary(){
        return salary + bonus * experience;
    }
    void print() {
        cout << "Manager name: " << name << endl;
        cout <<"Departament: " << oddel << endl;
        cout << "Salary: " << getTotalSalary() << endl;
        cout << "Experience: " << experience << endl;
    }
};

int main() {

    char name[20];
    int salary;
    int bonus;
    int experience;
    char department[50];
    int managerBonus;

    Employee *employees = new Employee[5];
    Manager *managers = new Manager[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "EMPLOYEES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> salary >> bonus >> experience;
            employees[i] = Employee(name, salary, bonus, experience);
            employees[i].print();
            cout << endl;
        }
    } else if (n == 2) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> salary >> bonus >> experience;
            cin >> department >> managerBonus;
            employees[i] = Employee(name, salary, bonus, experience);
            managers[i] = Manager(employees[i], department, managerBonus);
        }

        cout << "EMPLOYEES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            employees[i].print();
            cout << endl;
        }


        cout << "MANAGERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            managers[i].print();
            cout << endl;
        }

    } else if (n == 3) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> salary >> bonus >> experience;
            cin >> department >> managerBonus;
            managers[i] = Manager(name, salary, bonus, experience, department, managerBonus);
        }
        cout << "MANAGERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            managers[i].print();
            cout << endl;
        }

    }

    delete[] employees;
    delete[] managers;
}