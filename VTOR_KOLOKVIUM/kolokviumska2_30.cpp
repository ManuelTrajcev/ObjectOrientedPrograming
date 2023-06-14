#include <iostream>
#include <cstring>

using namespace std;

class InvalidOperation {
private:
    char msg[300];
public:
    InvalidOperation(char *msg) {
        strcpy(this->msg, msg);
    }

    void print() {
        cout << msg << endl;
    }
};

class Event {
private:
    char *name;
    int guests;
    int month;
    bool active;
    int maxCapacity;
public:
    Event(const char *name = "", int guests = 0, int month = 0, bool active = false, int maxCapacity = 0) {
        this->guests = guests;
        this->month = month;
        this->active = active;
        this->maxCapacity = maxCapacity;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Event(const Event &other) {
        this->guests = other.guests;
        this->month = other.month;
        this->active = other.active;
        this->maxCapacity = other.maxCapacity;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }

    Event &operator=(const Event &other) {
        if (this != &other) {
            this->guests = other.guests;
            this->month = other.month;
            this->active = other.active;
            this->maxCapacity = other.maxCapacity;
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
        }
        return *this;
    }

    ~Event() {
        delete[] name;
    }

    friend ostream &operator<<(ostream &os, const Event &event) {
        os << event.name << " " << event.guests << " " << event.month << endl;
        return os;
    }

    Event &operator+(const Event &add) {
        if (this->month != add.month) {
            throw InvalidOperation("Can't merge events from different months");
        }
        if ((this->guests + add.guests) > this->maxCapacity) {
            throw InvalidOperation("Can't merge events which have more guests then the capacity");
        }
        char *newName = new char[strlen(this->name) + strlen(add.name) + 4];
        strcpy(newName, this->name);
        strcat(newName, " & ");
        strcat(newName, add.name);
        delete[] this->name;
        this->name = new char[strlen(newName) + 1];
        strcpy(this->name, newName);
        this->guests += add.guests;
        return *this;
    }

    bool isActive() const {
        return active;
    }
};

class EventCalendar {
private:
    int year;
    Event *events;
    int n;
public:
    EventCalendar(int year = 0, Event *events = nullptr, int n = 0) {
        this->n = n;
        this->year = year;
        this->events = new Event[n];
        for (int i = 0; i < n; ++i) {
            this->events[i] = events[i];
        }
    }

    EventCalendar(const EventCalendar &other) {
        this->n = other.n;
        this->year = other.year;
        this->events = new Event[other.n];
        for (int i = 0; i < n; ++i) {
            this->events[i] = other.events[i];
        }
    }

    EventCalendar &operator=(const EventCalendar &other) {
        if (this != &other) {
            this->n = other.n;
            this->year = other.year;
            delete[] events;
            this->events = new Event[other.n];
            for (int i = 0; i < n; ++i) {
                this->events[i] = other.events[i];
            }
        }
        return *this;
    }

    ~EventCalendar() {
        delete[] events;
    }

    friend ostream &operator<<(ostream &os, EventCalendar &calendar) {
        os << calendar.year << endl;
        for (int i = 0; i < calendar.n; ++i) {
            if (calendar.events[i].isActive()) {
                os << calendar.events[i];
            }
        }
        return os;
    }

    EventCalendar &operator+=(Event &add) {
        Event *tmp = new Event[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = events[i];
        }
        tmp[n++] = add;
        delete[] events;
        events = tmp;
        return *this;
    }

};

int main() {
    Event event1("Dfest", 51, 7, 1, 500);
    Event event2("Exit", 51, 7, 1, 300);
    try { event1 + event2; }
    catch (InvalidOperation exc) {
        exc.print();
    }
    cout << event1;
    EventCalendar eventCalendar(2023);
    eventCalendar += event1;
    eventCalendar += event2;
    cout << eventCalendar;
    return 0;
}