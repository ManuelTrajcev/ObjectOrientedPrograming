#include <iostream>
#include <cstring>

using namespace std;

class FoodItem {
protected:
    char *type;
    int num;
public:
    FoodItem(char *type = "", int num = 0) {
        this->num = num;
        this->type = new char[strlen(type) + 1];
        strcpy(this->type, type);
    }

    virtual int getPrice() = 0;

    virtual int getTime() = 0;

    virtual ~FoodItem() {
        delete[] type;
    }

    char *getType() const {
        return type;
    }
};

class Pizza : public FoodItem {
private:
    char *dough;
public:
    Pizza(char *type = "", int num = 0, char *dough = "") : FoodItem(type, num) {
        this->dough = new char[strlen(dough) + 1];
        strcpy(this->dough, dough);
    }

    ~Pizza() {
        delete[] dough;
    }

    int getPrice() {
        if (strcmp(dough, "wholeWheat") == 0) {
            return num * 250;
        } else {
            return num * 350;
        }
    }

    int getTime() {
        return num * 25;
    }


};

class Steak : public FoodItem {
private:
    bool cooked;
public:
    Steak(char *type = "", int num = 0, bool cooked = false) : FoodItem(type, num), cooked(cooked) {

    }

    int getPrice() {
        return num * 1300;
    }

    int getTime() {
        if (cooked) {
            return num * 20;
        } else {
            return num * 15;
        }
    }
};

FoodItem *getMaxFoodItem(FoodItem **items, int n) {
    FoodItem *max = items[0];
    for (int i = 0; i < n; ++i) {
        if (max->getPrice() < items[i]->getPrice()) {
            max = items[i];
        }
    }
    return max;
}


int main() {
    FoodItem *p;
    int n;
    cin >> n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i < n; ++i) {
        cin >> type;
        cin >> size;


        if (strcmp(type, "pizza") == 0) {
            cin >> dough;
            items[i] = new Pizza(type, size, dough);
        } else {
            cin >> cooked;
            items[i] = new Steak(type, size, cooked);
        }

    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout << "Type: " << it->getType() << endl;
    cout << "The max price is: " << it->getPrice() << endl;
    cout << "Time to cook: " << it->getTime();
    return 0;
}