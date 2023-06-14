#include <stdio.h>
#include <string.h>
#include <ctype.h>


struct call {
    int day;
    int month;
    int year;
    int duration;
    char n1[10], n2[10];
};
typedef struct call call;

void readCall(call *c) {
    scanf("%d/%d/%d %s %s %d", &c->day, &c->month, &c->year, c->n1, c->n2, &c->duration);
}

void printCall(call c) {
    printf("%02d/%02d/%02d %s %s %d\n", c.day, c.month, c.year, c.n1, c.n2, c.duration);
}

void filterCalls() {

}

int main() {
    int n, total = 0;
    call calls[100];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        readCall(calls + i);
        if ((calls[i].year == 2019 || calls[i].year == 2020) || strcmp(calls->n1, "077250323") == 0) {
            printCall(calls[i]);
            total += calls[i].duration;
        }
    }
    printf("Total duration:%d", total);
    return 0;
}