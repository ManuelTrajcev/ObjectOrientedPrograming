#include <iostream>
#include <cstring>

using namespace std;

class Film {
    char name[100];
    float rating;
    float revenue;
public:
    Film() {
    }

    Film(char name[100], float rating, float revenue) {
        strcpy(this->name, name);
        this->rating = rating;
        this->revenue = revenue;
    }

    void setName(char *name) {
        strcpy(this->name, name);
    }

    void setRating(float rating) {
        this->rating = rating;
    }

    void setRevenue(float revenue) {
        this->revenue = revenue;
    }

    const char *getName() const {
        return name;
    }

    float getRating() const {
        return rating;
    }

    float getRevenue() const {
        return revenue;
    }

    void display() {
        cout << "Name of film: " << name << endl;
        cout << "Rating: " << rating << endl;
        cout << "Revenue: " << revenue << endl;
    }
};

void printMostPopularFilm(Film *films, int n) {
    float max = 0;
    int maxIndex = 0;
    for (int i = 0; i < n; ++i) {
        if (films[i].getRevenue() > max) {
            max = films[i].getRevenue();
            maxIndex = i;
        }
    }
    films[maxIndex].display();
}

int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    double rating;
    double revenue;

    for (int i = 0; i < n - 1; i++) {
        cin >> name;
        cin >> rating;
        cin >> revenue;

        // testing constructor with arguments
        films[i] = Film(name, rating, revenue);

    }


    // testing set methods and display for last element
    cin >> name;
    cin >> rating;
    cin >> revenue;
    films[n - 1].setName(name);
    films[n - 1].setRating(rating);
    films[n - 1].setRevenue(revenue);

    cout << "-->Testing set methods and display()" << endl;
    films[n - 1].display();
    cout << endl;

    cout << "-->Testing printMostPopularFilm()" << endl;
    printMostPopularFilm(films, n);
    return 0;
}