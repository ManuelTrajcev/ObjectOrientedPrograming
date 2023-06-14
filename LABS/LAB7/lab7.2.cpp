#include <iostream>
#include <cstring>

using namespace std;

class MarathonRunner {
protected:
    char *name;
    char country[40];
    double avgSpeed;
    double distance;
    double time;
public:

    MarathonRunner(char *name = "", char *country = "", double avgSpeed = 0, double distance = 0, double time = 0) {
        this->avgSpeed = avgSpeed;
        this->distance = distance;
        this->time = time;
        strcpy(this->country, country);
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    MarathonRunner(const MarathonRunner &other) {
        this->avgSpeed = other.avgSpeed;
        this->distance = other.distance;
        this->time = other.time;
        strcpy(this->country, other.country);
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }

    MarathonRunner &operator=(const MarathonRunner &other) {
        if (this != &other) {
            this->avgSpeed = other.avgSpeed;
            this->distance = other.distance;
            this->time = other.time;
            strcpy(this->country, other.country);
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
        }
        return *this;
    }

    double rating() {
        return (avgSpeed * 0.45 + distance * 0.3 + time * 0.25);
    }

    void print() {
        cout << name << " - " << country << endl;
        cout << "Average speed: " << avgSpeed << endl;
        cout << "Total distance: " << distance << endl;
        cout << "Total time: " << time << endl;
        cout << "Rating: " << rating() << endl;
    }

    ~MarathonRunner() {
        delete[] name;
    }

};

class EliteMarathonRunner : public MarathonRunner {
private:
    double eliteAvgSpeed;
    double eliteDistance;
    double eliteTime;
public:
    EliteMarathonRunner(char *name = "", char *country = "", double avgSpeed = 0, double distance = 0, double time = 0,
                        double eliteAvgSpeed = 0,
                        double eliteDistance = 0, double eliteTime = 0) : MarathonRunner(name, country, avgSpeed,
                                                                                         distance,
                                                                                         time),
                                                                          eliteAvgSpeed(eliteAvgSpeed),
                                                                          eliteDistance(eliteDistance),
                                                                          eliteTime(eliteTime) {

    }

    EliteMarathonRunner(const MarathonRunner &other, double eliteAvgSpeed = 0, double eliteDistance = 0,
                        double eliteTime = 0)
            : MarathonRunner(other), eliteAvgSpeed(eliteAvgSpeed), eliteDistance(eliteDistance), eliteTime(eliteTime) {

    }

    EliteMarathonRunner(const EliteMarathonRunner &other) {
        this->avgSpeed = other.avgSpeed;
        this->distance = other.distance;
        this->time = other.time;
        strcpy(this->country, other.country);
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->eliteAvgSpeed = other.eliteAvgSpeed;
        this->eliteDistance = other.eliteDistance;
        this->eliteTime = other.eliteTime;
    }

    EliteMarathonRunner &operator=(const EliteMarathonRunner &other) {
        if (this != &other) {
            this->avgSpeed = other.avgSpeed;
            this->distance = other.distance;
            this->time = other.time;
            strcpy(this->country, other.country);
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            this->eliteAvgSpeed = other.eliteAvgSpeed;
            this->eliteDistance = other.eliteDistance;
            this->eliteTime = other.eliteTime;
        }
        return *this;
    }

//    ~EliteMarathonRunner() {
//        delete[] name;
//    }

    double eliteRating() {
        return (eliteAvgSpeed * 0.7 + eliteDistance * 0.1 + eliteTime * 0.3);
    }

    double rating() {
        double r = MarathonRunner::rating() + eliteRating();
        return r;
    }

    void print() {
        MarathonRunner::print();
        cout << "Elite Rating: " << eliteRating()<<endl;
        cout << "New Rating: " << rating()/2<<endl;
    }
};

int main() {

    char name[50];
    char country[40];
    double avgSpeed;
    double distance;
    double time;
    double EliteavgSpeed;
    double Elitedistance;
    double Elitetime;

    MarathonRunner *RUNNERs = new MarathonRunner[5];
    EliteMarathonRunner *elRUNNERs = new EliteMarathonRunner[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "MARATHON RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> country >> avgSpeed >> distance >> time;
            RUNNERs[i] = MarathonRunner(name, country, avgSpeed, distance, time);
            RUNNERs[i].print();
        }
    } else if (n == 2) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> country >> avgSpeed >> distance >> time;
            cin >> EliteavgSpeed >> Elitedistance >> Elitetime;
            RUNNERs[i] = MarathonRunner(name, country, avgSpeed, distance, time);
            elRUNNERs[i] = EliteMarathonRunner(RUNNERs[i], EliteavgSpeed, Elitedistance, Elitetime);
        }

        cout << "NBA RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            RUNNERs[i].print();

        cout << "ELITE RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            elRUNNERs[i].print();

    } else if (n == 3) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> country >> avgSpeed >> distance >> time;
            cin >> EliteavgSpeed >> Elitedistance >> Elitetime;
            elRUNNERs[i] = EliteMarathonRunner(name, country, avgSpeed, distance, time,
                                               EliteavgSpeed, Elitedistance, Elitetime);
        }
        cout << "ELITE RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            elRUNNERs[i].print();

    }

    delete[] RUNNERs;
    delete[] elRUNNERs;
}
