#include <stdio.h>
#include <string.h>

#define NEDELI 4
#define DENOVI 5

typedef struct RabotnaNedela {
    int casovi[5];
    int n;
} RabotnaNedela;

typedef struct RabotnaNedela RN;

typedef struct Rabotnik {
    char ime[50];
    RabotnaNedela nedeli[4];
} Rabotnik;

typedef struct Rabotnik R;

int maxNedela(Rabotnik *r) {
    int max = 0;
    int maxIndex = 0;
    for (int i = 1; i < NEDELI; ++i) {
        int sum = 0;
        for (int j = 0; j < 5; ++j) {
            sum += r->nedeli[i].casovi[j];
        }
        if (sum > max) {
            max = sum;
            maxIndex = i;
        }
    }
    return maxIndex + 1;
}

int sumHours(Rabotnik r, int n) {
    int sum = 0;
    for (int j = 0; j < DENOVI; ++j) {
        sum += r.nedeli[n - 1].casovi[j];
    }
    return sum;
}

void table(Rabotnik *r, int n) {
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for (int i = 0; i < n; ++i) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", r[i].ime, sumHours(r[i], 1), sumHours(r[i], 2), sumHours(r[i], 3),
               sumHours(r[i], 4),
               sumHours(r[i], 1) + sumHours(r[i], 2) + sumHours(r[i], 3) + sumHours(r[i], 4));
    }
}


int main() {
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}
