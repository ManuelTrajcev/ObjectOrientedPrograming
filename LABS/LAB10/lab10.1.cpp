#include<iostream>
#include<cstring>

using namespace std;


class UserAlreadyExistsException {
    char username[100];
public:
    explicit UserAlreadyExistsException(char *username) {
        strcpy(this->username, username);
    }

    void showMessage() {
        cout << "User with username " << username << " already exists!" << endl;
    }
};

class UserNotFoundException {
    char name[50];
public:
    UserNotFoundException(char *name) {
        strcpy(this->name, name);
    }

    void showMessage() {
        cout << "User with username " << name << " was not found!" << endl;
    }
};

class FriendsLimitExceededException {
private:
    int n;
public:
    explicit FriendsLimitExceededException(int n) : n(n) {}

    void showMassage() {
        cout << "Can't have more than " << n << " friends." << endl;
    }
};

class User {
private:
    char username[50];
    int age;
    int friends;
    static int LIMIT;
public:
    User(char *username = "", int age = 18) : age(age) {
        strcpy(this->username, username);
        friends = 0;
    }

        User &operator++() {
        ++friends;
        return *this;
    }

    friend class SocialNetwork;

    static void setLimit(int l) {
        LIMIT = l;
    }

    int getFriends() const;
};

int User::LIMIT = 3;

int User::getFriends() const {
    return friends;
}

class SocialNetwork {
private:
    User *users;
    int n;
public:
    SocialNetwork() {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u) {
        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, u.username) == 0) {
                throw UserAlreadyExistsException(u.username);
            }
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;
    }

    void friendRequest(char *firstUsername, char *secondUsername) {
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, firstUsername) == 0) {
                for (int j = 0; j < n; j++) {
                    if (strcmp(users[j].username, secondUsername) == 0) {
                        if (users[i].getFriends() == User::LIMIT || users[j].getFriends() == User::LIMIT) {
                            throw FriendsLimitExceededException(User::LIMIT);
                        }
                        ++users[i];
                        ++users[j];
                        return;
                    }
                }
                throw UserNotFoundException(secondUsername);
            }
        }
        throw UserNotFoundException(secondUsername);
    }

    friend ostream &operator<<(ostream &os, const SocialNetwork &network) {
        os << "Users: " << endl;
        for (int i = 0; i < network.n; i++) {
            os << network.users[i] << endl;
        }
        return os;
    }
};


int main() {
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char username[50];
        int age;
        cin >> username >> age;
        User u(username, age);
        try {
            sn += u;
        } catch (UserAlreadyExistsException exception) {
            exception.showMessage();
        }

    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin >> friendships;
    for (int i = 0; i < friendships; i++) {
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            try {
                sn.friendRequest(username1, username2);
            } catch (FriendsLimitExceededException exception) {
                exception.showMassage();
            }
        } catch (UserNotFoundException exception) {
            exception.showMessage();
        }

    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    cin >> friendships;
    User::setLimit(maxFriends);
    for (int i = 0; i < friendships; i++) {
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            try {
                sn.friendRequest(username1, username2);
            } catch (UserNotFoundException exception) {
                exception.showMessage();
            }
        }catch (FriendsLimitExceededException e){
            e.showMassage();
        }
    }
    cout << sn;
    return 0;
}