#include <iostream>
#include <cstring>

using namespace std;

class SpaceObject {
    char name[100];
    char type[100];
    int distanceFromEarth;
public:
    SpaceObject() {
        strcpy(this->name, name);
        strcpy(this->type, type);
        this->distanceFromEarth = distanceFromEarth;
    }

    SpaceObject(char *name, char *type, int distanceFromEarth) {
        strcpy(this->name, name);
        strcpy(this->type, type);
        this->distanceFromEarth = distanceFromEarth;
    }

    const char *getName() const {
        return name;
    }

    const char *getType() const {
        return type;
    }

    int getDistanceFromEarth() {
        return distanceFromEarth;
    }

    void setDistanceFromEarth(int distanceFromEarth) {
        SpaceObject::distanceFromEarth = distanceFromEarth;
    }

    void setName(char *name) {
        strcpy(this->name, name);
    }

    void setType(char *type) {
        strcpy(this->type, type);
    }

    ~SpaceObject() {
    }

    void print() {
        cout << name << " (" << type << ") - distance: " << distanceFromEarth << " light years away from Earth" << endl;
    }
};

class Alien {
private:
    char name[100];
    int age;
    char homePlanet[100];
    int numObj;
    SpaceObject spaceObject[50];
public:
    Alien() {
//        strcpy(this->name, name);
//        strcpy(this->homePlanet, homePlanet);
//        this->age = age;
//        this->numObj = numObj;
    }

    Alien(char *name, int age, char *homePlanet, int numObj, SpaceObject *spaceObject) {
        strcpy(this->name, name);
        strcpy(this->homePlanet, homePlanet);
        this->age = age;
        this->numObj = numObj;
        for (int i = 0; i < numObj; ++i) {
            this->spaceObject[i]=spaceObject[i];
        }
    }

    Alien(const Alien &other) {
        strcpy(this->name, other.name);
        strcpy(this->homePlanet, other.homePlanet);
        this->age = other.age;
        this->numObj = other.numObj;
        for (int i = 0; i < numObj; ++i) {
            this->spaceObject[i]=spaceObject[i];
        }
    }

    ~Alien() {}

    void setName(char *name) {
        strcpy(this->name, name);
    }

    void setHomePlanet(char *homePlanert) {
        strcpy(this->homePlanet, homePlanert);
    }

    const char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void setAge(int age) {
        Alien::age = age;
    }

    const char *getHomePlanet() const {
        return homePlanet;
    }

    int getNumObj() const {
        return numObj;
    }

    void setNumObj(int numObj) {
        Alien::numObj = numObj;
    }

    const SpaceObject *getSpaceObject() const {
        return spaceObject;
    }

    SpaceObject getObjectClosestToEarth() {
        int favourite = 0;
        int closest = spaceObject[0].getDistanceFromEarth();
        for (int i = 0; i < numObj; ++i) {
            if (spaceObject[i].getDistanceFromEarth() < closest) {
                closest = spaceObject[i].getDistanceFromEarth();
                favourite = i;
            }
        }
        return spaceObject[favourite];
    }

    void print() {
        cout << "Alien name: " << name << endl;
        cout << "Alien age: " << age << endl;
        cout << "Alien homePlanet: " << homePlanet << endl;
        cout << "Favourite space object closest to earth: ";
        getObjectClosestToEarth().print();
    }
};

int main() {
    char name[100], homePlanet[100];
    int age, numObj;
    cin >> name >> age >> homePlanet >> numObj;
    //Testing default constructor for SpaceObject
    SpaceObject spaceObjects[numObj];
    for (int i = 0; i < numObj; i++) {
        char spaceObjectName[100], spaceObjectType[100];
        int distanceFromEarth;
        cin >> spaceObjectName >> spaceObjectType >> distanceFromEarth;
        //Testing constructor with arguments for SpaceObject
        spaceObjects[i] = SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
    }
    //Testing default constructor for Alien
    Alien alien;
    //Testing constructor with arguments for Alien and copy constructor for Alien
    alien = Alien(name, age, homePlanet, numObj, spaceObjects);
    Alien alien2 = Alien(alien);

    alien2.print();
    return 0;
}