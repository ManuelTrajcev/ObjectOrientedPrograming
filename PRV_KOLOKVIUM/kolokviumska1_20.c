#include<stdio.h>

typedef struct Pacient {
    char ime[50];
    int zdrastveno;
    int pregledi;
} Pacient;

typedef struct doktor {
    char ime[50];
    int br_pac;
    Pacient niza[50];
    float cena;
} doktor;

int pregledi(doktor doktor1) {
    int sum = 0;
    for (int j = 0; j < doktor1.br_pac; ++j) {
        if (doktor1.niza[j].zdrastveno == 0)
            sum += doktor1.niza[j].pregledi;
    }

    return sum;
}
int preglediVk(doktor doktor1) {
    int sum = 0;
    for (int j = 0; j < doktor1.br_pac; ++j) {
            sum += doktor1.niza[j].pregledi;
    }

    return sum;
}

void najuspesen_doktor(doktor *doktori, int n) {
    float max = 0;
    int maxIndex = 0;
    for (int i = 0; i < n; ++i) {
        float sum = 0;
        sum = pregledi(doktori[i]) * doktori[i].cena;
        if (sum > max) {
            max = sum;
            maxIndex = i;
        } else if (sum == max) {
            if (preglediVk(doktori[i]) > preglediVk(doktori[maxIndex])) {
                max = sum;
                maxIndex = i;
            }
        }
    }
    printf("%s %.2f %d", doktori[maxIndex].ime, max, preglediVk(doktori[maxIndex]));
}

int main() {
    int i, j, n, broj;
    doktor md[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        //ime na doktor
        scanf("%s", &md[i].ime);
        //broj na pacienti
        scanf("%d", &md[i].br_pac);
        //cena na pregled
        scanf("%f", &md[i].cena);

        for (j = 0; j < md[i].br_pac; j++) {
            scanf("%s", &md[i].niza[j].ime);
            scanf("%d", &md[i].niza[j].zdrastveno);
            scanf("%d", &md[i].niza[j].pregledi);
        }
    }
    najuspesen_doktor(md, n);

    return 0;
}
