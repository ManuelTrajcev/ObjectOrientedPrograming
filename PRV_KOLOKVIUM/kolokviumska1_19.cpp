#include <iostream>
#include <cstring>

using namespace std;


class IceCream {
private:
    char *name;
    char ingredients[100];
    float price;
    int discount;
public:
    IceCream(char *name = "", char *ingredients = "", float price = 0, int discount = 0) {
        this->price = price;
        this->discount = discount;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
    }

    IceCream(const IceCream &other) {
        this->price = other.price;
        this->discount = other.discount;
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->ingredients, other.ingredients);
    }

    IceCream &operator=(const IceCream &other) {
        if (this != &other) {
            this->price = other.price;
            this->discount = other.discount;
            delete[] name;
            this->name = new char[strlen(other.name) + 1];
            strcpy(this->name, other.name);
            strcpy(this->ingredients, other.ingredients);
        }
        return *this;
    }

    ~IceCream() {
        delete[] name;
    }

    friend ostream &operator<<(ostream &o, IceCream &i) {
        o << i.name << ": " << i.ingredients << " " << i.price;
        if (i.discount > 0) {
            o << " (" << i.price - (i.discount / 100.0 * i.price) << ")";
        }
        return o;
    }

    IceCream &operator++() {
        discount += 5;
        return *this;
    }

    IceCream &operator++(int) {
        IceCream tmp = *this;
        discount += 5;
        return tmp;
    }

    IceCream &operator+(char *string1) {
        char *tmp = new char[strlen(name) + strlen(string1) + 3];
        strcpy(tmp, name);
        strcat(tmp, " + ");
        strcat(tmp, string1);
        delete[] this->name;
        this->name = new char[strlen(tmp) + 1];
        strcpy(name, tmp);
        price += 10;
        return *this;
    }

    void setDiscount(int discount) {
        if (discount < 100 || discount > 0) {
            this->discount = discount;
        }
    }

    void setName(char *name) {
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
};

class IceCreamShop {
private:
    char name[70];
    IceCream *array;
    int count;
public:
    IceCreamShop(char *name = "", int count = 0, IceCream *array = nullptr) {
        this->count = count;
        strcpy(this->name, name);
        this->array = new IceCream[count];
        for (int i = 0; i < count; ++i) {
            this->array[i] = array[i];
        }
    }

    IceCreamShop(const IceCreamShop &other) {
        this->count = other.count;
        strcpy(this->name, other.name);
        this->array = new IceCream[count];
        for (int i = 0; i < count; ++i) {
            this->array[i] = other.array[i];
        }
    }

    IceCreamShop &operator=(const IceCreamShop &other) {
        if (this != &other) {
            this->count = other.count;
            strcpy(this->name, other.name);
            delete[] array;
            this->array = new IceCream[count];
            for (int i = 0; i < count; ++i) {
                this->array[i] = other.array[i];
            }
        }
        return *this;
    }

    ~IceCreamShop() {
        delete[] array;
    }

    friend ostream &operator<<(ostream &o, IceCreamShop &i) {
        o << i.name << endl;
        for (int j = 0; j < i.count; ++j) {
            o << i.array[j]<<endl;
        }
        return o;
    }

    IceCreamShop &operator+=(const IceCream &other) {
        IceCream *tmp = new IceCream[count + 1];
        for (int i = 0; i < count; ++i) {
            tmp[i] = array[i];
        }
        tmp[count++] = other;
        delete[] array;
        array = tmp;
        return *this;
    }
};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if (testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if (testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if (testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics += x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}