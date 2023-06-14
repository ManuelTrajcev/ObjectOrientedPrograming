#include <iostream>
#include <cstring>

using namespace std;

class NBAPlayer {
protected:
    char *name;
    char team[40];
    double avgPoints;
    double avgAssists;
    double avgJumps;
public:
    NBAPlayer(char *name = "", char *team = "", double avgPoints = 0, double avgAssists = 0, double avgJumps = 0) {
        this->avgPoints = avgPoints;
        this->avgAssists = avgAssists;
        this->avgJumps = avgJumps;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->team, team);
    }


    NBAPlayer(const NBAPlayer &other) {
        this->avgPoints = other.avgPoints;
        this->avgAssists = other.avgAssists;
        this->avgJumps = other.avgJumps;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->team, other.team);
    }

    NBAPlayer &operator=(const NBAPlayer &other) {
        if (this != &other) {
            this->avgPoints = other.avgPoints;
            this->avgAssists = other.avgAssists;
            this->avgJumps = other.avgJumps;
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            strcpy(this->team, other.team);
        }
        return *this;
    }


    double rating() {
        return avgPoints * 0.45 + avgAssists * 0.3 + avgJumps * 0.25;
    }

    void print() {
        cout << name << " - " << team << endl;
        cout << "Points: " << avgPoints << endl;
        cout << "Assists: " << avgAssists << endl;
        cout << "Rating: " << rating() << endl;
    }

};

class AllStarPlayer : public NBAPlayer {
private:
    double avgAllStarPoints;
    double avgAllStarAssists;
    double avgAllStarJumps;
public:
    AllStarPlayer(char *name = "", char *team = "", double avgPoints = 0, double avgAssists = 0, double avgJumps = 0,
                  double avgAllStarPoints = 0,
                  double avgAllStarAssists = 0, double avgAllStarJumps = 0) : NBAPlayer(name, team, avgPoints,
                                                                                        avgAssists,
                                                                                        avgJumps),
                                                                              avgAllStarPoints(avgAllStarPoints),
                                                                              avgAllStarAssists(avgAllStarAssists),
                                                                              avgAllStarJumps(avgAllStarJumps) {

    }

    AllStarPlayer(const NBAPlayer &other, double avgAllStarPoints, double avgAllStarAssists, double avgAllStarJumps)
            : NBAPlayer(other), avgAllStarPoints(avgAllStarPoints), avgAllStarAssists(avgAllStarAssists),
              avgAllStarJumps(avgAllStarJumps) {

    }

    AllStarPlayer(const AllStarPlayer &other) {
        this->avgPoints = other.avgPoints;
        this->avgAssists = other.avgAssists;
        this->avgJumps = other.avgJumps;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->team, other.team);
        this->avgAllStarPoints = other.avgAllStarPoints;
        this->avgAllStarAssists = other.avgAllStarAssists;
        this->avgAllStarJumps = other.avgAllStarJumps;
    }

    AllStarPlayer &operator=(const AllStarPlayer &other) {
        if (this != &other) {
            this->avgPoints = other.avgPoints;
            this->avgAssists = other.avgAssists;
            this->avgJumps = other.avgJumps;
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            strcpy(this->team, other.team);
            this->avgAllStarPoints = other.avgAllStarPoints;
            this->avgAllStarAssists = other.avgAllStarAssists;
            this->avgAllStarJumps = other.avgAllStarJumps;
        }
        return *this;
    }

    ~AllStarPlayer() {
        delete[] name;
    }

    double rating() {
        return NBAPlayer::rating() + avgAllStarPoints * 0.3 + avgAllStarAssists * 0.4 + avgAllStarJumps * 0.3;
    }

    double AllStarRating() {
        return avgAllStarPoints * 0.3 + avgAllStarAssists * 0.4 + avgAllStarJumps * 0.3;
    }

    void print() {
        NBAPlayer::print();
        cout << "All Star Rating: " << AllStarRating() << endl;
        cout << "New Rating: " << (NBAPlayer::rating() + AllStarRating()) / 2.0 << endl;
    }
};


int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer *players = new NBAPlayer[5];
    AllStarPlayer *asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name, team, points, assists, rebounds);
            players[i].print();
        }
    } else if (n == 2) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name, team, points, assists, rebounds);
            asPlayers[i] = AllStarPlayer(players[i], allStarPoints, allStarAssists, allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            asPlayers[i].print();

    } else if (n == 3) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints, allStarAssists, allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete[] players;
    delete[] asPlayers;
}