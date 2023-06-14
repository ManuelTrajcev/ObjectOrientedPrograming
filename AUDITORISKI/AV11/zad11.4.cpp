#include <iostream>
#include <cstring>

using namespace std;


class NegativeValueException {
private:
    char name[50];
public:
    NegativeValueException(const char *name = "") {
        strcpy(this->name, name);
    }

    void showMessage() {
        cout << "The product " << name << " cannot have a negative value for a price" << endl;
    }
};

class Discount {
public:
    static float EUR_TO_MKD;
    static float USD_TO_MKD;

    virtual float discount_price() = 0;

    virtual float getPrice() = 0;

    virtual void print_rule() = 0;
};

float Discount::EUR_TO_MKD = 61.5;
float Discount::USD_TO_MKD = 58.4;

class Product {
protected:
    char name[50];
    float price;
public:
    Product(const char *name = "", float price = 0) {
        strcpy(this->name, name);
        this->price = price;
    }

    void changePrice(float newPrice) {
        if (newPrice < 0) {
            throw NegativeValueException(this->name);
        }
        this->price = newPrice;
    }
};

class FoodProduct : public Discount, public Product {
private:

public:
    FoodProduct(const char *name = "", float price = 0) : Product(name, price) {}

    float discount_price() {
        return price;
    }

    float getPrice() {
        return price * Discount::EUR_TO_MKD;
    }

    void print_rule() {
        cout << "No discount for food products" << endl;
    }

};

class Drinks : public Discount, public Product {
private:
    bool isAlcohol;
public:
    Drinks(const char *name = "", float price = 0, bool isAlcohol = false) : Product(name, price),
                                                                             isAlcohol(isAlcohol) {

    }

    float discount_price() {
        if (isAlcohol && price > 20.0) {
            return getPrice() * 0.95;
        }
        if (!isAlcohol && strcmp(name, "coca-cola") == 0) {
            return getPrice() * 0.9;
        } else {
            return getPrice();
        }
    }

    float getPrice() {
        return price * Discount::EUR_TO_MKD;
    }

    void print_rule() {
        cout << "Alcohol products with price larger than 20EUR -> 5%, Coca-cola 10%" << endl;
    }
};

class Cosmetics : public Discount, public Product {
private:

public:
    Cosmetics(const char *name = "", float price = 0) : Product(name, price) {}

    float discount_price() {
        if ((getPrice() * EUR_TO_MKD / USD_TO_MKD) > 20.0) {
            return getPrice() * 0.86;
        } else if (getPrice() > 5.0) {
            return getPrice() * 0.88;
        } else {
            return getPrice();
        }
    }

    float getPrice() {
        return price * EUR_TO_MKD;
    }

    void print_rule() {
        cout << "price is USD >20$ -> 14%, price is EUR>5 -> 12%" << endl;
    }
};


int main() {
    int n = 0;
    float newPrice;
    Discount **d = new Discount *[10];
    d[n++] = new FoodProduct("leb", 0.5);
    d[n++] = new Drinks("viski", 22, true);
    d[n++] = new FoodProduct("sirenje", 6.2);
    d[n++] = new Drinks("votka", 10, true);
    d[n++] = new Cosmetics("krema", 12);
    d[n++] = new Drinks("sok", 1.2, false);
    d[n++] = new Cosmetics("parfem", 60);

    for (int i = 0; i < n; ++i) {
        cout << i << endl;
        cout << d[i]->getPrice() << endl;
        cout << d[i]->discount_price() << endl;
        d[i]->print_rule();
    }
    for (int i = 0; i < n; ++i) {
        Cosmetics *casted = dynamic_cast<Cosmetics *>(d[i]);
        if (casted) {
            int newPrice;
            cin >> newPrice;
            try {
                casted->changePrice(newPrice);
            } catch (NegativeValueException exception) {
                exception.showMessage();
            }
        }
    }
    return 0;
}