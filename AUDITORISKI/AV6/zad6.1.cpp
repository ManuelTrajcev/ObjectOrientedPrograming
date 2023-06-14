#include <iostream>
#include <cstring>

using namespace std;

class Array {
private:
    int *array;
    int count;
    int capacity;
public:
    Array(int capacity = 0) {
        this->capacity = capacity;
        this->count = 0;
        array = new int[capacity];
    }

    Array(const Array &other) {
        this->capacity = other.capacity;
        this->count = other.count;
        array = new int[capacity];
        for (int i = 0; i < count; ++i) {
            this->array[i] = other.array[i];
        }
    }

    Array &operator=(const Array &other) {
        if (this != &other) {
            this->capacity = other.capacity;
            this->count = other.count;
            delete[] array;
            array = new int[capacity];
            for (int i = 0; i < count; ++i) {
                this->array[i] = other.array[i];
            }
        }
        return *this;
    }

    ~Array() {
        delete[] array;
    }

    Array &operator+=(int n) {
        if (count == capacity) {
            capacity *= 2;
            int *tmp = new int[capacity];
            for (int i = 0; i < count; ++i) {
                tmp[i] = array[i];
            }
            delete[] array;
            array = tmp;
        }
        array[count++] = n;
        return *this;
    }

    Array &operator-=(int n) {
        int newSize = 0, j = 0;
        for (int i = 0; i < count; ++i) {
            if (array[i] != n) {
                array[j++] = array[i];
                newSize++;
            }
        }
        count = newSize;
        return *this;
    }

    int *getArray() const {
        return array;
    }

    int getCount() const {
        return count;
    }

    int getCapacity() const {
        return capacity;
    }

    friend ostream &operator<<(ostream &o, Array &a) {
        o << a.getCapacity() << endl;
        for (int i = 0; i < a.getCount(); ++i) {
            o << a.getArray()[i] << " - ";
        }
        o << endl;
        return o;
    }

    int &operator[](int i) {
        int error = -1;
        if (i >= 0 && i < count) {
            return array[i];
        } else {
            cout << "Error";
            return error;
        }
    }

    bool operator==(Array &a) {
        if (this->count != a.count) {
            return false;
        }
        for (int i = 0; i < count; ++i) {
            if (this->array[i] != a.array[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(Array &a) {
        if (this->count != a.count) {
            return true;
        }
        for (int i = 0; i < count; ++i) {
            if (this->array[i] != a.array[i]) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Array x(3);
    x += 2;
    x += 4;
    x += 5;
    x += 6;
    x += 7;
    cout << x;
    x -= 6;
    cout << x;
    x[2] = 99;
    cout << x;
    Array y(x);
    if (x != y) {
        cout << "Yes";
    }else{
        cout<<"No";
    }
    return 0;
}