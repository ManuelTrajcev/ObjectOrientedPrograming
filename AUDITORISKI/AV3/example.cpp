#include <iostream>

using namespace std;

class Example {
private:
    int a;
    int b;
public:             //constructorot instancira objekt od dadena klasa
    Example() {//default constructor
        cout << "Default constructor is called\n";
        a = 0;
        b = 0;
    }

    Example(int _a, int _b) {       //iminjata da bidat razlicni od iminjata na elementite
        cout << "Constructor with arguments is called\n";
        a = _a;                     //konstruktor so argumenti
        b = _b;
    }

    int getA() {
        return a;
    }

    int getB() {
        return b;
    }

    void setA(int _a) {
        a = _a;
    }

    void setB(int _b) {
        b = _b;
    }

    void print() {
        cout << a << " " << b << endl;
    }

    ~Example() {
        cout << "Object is destroyed\n";
    }

//    Example(int _a = 0, int _b = 0) {       //konstruktor so argumenti + default values
//        a = _a;
//        b = _b;
//    }
};

int main() {
    Example e;//default constructor
    //e.a; (ne raboti, a e privaten element)
    Example e1(10, 20);    //constructor with arguments
    e.print();
    e.setA(5);
    e.setB(15);
    e.print();
    e1.print();
    return 0;
}