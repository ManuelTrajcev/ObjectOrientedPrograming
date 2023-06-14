#include <iostream>

using namespace std;

struct Igrac{
    char name[15];
    int lvl;
    int points;
};
void readIgrac(Igrac igrac){
    cin>>igrac.name>>igrac.lvl>>igrac.points;
}
void printIgrac(Igrac &igrac){
    cout<<igrac.name<<igrac.lvl<<igrac.points;
}

struct KompjuterskaIgra{
    char name[20];
    Igrac players[30];
    int n;
};

void readIgra(KompjuterskaIgra &igra){
    cin>>igra.name>>igra.n;
    for (int i = 0; i < igra.n; ++i) {
        readIgrac(igra.players[i]);
    }
}
void printIgra(KompjuterskaIgra igra){
    cout<<igra.name<<igra.n<<endl;
    for (int i = 0; i < igra.n; ++i) {
        printIgrac(igra.players[i]);
        cout<<endl;
    }
}

//void najdobarIgrac(KompjuterskaIgra *lista, int n){
//
//}
int main(){
    int n;
    cin>>n;
    KompjuterskaIgra igri[100];
    for (int i = 0; i < n; ++i) {
        readIgra(igri[i]);
        printIgra(igri[i]);
    }
    return 0;
}