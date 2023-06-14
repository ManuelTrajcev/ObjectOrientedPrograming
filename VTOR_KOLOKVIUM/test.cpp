#include <iostream>

using namespace std;


class B {
public:
    static int n;

    void print() {
        cout << n;
    }
};


int B::n = 1;

int main() {
    B x, y;
    x.n = 4;
    x.print();
    return 0;
}