#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Employee {
private:
    char name[100];
    char surname[100];
    int salary;
public:
    Employee() {
        strcpy(this->name, "name");
        strcpy(this->surname, "surname");
        salary = 0;
    }

    Employee(char *name, char *surname, int salary) : salary(salary) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
    }

    Employee(const Employee &other) {
        strcpy(this->name, other.name);
        strcpy(this->surname, other.surname);
        this->salary = other.salary;
    }

    ~Employee() {}

    void printEmployee() {
        cout << "Employee name: " << name << endl;
        cout << "Employee surname: " << surname << endl;
        cout << "Employee salary: " << salary << endl;
    }

    const char *getName() const {
        return name;
    }

    void setName(char *name) {
        strcpy(this->name, name);
    }

    const char *getSurname() const {
        return surname;
    }

    void setSurname(char *name) {
        strcpy(this->surname, surname);
    }

    int getSalary() const {
        return salary;
    }

    void setSalary(int salary) {
        Employee::salary = salary;
    }

};

class TechCompany {
private:
    char name[100];
    Employee employees[20];
    int numOfEmployees;
public:
    char *getName() {
        return name;
    }

    TechCompany() {
        strcpy(this->name, "name");
        this->numOfEmployees = 0;
    }

    TechCompany(char *name) {
        strcpy(this->name, name);
        this->numOfEmployees = 0;
    }

    void setName(char *name) {
        strcpy(this->name, name);
    }

    TechCompany(char *name, Employee *employees, int numOfEmployees) {
        strcpy(this->name, name);
        this->numOfEmployees = numOfEmployees;
        for (int i = 0; i < numOfEmployees; ++i) {
            this->employees[i] = employees[i];
        }
    }


    TechCompany(const TechCompany &other) {
        strcpy(this->name, other.name);
        this->numOfEmployees = other.numOfEmployees;
        for (int i = 0; i < numOfEmployees; ++i) {
            this->employees[i] = other.employees[i];
        }
    }

    Employee *getEmployees() {
        return employees;
    }

    int getNumOfEmployees() {
        return numOfEmployees;
    }

    Employee getEmployee(int i) {
        return employees[i];
    }

    void setNumOfEmployees(int numOfEmployees) {
        this->numOfEmployees = numOfEmployees;
    }

    void print() {
        cout << "Tech company name: " << name << endl;
        cout << "Number of employees: " << numOfEmployees << endl;
    }

    int getNumEmployees() {
        return numOfEmployees;
    }

    double getAverageOfEmployeeSalary() {
        double sum = 0;
        for (int i = 0; i < numOfEmployees - 1; ++i) {
            sum += employees[i].getSalary();
        }
        return sum / numOfEmployees;
    }

    double total() {
        double sum = 0;
        for (int i = 0; i < numOfEmployees; ++i) {
            sum += ((employees[i].getSalary() - getAverageOfEmployeeSalary()) *
                    (employees[i].getSalary() - getAverageOfEmployeeSalary()));
        }
        return sum;
    }

    void addEmployee(Employee employee) {
        employees[numOfEmployees] = employee;
        numOfEmployees++;
    }
};

TechCompany printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies) {
    double max = companies[0].getAverageOfEmployeeSalary();
    int maxIndex = 0;
    for (int i = 0; i < numCompanies; ++i) {
        if (companies[i].getAverageOfEmployeeSalary() > max) {
            max = companies[i].getAverageOfEmployeeSalary();
            maxIndex = i;
        }
    }
    return companies[maxIndex];
}

TechCompany printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies) {
    double var = 0;
    double std = 0, maxStd = 0;
    int maxIndex = 0;
    for (int i = 0; i < numCompanies; ++i) {
        var = 0;
        var = companies[i].total() / (companies[i].getNumOfEmployees() - 1);
        std = sqrt(var);
        if (std > maxStd) {
            maxStd = std;
            maxIndex = i;
        }
    }
    return companies[maxIndex];
}

bool isSameCompany(TechCompany company1, TechCompany company2) {
    if (!strcmp(company1.getName(), company2.getName())) {
        return true;
    } else {
        return false;
    }
}

int main() {
    const int MAX_COMPANIES = 10;
    const int MAX_EMPLOYEES = 20;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char name[100];
        std::cin >> name;

        TechCompany company(name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout << "-->Testing get and set methods for one object and copy constructor" << std::endl;
    copy.setName("copy");
    std::cout << copy.getName() << std::endl;


    std::cout << "-->Testing addEmployee function" << std::endl;
    Employee newEmployee("John", "Doe", 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employees in copy: " << copy.getNumEmployees() << std::endl;


    std::cout << "-->Testing copy of first employee" << std::endl;
    Employee firstEmployee = copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout << "-->Testing methods" << std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " << t1.getName() << std::endl;

    if (isSameCompany(t, t1)) {
        std::cout << "The tech company: " << t.getName()
                  << " has the highest standard deviation and highest average salary" << std::endl;
    }
    return 0;
}
