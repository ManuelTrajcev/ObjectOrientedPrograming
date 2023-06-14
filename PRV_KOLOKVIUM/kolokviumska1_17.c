#include<stdio.h>
#include<string.h>

typedef struct SkiLift {
    char ime[15];
    int max_skijaci;
    int voUpotreba;
} SkiLift;
typedef struct skiCenter {
    char ime[20];
    char drzava[20];
    SkiLift niza[20];
    int br_lifts;
} skiCenter;

void najgolemKapacitet(skiCenter *sc, int n) {
    int max = 0;
    int maxIndex = 0;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < sc[i].br_lifts; ++j) {
            if (sc[i].niza[j].voUpotreba)
                sum += sc[i].niza[j].max_skijaci;
        }
        if (sum > max) {
            max = sum;
            maxIndex = i;
        } else if (sum == max) {
            if (sc[i].br_lifts > sc[maxIndex].br_lifts) {
                max = sum;
                maxIndex = i;
            }
        }
    }
    printf("%s\n%s\n%d", sc[maxIndex].ime, sc[maxIndex].drzava, max);
}

int main() {
    int i, j, n, broj;
    skiCenter sc[20];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        //printf("Ime:");
        scanf("%s", sc[i].ime);
        //printf("\nDrzava:");
        scanf("%s", sc[i].drzava);
        scanf("%d", &sc[i].br_lifts);

        for (j = 0; j < sc[i].br_lifts; j++) {
            scanf("%s", sc[i].niza[j].ime);
            scanf("%d", &sc[i].niza[j].max_skijaci);
            scanf("%d", &sc[i].niza[j].voUpotreba);
        }
    }
    najgolemKapacitet(sc, n);

    return 0;
}
