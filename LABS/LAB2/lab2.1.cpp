#include <iostream>
#include <cstring>

using namespace std;

class BasketballPlayer {
    char name[20];
    char secondName[20];
    int number;
    int p1, p2, p3;
public:
    void setName(char *_name) {
        strcpy(name, _name);
    }

    void setSecondName(char *_secondName) {
        strcpy(secondName, _secondName);
    }

    void setPoints(int _p1, int _p2, int _p3) {
        p1 = _p1;
        p2 = _p2;
        p3 = _p3;
    }

    void setNumber(int _number) {
        number = _number;
    }

    char getName() {
        cout << name;
    }

    void getSecondNAme() {
        cout << secondName;
    }

    int getPoints1() {
        return p1;
    }

    int getPoints2() {
        return p2;
    }

    int getPoints3() {
        return p3;
    }

    int getNumber() {
        return number;
    }

    float avgPoints() {
        return (p1 + p2 + p3) / 3.0;
    }

    void printPlayer() {
        cout << "Player: " << name << " " << secondName << " with number " << number << " has " << avgPoints()
             << " points on average";
    }
};

int main() {
    BasketballPlayer player;
    char name[20], secondName[20];
    int n, p1, p2, p3;
    cin >> name >> secondName >> n >> p1 >> p2 >> p3;
    player.setName(name);
    player.setSecondName(secondName);
    player.setNumber(n);
    player.setPoints(p1, p2, p3);
    player.printPlayer();
    return 0;
}