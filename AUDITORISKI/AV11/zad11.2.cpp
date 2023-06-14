#include <iostream>
#include <cstring>

using namespace std;

class NotValidUsernameException {
private:
    char notValidUsername[50];
public:
    NotValidUsernameException(const char *email = "") {
        strcpy(notValidUsername, email);
    }

    void showMassage() {
        cout << notValidUsername << " is not valid! Try again!" << endl;
    }
};

class User {
protected:
    int id;
    char username[50];
    static int ID_TRACKER;
public:
    User(char *username = "") {
        bool atSignFound = false;
        bool dotSignFound = false;
        for (int i = 0; i < strlen(username); ++i) {
            if (username[i] == '@') {
                atSignFound = true;
            }
            if (atSignFound) {
                if (username[i] == '.') {
                    dotSignFound = true;
                }
            }
        }
        if (!atSignFound || !dotSignFound) {
            throw NotValidUsernameException(username);
        }
        this->id = ID_TRACKER++;
        strcpy(this->username, username);
    }

    void print() {
        cout << id << ": " << username << endl;
    }
};

int User::ID_TRACKER = 1;

int main() {
    try {
        User u1("manueltrajcev7@gmail.com");
        u1.print();

        User u2("perohristov@gmail.com");
        u2.print();

        User u3("Stole");
        u3.print();
    }
    catch (NotValidUsernameException e) {
        e.showMassage();
    }
    return 0;
}