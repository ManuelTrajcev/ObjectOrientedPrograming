#include <stdio.h>

struct Laptop {
    char brand[100];
    float size;
    int touch;
    int price;
};
typedef struct Laptop Laptop;

void readLaptop(Laptop *laptop) {
    scanf("%s %f %d %d", laptop->brand, &laptop->size, &laptop->touch, &laptop->price);
}

void printLaptop(Laptop laptop) {
    printf("%s %g %d\n", laptop.brand, laptop.size, laptop.price);
}

struct ITStore {
    char name[100];
    char location[100];
    Laptop available[100];
    int n;
};
typedef struct ITStore ITStore;

void readITStore(ITStore *itStore) {
    scanf("%s %s %d\n", itStore->name, itStore->location, &itStore->n);
    for (int i = 0; i < itStore->n; ++i) {
        readLaptop(&itStore->available[i]);
    }
}

void printITStore(ITStore itStore) {
    printf("%s %s\n", itStore.name, itStore.location);
    for (int i = 0; i < itStore.n; ++i) {
        printLaptop(itStore.available[i]);
    }
}

void najeftina_ponuda(ITStore *s, int n) {
    int first = 1;
    int lowestPrice;
    ITStore lowest;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < s[i].n; ++j) {
            if (first) {
                if (s[i].available[j].touch) {
                    lowestPrice = s[i].available[j].price;
                    lowest = s[i];
                    first = 0;
                }
                continue;
            }
            if (s[i].available[j].touch && s[i].available[j].price < lowestPrice) {
                lowestPrice = s[i].available[j].price;
                lowest = s[i];
            }
        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n%s %s\n", lowest.name, lowest.location);
    printf("Najniskata cena iznesuva: %d", lowestPrice);
}

int main() {
    ITStore s[100];
    int n;
    scanf("%d", &n); //broj na IT prodavnici
    for (int i = 0; i < n; ++i) {
        readITStore(&s[i]);
        printITStore(s[i]);
    }
    najeftina_ponuda(s, n);
    return 0;
}