#include <iostream>
#include <cstring>

using namespace std;

class Pecivo{
protected:
    char testo[50];
public:

};

class Pica: public Pecivo{
private:
    char forma[50];
    char toppings[50];

public:

};

class Burek : public Pecivo{
private:
    bool yogurt;
public:

};
class Kifla: public Pecivo{
private:

public:

};



int main(){
    int type, n;
    int i =0, j =0, k = 0;
    cin>>n;
    Pica poca[n];
    Burek burek[n];
    Kifla kifla[n];


    return 0;
}