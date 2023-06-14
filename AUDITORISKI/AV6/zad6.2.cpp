#include <iostream>
#include <cstring>

using namespace std;

class Complex {
private:
    float a, b;
public:
    Complex(float a = 0, float b = 0) {
        this->a = a;
        this->b = b;
    }

    Complex(const Complex &other) {
        this->a = other.a;
        this->b = other.b;
    }

    Complex &operator=(const Complex &other) {
        if (this != &other) {
            this->a = other.a;
            this->b = other.b;
        }
        return *this;
    }

    ~Complex() {}

    Complex operator+(const Complex &one) {
        return Complex(one.a + a, one.b + b);
    }

    Complex operator/(const Complex &other) {
        float m = other.a * other.a + other.b * other.b;
        float r = (a * other.a - b * other.b) / m;
        float l = (b * other.a + b * other.b) / m;
        return Complex(r, l);
    }

    Complex &operator+=(const Complex &other) {
        a += other.a;
        b += other.b;
        return *this;
    }

    Complex &operator-=(const Complex &other) {
        a -= other.a;
        b -= other.b;
        return *this;
    }

    Complex &operator*=(const Complex &c) {
        a = a * c.a - b * c.b;
        b = b * c.a - a * c.b;
        return *this;
    }

    Complex operator*(const Complex &c) {
        return Complex(a * c.a - b * c.b, b * c.a - a * c.b);
    }

    Complex &operator/=(const Complex &other) {
        a /= other.a;
        b /= other.b;
        return *this;
    }

    bool operator==(const Complex &other) {
        return a == other.a && b == other.b;
    }

    Complex operator+(float n) {
        Complex result(a + n, b);
        return result;
    }

    friend Complex operator+(float n, Complex &c);

    friend Complex operator-(const Complex &c1, const Complex &c2);


    friend ostream &operator<<(ostream &o, const Complex &c) {
        o << c.a;
        if (c.b >= 0) {
            o << "+";
        }
        o << c.b << "i";
        return o;
    }
};

Complex operator+(float n, Complex &c) {
    return Complex(c.a + n, c.b);
}

Complex operator-(const Complex &c1, const Complex &c2) {
    return Complex(c1.a - c2.a, c1.b - c2.b);
}

int main() {
    Complex c1(2, -6);
    Complex c2(3, 5);
    Complex c = c1 + c2;
    cout << c1 << " + " << c2 << " = " << c << endl;
    c = c1 - c2;
    cout << c1 << " - " << c2 << " = " << c << endl;
    c = c1 * c2;
    cout << c1 << " * " << c2 << " = " << c << endl;
    c = c1 / c2;
    cout << c1 << " / " << c2 << " = " << c << endl;
    if (c == c1) {
        cout << "Numbers are equal" << endl;
    }

    c = c1 + 2;
    cout << c1 << " + " << 2 << " = " << c << endl;
    c = 2 + c1;
    cout << 2 << " + " << c1 << " = " << c << endl;
    return 0;
}