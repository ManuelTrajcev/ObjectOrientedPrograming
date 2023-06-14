#include <stdio.h>
#include <string.h>

struct Vozenje {
    char name[100];
    int duration;
    float price;
    int discount;
};
typedef struct Vozenje Vozenje;

void readVozenje(Vozenje *ride) {
    scanf("%s %d %f %d", ride->name, &ride->duration, &ride->price, &ride->discount);
}

void printVozenje(Vozenje ride) {
    printf("%s %d %.2f", ride.name, ride.duration, ride.price);
}

struct ZabavenPark {
    char name[100];
    char location[100];
    Vozenje rides[100];
    int n;
};
typedef struct ZabavenPark ZabavenPark;

void readPark(ZabavenPark *park) {
    scanf("%s %s %d", park->name, park->location, &park->n);
}

void printdPark(ZabavenPark park) {
    printf("%s %s\n", park.name, park.location);
}

void NajdobarPark(ZabavenPark *parks, int n) {
    ZabavenPark best;
    int count = 0, maxCount = 0, time = 0, maxTime = 0;
    for (int i = 0; i < n; ++i) {
        count = 0;
        time = 0;
        for (int j = 0; j < parks[i].n; ++j) {
            if (parks[i].rides[j].discount) {
                count++;
            }
            time += parks[i].rides[j].duration;
        }
        if (count > maxCount) {
            maxCount = count;
            best = parks[i];
            if (time > maxTime) {
                maxTime = time;
            }
        } else if (count == maxCount) {
            if (time > maxTime) {
                maxCount = count;
                best = parks[i];
            }
        }
    }
    printf("Najdobar park: %s %s", best.name, best.location);
}

int main() {
    int i, j, n, broj;
    //kreiraj niza od maksimum 100 zabavni parkovi
    ZabavenPark ff[100];
    scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++) {
        readPark(&ff[i]);
        printdPark(ff[i]);
        for (j = 0; j < ff[i].n; j++) {
            readVozenje(&ff[i].rides[j]);
            printVozenje(ff[i].rides[j]);
            printf("\n");
        }
    }
    NajdobarPark(ff, n);
    return 0;
}
