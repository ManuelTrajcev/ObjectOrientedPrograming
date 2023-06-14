#include <iostream>
#include <cstring>

using namespace std;

class Game {
protected:
    char name[50];
public:
    Game(const char *name = "") {
        strcpy(this->name, name);
    }

    virtual void displayInfo() = 0;

    virtual int complexity() = 0;
};

class BoardGame : virtual public Game {
protected:
    int maxPlayers;
public:
    BoardGame(const char *name = "", int maxPlayers = 0) : Game(name), maxPlayers(maxPlayers) {

    }

    void displayInfo() {
        cout << "Game: " << name << endl;
        cout << "Max Players: " << maxPlayers << endl;
        cout << "Complexity: " << complexity() << endl;
    }

    int complexity() {
        if (maxPlayers > 6) {
            return 10;
        } else if (maxPlayers > 3) {
            return 5;
        } else {
            return 3;
        }
    }
};

class CardGame : virtual public Game {
protected:
    int numCards;
public:
    CardGame(const char *name = "", int numCards = 0) : Game(name), numCards(numCards) {

    }

    void displayInfo() {
        cout << "Game: " << name << endl;
        cout << "Number of cards: " << numCards << endl;
        cout << "Complexity: " << complexity() << endl;
    }

    int complexity() {
        if (numCards > 20) {
            return 10;
        } else if (numCards > 10) {
            return 5;
        } else {
            return 3;
        }
    }
};

class BoardCardGame : public BoardGame, public CardGame {
private:

public:
    BoardCardGame(const char *name = "", int maxPlayers = 0, int numCards = 0) : BoardGame(name, maxPlayers),
                                                                                 CardGame(name, numCards) {

    }

    void displayInfo() {
        cout << "Game: " << name << endl;
        cout << "Complexity: " << complexity() << endl;
    }

    int complexity() {
        return (CardGame::complexity() + BoardGame::complexity()) / 2;
    }
};

Game *mostComplexCardGame(Game **games, int n) {
    int flag = 1;
    Game *g;
    for (int i = 0; i < n; ++i) {
        CardGame *casted = dynamic_cast<CardGame *>(games[i]);
        if (casted != 0) {
            if (flag) {
                g = games[i];
                flag = 0;
                continue;
            }
            if (games[i]->complexity() > g->complexity()) {
                g = games[i];
            }
        }
    }
    return g;
}


int main() {
    char title[50];
    int maxPlayers;
    int numCards;
    int n;
    int choice;

    cin >> choice;
    if (choice == 1) {
        cin >> title;
        BoardCardGame boardCardGame(title, 8, 15);
        boardCardGame.displayInfo();
    } else {

        cin >> n;

        Game **g = new Game *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> title >> maxPlayers;

                g[i] = new BoardGame(title, maxPlayers);
            } else {
                cin >> title >> numCards;

                g[i] = new CardGame(title, numCards);
            }

        }

        mostComplexCardGame(g, n)->displayInfo();

    }


    return 0;
}