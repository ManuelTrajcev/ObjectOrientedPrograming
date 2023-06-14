#include <iostream>
#include <cstring>

using namespace std;

class Athlete {
protected:
    char name[20];
    int age;
public:
    Athlete(const char *name = "", int age = 0) : age(age) {
        strcpy(this->name, name);
    }

    virtual void displayInfo() = 0;

    virtual double value() = 0;

};

class Jumper : virtual public Athlete {
protected:
    double height;
public:
    Jumper(const char *name = "", int age = 0, double height = 0) : Athlete(name, age), height(height) {

    }

    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Height: " << height << endl;
    }

    double value() {
        return height;
    }

};

class Runner : virtual public Athlete {
protected:
    double speed;
public:
    Runner(const char *name = "", int age = 0, double speed = 0) : Athlete(name, age), speed(speed) {

    }

    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Speed: " << speed << endl;
    }

    double value() {
        return speed;
    }
};

class AllRoundAthlete : public Jumper, public Runner {
private:
    double stamina;
public:

    AllRoundAthlete(const char *name = "", int age = 0, float height = 0, float speed = 0, double stamina = 0) : Runner(name, age, speed),
                                                                                             Jumper(name, age, height), Athlete(name, age) {
        this->stamina = stamina;
    }

    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Speed: " << speed << endl;
        cout << "Height: " << height << endl;
        cout << "Stamina: " << stamina << endl;
    }
    double value(){
        return speed;
    }
};


Athlete *findAthleteWithMaxValue(Athlete **athletes, int n){
    double max = 0;
    int maxIndx = 0;
    for (int i = 0; i < n; ++i) {
        Runner *casted = dynamic_cast<Runner *>(athletes[i]);
        if (casted!=0){
            if (max<athletes[i]->value()){
                maxIndx = i;
                max = athletes[i]->value();
            }
        } else{
            if (max<athletes[i]->value()){
                maxIndx = i;
                max = athletes[i]->value();
            }
        }
    }

    return athletes[maxIndx];
}
int main() {
    char name[50];
    int age;
    double speed;
    double height;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>name;
        cin>>age;
        AllRoundAthlete allRoundAthlete(name, age, 13.6, 1.80, 6);
        allRoundAthlete.displayInfo();
    }
    else {

        cin >> n;

        Athlete **athletes = new Athlete *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> name >> age >> speed;

                athletes[i] = new Runner(name, age, speed);
            } else {
                cin >> name >> age >> height;

                athletes[i] = new Jumper(name, age, height);
            }

        }

        findAthleteWithMaxValue(athletes, n)->displayInfo();

    }


    return 0;
}