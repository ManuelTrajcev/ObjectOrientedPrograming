#include <iostream>
#include <cstring>

using namespace std;

class User {
private:
    char *username;
    char *companyName;
    int position;

    void copy(const User &other) {
        this->username = new char[strlen(other.username)];
        strcpy(this->username, other.username);
        this->companyName = new char[strlen(other.companyName)];
        strcpy(this->companyName, other.companyName);
        this->position = other.position;
    }

public:
    User(const char *username = "", const char *companyName = "", int position = 0) {
        this->username = new char[strlen(username)];
        strcpy(this->username, username);
        this->companyName = new char[strlen(companyName)];
        strcpy(this->companyName, companyName);
        this->position = position;
    }

    User(const User &other) {
        copy(other);
    }

    User &operator=(const User &other) {
        if (this != &other) {
            delete[] username;
            delete[] companyName;
            copy(other);
        }
        return *this;
    }

    virtual ~User() {
        delete[] username;
        delete[] companyName;
    }

    bool operator==(const User &rhs) const {
        return !(strcmp(this->username, rhs.username));
    }

    int getPosition() const {
        return position;
    }

        friend istream &operator>>(istream &is, User &user) {
        is >> user.username >> user.companyName >> user.position;
        return is;
    }
};

class OperationNotSupported {
    char message[50];
public:
    OperationNotSupported(const char *message = "") {
        strcpy(this->message, message);
    }

    void showMessage() {
        cout << message << endl;
    }
};

class Group {
protected:
    User *users;
    int num;
    char name[50];

    void copy(const Group &g) {
        strcpy(this->name, g.name);
        this->num = g.num;
        users = new User[num];
        for (int i = 0; i < num; ++i) {
            users[i] = g.users[i];
        }
    }

public:
    Group(const char *name = "test") {
        num = 0;
        this->users = new User[num];
        for (int i = 0; i < num; ++i) {
            this->users[i] = users[i];
        }
    }

    Group(const Group &g) {
        copy(g);
    }

    Group &operator=(const Group &g) {
        if (this != &g) {
            delete[] users;
            copy(g);
        }
        return *this;
    }

    virtual ~Group() {
        delete[] users;
    }

    virtual void addMember(User &u) {
        for (int i = 0; i < num; ++i) {
            if (users[i] == u) {
                throw OperationNotSupported("Username already exists");
            }
        }
        User *tmp = new User[num + 1];
        for (int i = 0; i < num; ++i) {
            tmp[i] = users[i];
        }
        tmp[num++] = u;
        delete[] users;
        users = tmp;
    }

    virtual double averagePositionOfMembers() const {
        double sum = 0;
        for (int i = 0; i < num; ++i) {
            sum += users[i].getPosition();
        }
        if (num == 0) {
            return 0;
        }
        return sum / num;
    }

    virtual double rating() const {
        return (10 - averagePositionOfMembers() * num / 100.0);
    }

    friend ostream &operator<<(ostream &os, const Group &group) {
        os << "Group: " << group.name << endl;
        os << "Members: " << group.num << endl;
        os << "Rating: " << group.rating() << endl;
        os << "Members list: " << endl;
        if (group.num == 0) {
            os << "EMPTY" << endl;
            return os;
        }
        for (int i = 0; i < group.num; ++i) {
            os << i + 1 << ". " << group.users[i] << endl;
        }
        return os;
    }
};

class PrivateGroup : public Group {
    static int CAPACITY;
    const static double COEF;
public:
    PrivateGroup(const char *name = "") : Group(name) {

    }

    static void setCapacity(int capacity) {
        CAPACITY = capacity;
    }

    void addMember(User &u) {
        if (num == CAPACITY) {
            throw OperationNotSupported("The group's capacity has been excited");
        }
        Group::addMember(u);
    }

    double averagePositionOfMembers() const {
        double sum = 0;
        for (int i = 0; i < num; ++i) {
            sum += users[i].getPosition();
        }
        if (num == 0) {
            return 0;
        }
        return sum / num;
    }

    double rating() const {
        return (10 - averagePositionOfMembers() * ((double)num / CAPACITY) * COEF);
    }

    static int getCapacity() {
        return CAPACITY;
    }

    friend ostream &operator<<(ostream &os, const PrivateGroup &pg) {
        os << "Private ";
        Group g(pg);
        return os << g;
    }
};

int PrivateGroup::CAPACITY = 10;
const double PrivateGroup::COEF = 0.8;


int main() {
    int n;
    Group *g = new Group("FINKI Students");
    cin >> n;
    for (int i = 0; i < n; ++i) {
        User u;
        cin >> u;

        try {
            g->addMember(u);
        }
        catch (OperationNotSupported e) {
            e.showMessage();
        }
    }
    return 0;
}