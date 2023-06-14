#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Skilift {
    char name[100];
    int maxUsers;
    int active;
};
typedef struct Skilift Skilift;
struct SkiCenter {
    char name[20];
    char country[20];
    Skilift skilifts[20];
    int countLifts;

};
typedef struct SkiCenter SkiCentre;

void readSkiLift(Skilift *lift) {
    scanf("%s %d %d", lift->name, &lift->maxUsers, &lift->active);
}

void readSkiCentre(SkiCentre *centre) {
    scanf("%s %s", centre->name, centre->country);
    scanf("%d", &centre->countLifts);
    for (int i = 0; i < centre->countLifts; ++i) {
        readSkiLift(centre->skilifts + i);
    }
}

int calculateCapacity(SkiCentre sc) {
    int sum = 0;
    for (int i = 0; i < sc.countLifts; ++i) {
        sum += sc.skilifts->maxUsers;
    }
}

void printSkiCentre(SkiCentre sc) {
    printf("%s\n%s\n%d\n", sc.name, sc.country, calculateCapacity(sc));
}




int cmpSkiCentre(SkiCentre s1, SkiCentre s2) {
    if (calculateCapacity(s1) > calculateCapacity(s2)) {
        return 1;
    } else if (calculateCapacity(s1) < calculateCapacity(s2)) {
        return -1;
    } else {
        if (s1.countLifts > s2.countLifts) {
            return 1;
        } else if (s1.countLifts > s2.countLifts) {
            return 1;
        } else {
            return 0;
        }

    }
}

void najgolemKapaciter(SkiCentre *sc, int n) {
    SkiCentre max = sc[0];
    for (int i = 1; i < n; ++i) {
        if (cmpSkiCentre(sc[i], max) > 0) {
            max = sc[i];
        }
    }
    printSkiCentre(max);
}

int main() {
    int n;
    scanf("%d", &n);
    SkiCentre centers[10];
    for (int i = 0; i < n; ++i) {
        readSkiCentre(&centers[i]);
    }
    return 0;
}