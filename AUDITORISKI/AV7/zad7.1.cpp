#include <iostream>
#include <cstring>

using namespace std;

class TennisPlayer {
protected:
    char firstName[50];
    char secondName[50];
    bool play;
public:
    TennisPlayer(char *firstName="", char *secondName="", bool play = false) {
        strcpy(this->firstName, firstName);
        strcpy(this->secondName, secondName);
        this->play = play;
    }
    TennisPlayer(const TennisPlayer &other) {
        strcpy(this->firstName, other.firstName);
        strcpy(this->secondName, other.secondName);
        this->play = play;
    }

    ~TennisPlayer(){}

    friend ostream &operator<<(ostream &os, const TennisPlayer &player) {
        string array = (player.play == 1) ? "yes" : "no";
        os << "First Name: " << player.firstName << " Second Name: " << player.secondName << " Plays in League: " << array ;
        return os;
    }
};

class RankedTennisPlayer : public TennisPlayer{
private:
    int rank;
public:
    RankedTennisPlayer(const TennisPlayer &other, int rank) : TennisPlayer(other){
        this->rank = rank;
    }
    RankedTennisPlayer(char *firstName="", char *secondName="", bool play = false, int rank=0){
        this->rank = rank;
        strcpy(this->firstName, firstName);
        strcpy(this->secondName, secondName);
        this->play = play;
    }

    friend ostream &operator<<(ostream &os, const RankedTennisPlayer &player) {
        os << static_cast<const TennisPlayer &>(player) << " Rank: " << player.rank << endl;
        return os;
    }

};

int main() {
    TennisPlayer rf("Roger", "Federer");
    TennisPlayer ng("Novak", "Djokovikj");
    cout << rf;
    cout << ng;
    //TennisPlayer t;
    RankedTennisPlayer rn("Rafael", "Nadal", true, 2750);
    cout << rn<<endl;
    TennisPlayer tp = rn;
    cout << tp<<endl;
    //RankedTennisPlayer copy(tp);
    RankedTennisPlayer copy(ng, 3320);
    cout << copy<<endl;
    return 0;
}