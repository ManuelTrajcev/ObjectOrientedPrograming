#include <iostream>
#include <cstring>

using namespace std;

class Vehicle {
public:
    char id[9];
    char *nameDriver;
    int location;
    int capacity;
    float km;
public:
    Vehicle(char *id = "", char *nameDriver = "", int location = 0, int capacity = 0, float km = 0) {
        this->capacity = capacity;
        this->location = location;
        this->km = km;
        strcpy(this->id, id);
        this->nameDriver = new char[strlen(nameDriver) + 1];
        strcpy(this->nameDriver, nameDriver);
    }

    Vehicle(const Vehicle &other) {
        this->capacity = other.capacity;
        this->location = other.location;
        this->km = other.km;
        strcpy(this->id, other.id);
        this->nameDriver = new char[strlen(other.nameDriver) + 1];
        strcpy(this->nameDriver, other.nameDriver);
    }

    Vehicle &operator=(const Vehicle &other) {
        if (this != &other) {
            this->capacity = other.capacity;
            this->location = other.location;
            this->km = other.km;
            strcpy(this->id, other.id);
            delete[] this->nameDriver;
            this->nameDriver = new char[strlen(other.nameDriver) + 1];
            strcpy(this->nameDriver, other.nameDriver);
        }
        return *this;
    }

    ~Vehicle() {
        delete[] nameDriver;
    }

    void print() {
        cout << "ID: " << id << " Driver's name: " << nameDriver << " Passenger capacity: " << capacity << " Location: "
             << location << " kms driven: " << km << endl;
    }

    const char *getId() const {
        return id;
    }

    int getLocation() const {
        return location;
    }

    void setLocation(int location) {
        Vehicle::location = location;
    }

    int getCapacity() const {
        return capacity;
    }

    void setCapacity(int capacity) {
        Vehicle::capacity = capacity;
    }

    float getKm() const {
        return km;
    }

    void setKm(float km) {
        Vehicle::km = km;
    }
};

class RideApp {
private:
    char name[20];
    Vehicle *vehicles;
    int count;
public:
    RideApp(char *name = "", int count = 0) {
        this->count = count;
        strcpy(this->name, name);
        this->vehicles = new Vehicle[count];
        for (int i = 0; i < count; ++i) {
            this->vehicles[i] = vehicles[i];
        }
    }

    RideApp(const RideApp &other) {
        this->count = other.count;
        strcpy(this->name, other.name);
        this->vehicles = new Vehicle[count];
        for (int i = 0; i < count; ++i) {
            this->vehicles[i] = other.vehicles[i];
        }
    }

    RideApp &operator=(const RideApp &other) {
        if (this != &other) {
            this->count = other.count;
            strcpy(this->name, other.name);
            delete[] this->vehicles;
            this->vehicles = new Vehicle[count];
            for (int i = 0; i < count; ++i) {
                this->vehicles[i] = other.vehicles[i];
            }
        }
        return *this;
    }

    ~RideApp() {
        delete[] vehicles;
    }

    void print() {
        cout << name << endl;
        if (count == 0) {
            cout << "EMPTY" << endl;
        }
        for (int i = 0; i < count; ++i) {
            vehicles[i].print();
        }
    }

    void signUpVehicle(const Vehicle &vehicle) {
        for (int i = 0; i < count; ++i) {
            if (strcmp(vehicles[i].getId(), vehicle.getId()) == 0) {
                return;
            }
        }
        Vehicle *tmp = new Vehicle[count + 1];
        for (int i = 0; i < count; ++i) {
            tmp[i] = vehicles[i];
        }
        tmp[count++] = vehicle;
        delete[] vehicles;
        vehicles = tmp;
    }

    void addRide(int area, int passengers, int distanceKm) {
        int max = 9999, maxIndex = 0;
        int flag = 0;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < count; ++j) {
                if ((((vehicles[j].getLocation() + i) == area) || ((vehicles[j].getLocation() - i) == area)) &&
                    vehicles[j].capacity >= passengers) {
                    if (vehicles[j].getKm() < max) {
                        max = vehicles[j].getKm();
                        maxIndex = j;
                        flag = 1;
                    }
                }
            }
            if (flag) {
                break;
            }
        }
        vehicles[maxIndex].setKm(vehicles[maxIndex].getKm() + distanceKm);
        vehicles[maxIndex].setLocation(area);
    }

};

int main() {
    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "CONSTRUCTOR Vehicle" << endl;
        Vehicle vehicle("NE1234SA", "Stefan", 5, 4);
        vehicle.print();
        cout << "CONSTRUCTOR Vehicle OK" << endl;
    } else if (testCase == 2) {
        cout << "COPY-CONSTRUCTOR Vehicle" << endl;
        Vehicle vehicle = Vehicle("NE1234SA", "Stefan", 5, 4);
        vehicle.print();
        cout << "COPY-CONSTRUCTOR Vehicle OK" << endl;
    } else if (testCase == 3) {
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = Vehicle" << endl;
        Vehicle vehicle;
        Vehicle vehicle2("NE1234SA", "Stefan", 5, 4);
        vehicle = vehicle2;
        vehicle.print();
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = Vehicle OK" << endl;
    } else if (testCase == 4) {
        cout << "CONSTRUCTOR RideApp" << endl;
        char appName[50];
        cin >> appName;
        RideApp app(appName);
        app.print();
        cout << "CONSTRUCTOR RideApp OK" << endl;
    } else if (testCase == 5) {
        cout << "RideApp signUpVehicle test" << endl;
        char appName[50];
        cin >> appName;
        RideApp app(appName);
        int n;
        cin >> n;
        char ID[9];
        char name[20];
        int location;
        int capacity;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location >> capacity;
            app.signUpVehicle(Vehicle(ID, name, location, capacity));
        }
        app.print();
    } else if (testCase == 6) {
        cout << "RideApp addRide test" << endl;
        char appName[50];
        cin >> appName;
        RideApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        int capacity;
        for (int i = 0; i < 4; i++) {
            cin >> ID >> name >> location >> capacity;
            app.signUpVehicle(Vehicle(ID, name, location, capacity));
        }
        cin >> n;
        for (int i = 0; i < n; i++) {
            int area, passengers, kms;
            cin >> area >> passengers >> kms;
            app.addRide(area, passengers, kms);
        }

        app.print();
    }
    return 0;
}

