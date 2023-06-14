#include <stdio.h>

struct Gragjanin {
    char ime[20];
    char prezime[20];
    int embg;
};
typedef struct Gragjanin Gragjanin;

void readGragjanin(Gragjanin *gragjanin) {
    scanf("%s %s %d", gragjanin->ime, gragjanin->prezime, &gragjanin->embg);
}
void printGragjanin(Gragjanin gragjanin){
    printf("%s %s %d ", gragjanin.ime, gragjanin.prezime, gragjanin.embg);
}

struct Grad {
    char ime[20];
    int ziteli;
};
typedef struct Grad Grad;

void readGrad(Grad *grad) {
    scanf("%s %d", grad->ime, &grad->ziteli);
}
void printGrad(Grad grad) {
    printf("%s %d ", grad.ime, grad.ziteli);
}

struct Pretsedatel {
    Gragjanin pretsedatel;
    char partija[20];
};
typedef struct Pretsedatel Pretsedatel;

void readPretsedatel(Pretsedatel *pretsedatel) {
    readGragjanin(&pretsedatel->pretsedatel);
    scanf("%s", pretsedatel->partija);
}
void printPretsedatel(Pretsedatel pretsedatel) {
    printGragjanin(pretsedatel.pretsedatel);
    printf("%s ", pretsedatel.partija);
}

struct Drzava {
    char name[20];
    Pretsedatel pretsedatel;
    Grad glavenGrad;
    int ziteli;
};
typedef struct Drzava Drzava;

void readDrzava(Drzava *drzava) {
    scanf("%s", drzava->name);
    readPretsedatel(&drzava->pretsedatel);
    readGrad(&drzava->glavenGrad);
}
void printDrzava(Drzava drzava) {
    printf("%s ", drzava.name);
    printPretsedatel(drzava.pretsedatel);
    printGrad(drzava.glavenGrad);
}
void printLargest(Drzava *drzava, int n){
    Drzava max = drzava[0];
    for (int i = 1; i < n; ++i) {
        if(drzava[i].glavenGrad.ziteli > max.glavenGrad.ziteli){
            max = drzava[i];
        }
    }
    printDrzava(max);
}

int main() {
    int n;
    Drzava drzavi[100];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        readDrzava(drzavi + i);
    }
    printLargest(drzavi,n);
    return 0;
}