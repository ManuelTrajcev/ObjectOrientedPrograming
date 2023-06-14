#include <iostream>
#include <cstring>

using namespace std;

class Shape {
protected:
    double height;
    double base;
public:
    Shape(double height, double base) : height(height), base(base) {

    }

    virtual void print() = 0;


    virtual double volume() = 0;

    double getHeight() {
        return height;
    }
};

class Cylinder : public Shape {
private:
public:
    Cylinder(double height, double base) : Shape(height, base) {

    }


    double volume() {
        return base * base * 3.14 * height;
    }

    void print() {
        cout << "Cylinder with volume: " << volume();
    }
};

class Cone : public Shape {
private:
public:
    Cone(double height, double base) : Shape(height, base) {}


    double volume() {
        return 1.0 / 3 * base * base * height * 3.14;
    }

    void print() {
        cout << "Cone with volume: " << volume();
    }
};

class Cuboid : public Shape {
private:
    double secondBase;
public:
    Cuboid(double height, double base, double secondBase) : Shape(height, base), secondBase(secondBase) {}

    void print() {
        cout << "Cuboid with volume: " << volume();
    }

    double volume() {
        return base * secondBase * height;
    }
};

void shapeWithLargestVolume(Shape **shapes, int n) {
    Shape *max = shapes[0];
    for (int i = 1; i < n; ++i) {
        if (shapes[i]->volume() > max->volume()) {
            max = shapes[i];
        }
    }
    cout << "Biggest volume has ";
    max->print();
}

int countShapesWithCircleBase(Shape **shapes, int n) {
    int counter = 0;
    for (int i = 1; i < n; ++i) {
        Cuboid *castedCuboid = dynamic_cast<Cuboid *>(shapes[i]);
        if (castedCuboid == nullptr) {
            counter++;
        }
    }
    return counter;
}


int main() {
    int n;
    cin >> n;
    Shape **pShape = new Shape *[n];
    for (int i = 0; i < n; ++i) {
        int type; //1-c,
        double height, base, secondBase;
        cin >> type >> height >> base;
        if (type == 3) {
            cin >> secondBase;
        }
        if (type == 1) {
            pShape[i] = new Cylinder(height, base);
        } else if (type == 2) {
            pShape[i] = new Cone(height, base);
        } else {
            pShape[i] = new Cuboid(height, base, secondBase);
        }

        pShape[i]->print();
        cout << endl;

    }

    shapeWithLargestVolume(pShape, n);
    cout << "\nNumber of shapes with out circular base is: " << countShapesWithCircleBase(pShape, n);

    return 0;
}