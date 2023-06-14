#include <iostream>
#include <ctype.h>
#include <string.h>

using namespace std;

void normalizeName(char *name) {
    name[0] = toupper(name[0]);
    for (int i = 1; i < strlen(name); ++i) {
        name[i] = tolower(name[i]);
    }
}

struct Student {
    char firstName[100];
    char lastName[100];
    char index[10];
    int grades[40];
    int countGrades;

    void read() {
        cin >> firstName >> lastName >> index >> countGrades;
        for (int i = 0; i < countGrades; ++i) {
            cin >> grades[i];
        }
    }

    float average() {
        float sum = 0;
        for (int i = 0; i < countGrades; ++i) {
            sum += grades[i];
        }
        return sum / countGrades;
    }

    void printStudent() {
        normalizeName(firstName);
        normalizeName(lastName);
        cout << firstName << " " << lastName << " " << index <<
             " " << average() << endl;
    }

};

void sort(Student *student, int n) {
    Student tmp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (student[j].average() < student[j + 1].average()) {
                tmp = student[j];
                student[j] = student[j + 1];
                student[j + 1] = tmp;
            }
        }
    }
}

int main() {
    int n;
    Student student[100];
    cin >> n;
    for (int i = 0; i < n; ++i) {
        student[i].read();
    }
    sort(student, n);
    for (int i = 0; i < n; ++i) {
        student[i].printStudent();
    }
    return 0;
}