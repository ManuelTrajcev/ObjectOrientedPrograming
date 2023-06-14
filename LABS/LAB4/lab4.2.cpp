#include <iostream>
#include <cstring>

using namespace std;

class Student {
private:
    char *name;
    int age;
    char *major;
public:
    Student(char *name = "name", int age = 0, char *major = "major") {
        this->age = age;
        this->name = new char[strlen(name) + 1];
        this->major = new char[strlen(major) + 1];
        strcpy(this->name, name);
        strcpy(this->major, major);
    }

    Student(const Student &other) {
        this->age = other.age;

        this->name = new char[strlen(other.name) + 1];
        this->major = new char[strlen(other.major) + 1];
        strcpy(this->name, other.name);
        strcpy(this->major, other.major);
    }

    Student &operator=(const Student &other) {
        this->age = other.age;
        delete[] this->name;
        delete[] this->major;
        this->name = new char[strlen(other.name) + 1];
        this->major = new char[strlen(other.major) + 1];
        strcpy(this->name, other.name);
        strcpy(this->major, other.major);
        return *this;
    }

    ~Student() {
        delete[] this->name;
        delete[] this->major;
    }

    char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    char *getMajor() const {
        return major;
    }
};

class Classroom {
private:
    Student *students;
    int numStudents;
    int capacity;
public:
    int getNumStudents() const {
        return numStudents;
    }

    Student getStudents(int r) {
        return students[r];
    }

    Classroom(Student *students = 0, int numStudents = 0, int capacity = 0) {
        this->capacity = capacity;
        this->numStudents = numStudents;
        this->students = new Student[numStudents];
        for (int i = 0; i < numStudents; ++i) {
            this->students[i] = students[i];
        }
    }

    Classroom(const Classroom &other) {
        this->capacity = other.capacity;
        this->numStudents = other.numStudents;
        this->students = new Student[other.numStudents];
        for (int i = 0; i < other.numStudents; ++i) {
            this->students[i] = other.students[i];
        }
    }

    Classroom &operator=(const Classroom &other) {
        delete[] this->students;
        this->capacity = other.capacity;
        this->numStudents = other.numStudents;
        this->students = new Student[other.numStudents];
        for (int i = 0; i < other.numStudents; ++i) {
            this->students[i] = other.students[i];
        }
        return *this;
    }

    void add(const Student &other) {
        Student *tmp = new Student[numStudents + 1];
        for (int i = 0; i < numStudents; ++i) {
            tmp[i] = this->students[i];
        }
        tmp[numStudents] = other;
        delete[] students;
        students = new Student[numStudents + 1];
        numStudents++;
        students = tmp;
    }

    void remove(char *name) {
        int j = 0, i = 0;
        Student *tmp = new Student[numStudents];
        for (i = 0; i < numStudents; ++i) {
            if (strcmp(this->students[i].getName(), name) != 0) {
                tmp[j] = this->students[i];
                j++;
            }
        }
        if (i != j) {
            delete[] students;
            students = new Student[numStudents - 1];
            numStudents--;
            students = tmp;
        }
    }

    void printStudents() {
        for (int i = 0; i < numStudents; ++i) {
            cout << students[i].getName() << " (" << students[i].getAge() << ", " << students[i].getMajor() << ")"
                 << endl;
        }
        cout << endl;
    }
};

double findMedianAge(Classroom classroom) {
    double age = 0;
    double array[100];
    for (int i = 0; i < classroom.getNumStudents(); ++i) {
        array[i] = classroom.getStudents(i).getAge();
    }
    for (int i = 0; i < classroom.getNumStudents(); ++i) {
        for (int j = i + 1; j < classroom.getNumStudents(); ++j) {
            if (array[i] > array[j]) {
                swap(array[i], array[j]);
            }
        }
    }
    if (classroom.getNumStudents() % 2 == 0) {
        age = (array[classroom.getNumStudents() / 2] + array[classroom.getNumStudents() / 2 - 1]) / 2;
    } else {
        age = array[classroom.getNumStudents() / 2];
    }
    return age;
}

//DO NOT CHANGE
int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i * numStudents + j] = student;
        }
        cout << "Classroom " << i << endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;
    cout << "After removing the elements:" << endl; /// Added
    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout << "Classroom " << i << endl;
        classrooms[i].printStudents();
    }

    return 0;
}