#include <stdio.h>
#include <string.h>

typedef struct Employee {
    char name[100];
    char EMBG[100];
    char sector[100];
    int salary;
} Employee;

//void readEmployee(Employee *employee) {
//    scanf("%s %s %s %d", employee->name, employee->EMBG, employee->sector, &employee->salary);
//}
//
//void printEmployee(Employee employee) {
//    printf("%s %s %s %d\n", employee.name, employee.EMBG, employee.sector, employee.salary);
//}

typedef struct Company {
    char name[100];
    Employee employees[100];
    int n;
} Company;

//void readCompany(Company *company) {
//    scanf("%s %d", company->name, &company->n);
//    for (int i = 0; i < company->n; ++i) {
//        readEmployee(company->employees + i);
//    }
//}

void printHighestSalary(Company *company, int n, char *departement) {
    Company max;
    int maxSalary;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < company->n; ++j) {
            if (strcmp(departement, company[i].employees[j].sector) == 0) {
                max = company[i];
                maxSalary = company[i].employees[j].salary;
            }
        }
    }
}

void printBellowAverage(Company *company, int n) {

}

int main() {
    int n;
    Company company[100];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s %d", company[i].name, &company[i].n);
    }
    return 0;
}