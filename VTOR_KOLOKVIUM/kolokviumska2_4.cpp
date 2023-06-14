#include <cstring>
#include <iostream>

using namespace std;


enum Size {
    small, large, family
};

class Pizza {
protected:
    char name[20];
    char ingredients[100];
    float inPrice;
public:
    Pizza(const char *name = "", const char *ingredients = "", float inPrice = 0) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->inPrice = inPrice;
    }

    virtual double price() = 0;

    virtual void print() = 0;

    friend ostream &operator<<(ostream &os, Pizza &pizza) {
        os << pizza.name << ": " << pizza.ingredients;
        pizza.print();
        os << " - " << pizza.price() << endl;
        return os;
    }

    const char *getName() const {
        return name;
    }

    bool operator<(Pizza &rhs) {
        return price() < rhs.price();
    }


};

class FlatPizza : public Pizza {
private:
    Size s;
public:
    FlatPizza(const char *name = "", const char *ingredients = "", float inPrice = 0, Size s = small) : Pizza(name,
                                                                                                              ingredients,
                                                                                                              inPrice),
                                                                                                        s(s) {

    }

    double price() {
        double outPrice = inPrice;
        if (s == small) {
            outPrice += (inPrice * 0.1);
        } else if (s == large) {
            outPrice += (inPrice * 0.2);
        } else {
            outPrice += (inPrice * 0.3);
        }
        return outPrice;
    }

    void print() {
        char size[20];
        if (s == small) {
            strcpy(size, ", small");
        } else if (s == large) {
            strcpy(size, ", large");
        } else {
            strcpy(size, ", family");
        }
        cout << size;
    }
};

class FoldedPizza : public Pizza {
private:
    bool whiteFlour;
public:
    FoldedPizza(const char *name = "", const char *ingredients = "", float inPrice = 0, bool whiteFlour = true) : Pizza(
            name,
            ingredients,
            inPrice),
                                                                                                                  whiteFlour(
                                                                                                                          whiteFlour) {

    }

    double price() {
        double outPrice = inPrice;

        if (whiteFlour) {
            outPrice += (inPrice * 0.1);
        } else {
            outPrice += (inPrice * 0.3);
        }
        return outPrice;
    }

    void print() {
        char wf[10];
        if (whiteFlour) {
            strcpy(wf, ", wf");
        } else {
            strcpy(wf, ", nwf");
        }
        cout << wf;
    }

    void setWhiteFlour(bool whiteFlour) {
        FoldedPizza::whiteFlour = whiteFlour;
    }
};

void expensivePizza(Pizza **p, int n) {
    Pizza *max = p[0];
    for (int i = 1; i < n; ++i) {
        if (max->price() < p[i]->price()) {
            max = p[i];
        }
    }
    cout << *max;
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}
