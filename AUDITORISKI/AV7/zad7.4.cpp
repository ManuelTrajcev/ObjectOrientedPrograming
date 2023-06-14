#include <iostream>
#include <cstring>

using namespace std;

class Ekipa {
protected:
    char name[15];
    int numWin;
    int numLoss;
public:
    Ekipa(char *name, int numWin, int numLoss) : numWin(numWin), numLoss(numLoss) {
        strcpy(this->name, name);
    }

    friend ostream &operator<<(ostream &os, const Ekipa &ekipa) {
        os << "Ime: " << ekipa.name << " Pobedi: " << ekipa.numWin << " Porazi: " << ekipa.numLoss;
        return os;
    }

    ~Ekipa() {}
};

class FudbalskaEkipa : public Ekipa {
private:
    int redCards;
    int yellowCards;
    int draft;
public:
    FudbalskaEkipa(char *name, int numWin, int numLoss, int redCards, int yellowCards, int draft) : Ekipa(name, numWin,
                                                                                                          numLoss),
                                                                                                    redCards(redCards),
                                                                                                    yellowCards(
                                                                                                            yellowCards),
                                                                                                    draft(draft) {

    }

    int points() {
        int p = numWin * 3 + draft;
        return p;
    }

    friend ostream &operator<<(ostream &os, FudbalskaEkipa &ekipa) {
        os << static_cast<const Ekipa &>(ekipa) << " Nereseni: " << ekipa.draft << " Poeni: " << ekipa.points();
        return os;
    }
};

int main() {
    char name[15];
    int win, loss, rc, yc, draft;
    cin >> name >> win >> loss >> rc >> yc >> draft;
    FudbalskaEkipa fe(name, win, loss, rc, yc, draft);
    cout << fe;
    return 0;
}