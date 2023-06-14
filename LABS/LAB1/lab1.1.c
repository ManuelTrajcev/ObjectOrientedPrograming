#include <stdio.h>
#include <string.h>

typedef struct Employee {
    char name[100];
    char EMBG[100];
    char sector[100];
    int salary;
} Employee;

typedef struct Company {
    char name[100];
    int n;
    Employee employee[100];
} Company;

void printEmployeesBellowAverageSalary(Company *company, int num) {
    float avg = 0;
    printf("Employees with salary below average:\n");
    for (int i = 0; i < num; ++i) {
        avg = 0;
        for (int j = 0; j < company[i].n; ++j) {
            avg += company[i].employee[j].salary;
        }
        avg /= (float) company[i].n;
        for (int j = 0; j < company[i].n; ++j) {
            if (company[i].employee[j].salary < avg) {
                printf("%s %s %s %d\n", company[i].employee[j].name, company[i].employee[j].EMBG,
                       company[i].employee[j].sector, company[i].employee[j].salary);
            }
        }
    }
}

void printHighestSalaryEmployee(Company *company, int num, char *departament) {
    printf("Employee with higihest salary in departament:\n");
    int max, maxIndex;
    for (int i = 0; i < num; ++i) {
        max = company[i].employee[0].salary;
        maxIndex = 0;
        for (int j = 1; j < company[i].n; ++j) {
            if (company[i].employee[0].salary > max && company[i].employee[j].sector == departament) {
                max = company[i].employee[j].salary;
                maxIndex = j;
            }
        }
        printf("%s %s %s %d\n", company[i].employee[maxIndex].name, company[i].employee[maxIndex].EMBG,
               company[i].employee[maxIndex].sector, company[i].employee[maxIndex].salary);
    }
}


int main() {
    int n;
    Company company[50];
    char sector[50];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s %d", company[i].name, &company[i].n);
        for (int j = 0; j < company[i].n; ++j) {
            scanf("%s %s %s %d", company[i].employee[j].name, company[i].employee[j].EMBG,
                  company[i].employee[j].sector, &company[i].employee[j].salary);
        }
    }
    scanf("%s", sector);
    printEmployeesBellowAverageSalary(company, n);
    printHighestSalaryEmployee(company,n,sector);
    return 0;
}