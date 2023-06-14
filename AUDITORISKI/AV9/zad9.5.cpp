//KOLOKVIUMSKA

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class RoundPeg {
protected:
    float radius;
public:
    RoundPeg(float radius = 0) : radius(radius) {

    }

    virtual float getRadius() const {
        return radius;
    }

    void setRadius(float radius) {
        RoundPeg::radius = radius;
    }

};


class RoundHole {

    float radius;
public:
    RoundHole(float radius = 0) : radius(radius) {

    }

    float getRadius() const {
        return radius;
    }

    void setRadius(float radius) {
        RoundHole::radius = radius;
    }

    bool fits(RoundPeg *roundPeg) {
        return roundPeg->getRadius() <= this->radius;
    }
};

class SquarePeg {
protected:
    float side;
public:
    SquarePeg(float side = 0) : side(side) {

    }

    float getSide() const {
        return side;
    }

    void setSide(float side) {
        SquarePeg::side = side;
    }
};

class SquarePegAddapter : public SquarePeg, public RoundPeg {

public:
    SquarePegAddapter(float side) : RoundPeg(side * sqrt(2) / 2), SquarePeg(side) {

    }

    float getRadius() const {
        return side * sqrt(2) / 2;
    }

};

int main() {
    RoundHole hole(10);
    RoundPeg *peg1 = new RoundPeg(8);
    RoundPeg *peg2 = new RoundPeg(11);
    cout << hole.fits(peg1) << endl;
    cout << hole.fits(peg2) << endl;
    RoundPeg *peg3 = new SquarePegAddapter(30);
    cout << hole.fits(peg3) << endl;
    return 0;
}