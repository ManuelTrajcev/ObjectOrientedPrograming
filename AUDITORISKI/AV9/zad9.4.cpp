#include <iostream>
#include <cstring>

using namespace std;

class Product {
protected:
    char name[50];
    float price;
public:
    Product(char *name = "", float price = 0) {
        this->price = price;
        strcpy(this->name, name);
    }
};

class Discountable {

public:
    virtual float getPrice() = 0;

    virtual void print() = 0;

    virtual float getPriceWithDiscount() = 0;
};

class FoodProduct : public Product, public Discountable {
private:
    int calories;
public:
    FoodProduct(char *name = "", float price = 0, int calories = 0) : Product(name, price),
                                                                      calories(calories) {

    }

    float getPrice() {
        return price;
    }

    float getPriceWithDiscount() {
        if (calories > 500) {
            return 0.8 * price;
        } else if (calories > 100) {
            return 0.9 * price;
        } else {
            return 0.95 * price;
        }
    }

    void print() {
        cout << "FoodProduct: " << name << " Calories: " << calories << " Price: " << getPrice()
             << " Price with discount: "
             << getPriceWithDiscount() << endl;
    }
};

class DigitalProduct : public Product, public Discountable {
private:
    float sizeInMb;
public:
    DigitalProduct(char *name = "", float price = 0, float sizeInMb = 0) : Product(name, price),
                                                                           sizeInMb(sizeInMb) {

    }

    float getPrice() {
        return price;
    }

    float getPriceWithDiscount() {
        if (sizeInMb > 1024) {
            return 0.7 * price;
        } else if (sizeInMb > 512) {
            return 0.85 * price;
        } else {
            return 0.925 * price;
        }
    }

    void print() {
        cout << "DigitalProduct: " << name << " Size in Mb: " << sizeInMb << " Price: " << getPrice()
             << " Price with discount: "
             << getPriceWithDiscount() << endl;
    }

};

float totalDiscount(Discountable **d, int n) {
    float sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += (d[i]->getPrice() - d[i]->getPriceWithDiscount());
    }
    return sum;
}

int countFoodProducts(Discountable **d, int n) {
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        FoodProduct *casted = dynamic_cast<FoodProduct *>(d[i]);
        if (casted != 0) {
            counter++;
        }
    }
    return counter;
}

int main() {
    int n;
    cin >> n;
    Discountable **d = new Discountable *[n];
    for (int i = 0; i < n; ++i) {
        int type;
        char name[50];
        float price;
        float size;
        int caloires;
        cin >> type;
        if (type == 1) {
            cin >> name >> price >> caloires;
            d[i] = new FoodProduct(name, price, caloires);
        } else {
            cin >> name >> price >> size;
            d[i] = new DigitalProduct(name, price, size);
        }
    }

    for (int i = 0; i < n; ++i) {
        d[i]->print();
    }

    cout << "Total discount: " << totalDiscount(d, n)<<endl;
    cout << "Total Food Products: " << countFoodProducts(d, n)<<endl;
    cout << "Total Digital Products: " << n - countFoodProducts(d, n);

    return 0;
}