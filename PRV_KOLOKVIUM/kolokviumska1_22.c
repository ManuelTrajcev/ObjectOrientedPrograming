#include <stdio.h>
#include <string.h>

//место за вашиот код


struct Proizvod {
    char kod[20];
    int cena;
    int dostapni;
};
typedef struct Proizvod Proizvod;

typedef struct Narachka {
    char name[20];
    Proizvod niza[10];
    int n;
    int brProizvodi[10];
    int num;
} Narachka;

void pecatiFaktura(Narachka n) {
    printf("Faktura za %s\n", n.name);
    for (int i = 0; i < n.n; ++i) {
        if (n.brProizvodi[i] > n.niza[i].dostapni) {
            printf("Fakturata ne moze da se izgotvi");
            return;
        }
    }
    for (int i = 0; i < n.n; ++i) {
        for (int j = i; j < n.n - 1 - i; ++j) {
            if (strcmp(n.niza[j].kod, n.niza[j + 1].kod) > 0) {
                Proizvod tmp;
                tmp = n.niza[j];
                n.niza[j] = n.niza[j + 1];
                n.niza[j + 1] = tmp;
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < n.n; ++i) {
        printf("%s %d %d %d\n", n.niza[i].kod, n.niza[i].cena, n.brProizvodi[i], n.niza[i].cena * n.brProizvodi[i]);
        n.niza[i].dostapni -= n.brProizvodi[i];
        sum += (n.niza[i].cena * n.brProizvodi[i]);
    }
    printf("Vkupnata suma na fakturata e %d", sum);
}

int main() {

    Narachka narachka;
    scanf("%s %d", narachka.name, &narachka.n);
    // внеси го името лицето кое ја прави нарачката
    // внеси го бројот на порачани производи во нарачката

    int i;
    //за секој од нарачаните производи се внесуваат информации
    for (i = 0; i < narachka.n; ++i) {
        scanf("%s %d %d\n", narachka.niza[i].kod, &narachka.niza[i].cena, &narachka.niza[i].dostapni);// внеси код
//        scanf("%d", &narachka.niza[i].cena);// внеси единицчна цена
//        scanf("%d", &narachka.niza[i].dostapni);// внеси број на производи во магацин
    }
    //за секој производ се внесува колку такви производи се порачани во нарачката
    int j;
    for (j = 0; j < narachka.n; ++j) {
        //се внесува број на производи во нарачката
        scanf("%d", &narachka.brProizvodi[j]);

    }


    pecatiFaktura(narachka);


    return 0;
}