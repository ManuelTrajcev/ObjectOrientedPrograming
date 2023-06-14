#include <iostream>
#include <cstring>

using namespace std;

class Country {
    char name[100];
    char capital[100];
    float area;
    float population;
public:
    Country() {}

    Country(char name[100], char capital[100], float area, float population) {
        strcpy(this->name, name);
        strcpy(this->capital, capital);
        this->area = area;
        this->population = population;
    }

    void setName(char *name) {
        strcpy(this->name, name);
    }

    void setCapital(char *capital) {
        strcpy(this->capital, capital);
    }

    void setArea(float area) {
        Country::area = area;
    }

    void setPopulation(float population) {
        Country::population = population;
    }

    const char *getName() const {
        return name;
    }

    const char *getCapital() const {
        return capital;
    }

    float getArea() const {
        return area;
    }

    float getPopulation() const {
        return population;
    }

    void display() {
        cout << "Country: " << name << endl;
        cout << "Capital: " << capital << endl;
        cout << "Area: " << area << endl;
        cout << "Population: " << population << endl;
    }

    ~Country() {}
};

void sortCountries(Country *countries, int n) {
    for (int i = 0; i < n; ++i) {
        float min = countries[i].getArea();
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (countries[j].getArea() < min) {
                min = countries[j].getArea();
                minIndex = j;
            }
        }
        if (i != minIndex)
            swap(countries[i], countries[minIndex]);
    }
    for (int i = 0; i < n; ++i) {
        countries[i].display();

    }
}

int main() {
    int n;
    cin >> n;
    Country countries[100];

    char name[100];
    char capital[100];
    double area;
    double population;

    for (int i = 0; i < n - 1; i++) {
        cin >> name;
        cin >> capital;
        cin >> area;
        cin >> population;

        // testing constructor with arguments
        countries[i] = Country(name, capital, area, population);

    }


    // testing set methods and display for last element
    cin >> name;
    cin >> capital;
    cin >> area;
    cin >> population;
    countries[n - 1].setName(name);
    countries[n - 1].setCapital(capital);
    countries[n - 1].setArea(area);
    countries[n - 1].setPopulation(population);

    cout << "-->Testing set methods and display()" << endl;
    countries[n - 1].display();
    cout << endl;

    cout << "-->Testing sortCountries()" << endl;
    sortCountries(countries, n);
    return 0;
}