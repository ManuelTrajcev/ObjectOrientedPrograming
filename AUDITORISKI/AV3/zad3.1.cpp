//Да се напише класа за опишување на геометриско тело триаголник. Во класата
//да се напишат методи за пресметување на плоштината и периметарот на
//триаголникот.
//Потоа да се напише главна програма во која ќе се инстнацира еден објект од
//оваа класа со вредности за страните кои претходно ќе се прочитаат од
//стандарден влез. На овој објект да се повикат соодветните методи за
//пресметување на плоштината и периметарот.

#include <iostream>
#include <math.h>

using namespace std;

class Triangle {
    int a, b, c;        //po default se private
public:
    Triangle(int _a = 5, int _b = 4, int _c = 3) {  //5,4,3 default values
        cout << "Constructor is called\n";
        a = _a;
        b = _b;
        c = _c;
    }

    ~Triangle() {
        cout << "Object is destroyed\n";
    }

    int perimeter() {       //a,b,c ne se deklarirart vo (), bidejki gi ima vo samata clasa
        return a + b + c;   //sum a,b,c
    }

    double area() {
        float s = float(a + b + c) / 2;   //dynamic cast
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    void print() {
        cout << "Triangle with sides " << a << ", " << b << ", " << c << endl;
        cout << "Perimeter: " << perimeter() << " Area: " << area() << endl;
    }
};

int main() {
    Triangle t;
    Triangle t1(6, 6, 6);
    t.print();
    t1.print();
    return 0;
}