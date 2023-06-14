#include <iostream>
#include <cstring>

using namespace std;

class Animal {
protected:
    char name[50];
public:
    Animal(char *name = "") {
        strcpy(this->name, name);
    }

    virtual void makeSound() {
        cout << name << " makes the sound bla bla" << endl;
    }
};

class Dog : public Animal {
private:
    char name[50];
public:
    Dog(char *name = "") {
        strcpy(this->name, name);
    }

    void makeSound() {
        cout << name << " makes the sound af af" << endl;
    }
};

class Cat : public Animal {
private:
    char name[50];
public:
    Cat(char *name = "") {
        strcpy(this->name, name);
    }

    void makeSound() {
        cout << name << " makes the sound myau myau" << endl;
    }
};

int main() {
//    Animal **animals = new Animal *[3];
//    animals[0] = new Animal("Simba");
//    animals[1] = new Dog("Sarko");
//    animals[2] = new Cat("Bela");
//    for (int i = 0; i < 3; ++i) {
//        animals[i]->makeSound();
//    }
    int n;
    cin >> n;
    Animal **animals = new Animal *[n];

    for (int i = 0; i < n; ++i) {
        int type; //1=cat 2=dog
        char name[30];
        cin >> type >> name;
        if (type == 1) {
            animals[i] = new Cat(name);
        } else {
            animals[i] = new Dog(name);
        }
    }


    for (int i = 0; i < n; ++i) {
        animals[i]->makeSound();
    }

    return 0;
}