#include <iostream>
#include <cstring>

using namespace std;

class MobilePhone {
private:
    char model[50];
    int modelNumber;
    int year;
public:
    MobilePhone() {
        strcpy(this->model, "Basic");
        this->modelNumber = 1;
        this->year = 2000;
    }

    MobilePhone(char *model, int modelNumber, int year) : modelNumber(modelNumber), year(year) {
        strcpy(this->model, model);
    }

    ~MobilePhone() {}

    MobilePhone(const MobilePhone &other) {
        strcpy(this->model, other.model);
        this->modelNumber = other.modelNumber;
        this->year = other.year;
    }

    void printPhone() {
        cout << model << " " << modelNumber << " release year: " << year << endl;
    }

};

class Owner {
private:
    char name[100];
    char secondName[100];
    MobilePhone phone;
public:
    Owner() {
        strcpy(this->name, "Name");
        strcpy(this->secondName, "Second Name");
    }

    Owner(char *name, char *secondName, const MobilePhone &phone) : phone(phone) {
        strcpy(this->name, name);
        strcpy(this->secondName, secondName);
    }

    ~Owner() {}

    void print() {
        cout << name << " " << secondName << " has a mobile phone: " << endl;
        phone.printPhone();
    }
};

int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin>>testCase;

    cin>>model;
    cin>>modelNumber;
    cin>>year;
    cin>>name;
    cin>>surname;

    if(testCase==1){
        MobilePhone mobilePhone(model,modelNumber,year);

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }
    if(testCase==2){
        MobilePhone mobilePhone(MobilePhone(model,modelNumber,year));

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }

}