//DIAMAND PROBLEM

#include <iostream>
#include <cstring>

using namespace std;

class Vehicle {
protected:
    int acceleration;
public:
    Vehicle() {
        acceleration = 0;
        cout << "Vehicle constructor" << endl;
    }

    virtual void accelerate() {
        cout << "Vehicle accelerate called" << endl;
        acceleration++;
    }

    ~Vehicle() {
        cout << "Vehicle destructor" << endl;
    }

    int getAcceleration() const {
        return acceleration;
    }
};

class Car : virtual public Vehicle {

public:
    Car() {
        cout << "Car constructor" << endl;
    }

//    void accelerate() {
//        cout << "Car accelerate called" << endl;
//        Vehicle::accelerate();
//        Vehicle::accelerate();
//    }

    ~Car() {
        cout << "Car destructor" << endl;

    }

    virtual void drive() {
        cout << "Car is driving" << endl;
    }
};

class Jet : virtual public Vehicle {

public:
    Jet() {
        cout << "Jet constructor" << endl;
    }

    void accelerate() {
        cout << "Jet accelerate called" << endl;
        acceleration += 50;
    }

    virtual void fly() {
        cout << "Jet is flying" << endl;
    }

    ~Jet() {
        cout << "Jet destructor" << endl;
    }
};

class JetCar : public Car, public Jet {
private:

public:
    JetCar() {
        cout << "JetCar constructor" << endl;
    }

    ~JetCar() {
        cout << "JetCar destructor" << endl;
    }


    void drive() {
        cout << "JetCar is driving" << endl;
    }

    void fly() {
        cout << "JetCar is flying" << endl;
    }
};

int main() {
    JetCar jetCar;
    jetCar.fly();
    jetCar.drive();
    return 0;
}