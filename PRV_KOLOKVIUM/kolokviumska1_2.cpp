#include <iostream>
#include <cstring>

using namespace std;

class List {
private:
    int *nums;
    int n;
public:
    List(int *nums = 0, int n = 0) {
        this->n = n;
        this->nums = new int[n];
        for (int i = 0; i < n; ++i) {
            this->nums[i] = nums[i];
        }
    }

    List(const List &other) {
        this->n = other.n;
        delete[] nums;
        this->nums = new int[other.n];
        for (int i = 0; i < n; ++i) {
            this->nums[i] = other.nums[i];
        }
    }

    List &operator=(const List &other) {
        if (this != &other) {
            this->n = other.n;
            this->nums = new int[other.n];
            for (int i = 0; i < n; ++i) {
                this->nums[i] = other.nums[i];
            }
        }
        return *this;
    }

    ~List() {
        delete[] nums;
    }

    int sum() {
        int sum = 0;

        for (int i = 0; i < n; ++i) {
            sum += nums[i];
        }
        return sum;
    }

    double average() {
        return 1.0 * sum() / n;
    }

    void pecati() {
        cout << n << ": ";
        for (int i = 0; i < n; ++i) {
            cout << nums[i] << " ";
        }
        cout << "sum: " << sum();
        cout << " average: " << average();
        cout << endl;
    }

    int getN() const {
        return n;
    }

};

class ListContainer {
private:
    List *lists;
    int n;
    int att;
    int fail;
public:
    ListContainer(int n = 0, int att = 0, int fail = 0) {
        this->att = 0;
        this->n = 0;
        this->lists = new List[n];
        this->fail = fail;
    }

    ListContainer(const ListContainer &other) {
        this->att = other.att;
        this->n = other.n;
        this->fail = other.fail;
        this->lists = new List[n];
        for (int i = 0; i < n; ++i) {
            this->lists[i] = other.lists[i];
        }
    }

    ListContainer &operator=(const ListContainer &other) {
        if (this != &other) {
            this->att = other.att;
            this->n = other.n;
            this->fail = other.fail;
            delete[] lists;
            this->lists = new List[n];
            for (int i = 0; i < n; ++i) {
                this->lists[i] = other.lists[i];
            }
        }
        return *this;
    }

    int sum() {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += lists[i].sum();
        }
        return sum;
    }

    double average() {
        double avg = 0;
        int count = 0;
        for (int i = 0; i < n; ++i) {
            count += lists[i].getN();
        }
        return 1.0 * sum() / count;
    }


    void addNewList(List &l) {
        for (int i = 0; i < n; ++i) {
            if (lists[i].sum() == l.sum()) {
                fail++;
                return;
            }
        }
        List *tmp = new List[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = lists[i];
        }
        tmp[n] = l;
        n++;
        delete[] lists;
        lists = tmp;
        att++;
    }

    void print() {
        if (n == 0) {
            cout << "The list is empty" << endl;
            return;
        }
        for (int i = 0; i < n; ++i) {
            cout << "List number: ";
            cout << i + 1 << " List info: ";
            lists[i].pecati();
        }
        cout << "Sum: " << sum() << " Average: " << average() << endl;
        cout << "Successful attempts: " << att << " Failed attempts: " << fail << endl;
    }

    ~ListContainer() {
        delete[] lists;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++) {
            cin >> niza[j];

        }

        List l = List(niza, n);

        lc.addNewList(l);
    }


    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1.sum();
        lc1.average();

    } else {
        lc.print();
    }
}