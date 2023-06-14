#include <iostream>

using namespace std;

class Room {
protected:

public:
    virtual void displayRoomInfo() = 0;

    virtual void displayRoomPrice() = 0;
};

class StandardRoom : public Room {
private:
    bool hasBathroom;
public:
    StandardRoom(bool hasBathroom = false) : hasBathroom(hasBathroom) {

    }

    void displayRoomInfo() {
        cout << "This is a standard room with a queen-sized bed";
        if (hasBathroom) {
            cout << " and a bathroom";
        }
        cout << "." << endl;
    }

    void displayRoomPrice() {
        if (hasBathroom)
            cout << "The price for a standard room is $100 per night." << endl;
        else
            cout << "The price for a standard room is $80 per night." << endl;

    }
};

class DeluxeRoom : public Room {
private:
    bool hasBalcony;
public:
    DeluxeRoom(bool hasBalcony = false) : hasBalcony(hasBalcony) {

    }

    void displayRoomInfo() {
        cout << "This is a deluxe room with a king-sized bed, a bathroom, a mini-fridge";
        if (hasBalcony) {
            cout << " and a balcony";
        }
        cout << "." << endl;
    }

    void displayRoomPrice() {
        if (hasBalcony)
            cout << "The price for a deluxe room is $200 per night." << endl;
        else
            cout << "The price for a deluxe room is $160 per night." << endl;
    }

};


int main() {
    Room *rooms[5];

    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "TEST CASE 1: TESTING STANDARD ROOM CLASS" << endl;

        for (int i = 0; i < 5; i++) {
            rooms[i] = new StandardRoom();
            rooms[i]->displayRoomInfo();
            rooms[i]->displayRoomPrice();
        }
    } else if (testCase == 2) {
        cout << "TEST CASE 2: TESTING DELUXE ROOM CLASS" << endl;
        for (int i = 0; i < 5; i++) {
            rooms[i] = new DeluxeRoom();
            rooms[i]->displayRoomInfo();
            rooms[i]->displayRoomPrice();
        }
    } else {
        cout << "TEST CASE 3: TESTING BOTH CLASSES" << endl;
        for (int i = 0; i < 5; i++) {
            if (i % 2) {
                bool hasBalcony;
                cin >> hasBalcony;
                rooms[i] = new DeluxeRoom(hasBalcony);
            } else {
                bool hasBathroom;
                cin >> hasBathroom;
                rooms[i] = new StandardRoom(hasBathroom);
            }
            rooms[i]->displayRoomInfo();
            rooms[i]->displayRoomPrice();
        }
    }

    return 0;
}