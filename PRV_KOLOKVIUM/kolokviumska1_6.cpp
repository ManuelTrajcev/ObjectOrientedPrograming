#include<iostream>
#include <cstring>

using namespace std;

struct Voz {
    char relation[50];
    float km;
    int passengers;
};

struct ZeleznickaStanica {
    char city[20];
    Voz vozovi[30];
    int n;
};


void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad) {
    int minIndex = 0;
    int index = 0;
    for (int i = 0; i < n; ++i) {
        if (strstr(grad, zs[i].city)) {
            float min = zs[i].vozovi[0].km;
            index = i;
            minIndex = 0;
            for (int j = 0; j < zs->n; ++j) {
                if (zs[i].vozovi[j].km <= min) {
                    min = zs[i].vozovi[j].km;
                    minIndex = j;
                }
            }
        }
    }
    cout << "Najkratka relacija: " << zs[index].vozovi[minIndex].relation << " (" << zs[index].vozovi[minIndex].km
         << " km)";
}

int main() {

    int n;
    cin >> n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i = 0; i < n; i++) {
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        cin >> zStanica[i].city >> zStanica[i].n;
        for (int j = 0; j < zStanica[i].n; ++j) {
            cin >> zStanica[i].vozovi[j].relation >> zStanica[i].vozovi[j].km >> zStanica[i].vozovi[j].passengers;
        }
    }

    char grad[25];
    cin >> grad;

    najkratkaRelacija(zStanica, n, grad);
    return 0;
}
