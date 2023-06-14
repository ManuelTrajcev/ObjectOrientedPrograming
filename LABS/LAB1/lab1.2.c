#include <stdio.h>

typedef struct Transaction {
    int id;
    int sum;
    int commisision;
    int type;
} Transaction;

void check(int n, Transaction *transaction) {
    int flag = 1;
    for (int i = 0; i < n; ++i) {
        if (transaction[i].type) {
            printf("%d %d\n", transaction[i].id, transaction[i].sum + transaction[i].commisision);
            flag = 0;
        }
    }
    if(flag){
        printf("No credit card transcation");
    }
}

int main() {
    int n;
    Transaction transaction[100];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", &transaction[i].id, &transaction[i].sum, &transaction[i].commisision,
              &transaction[i].type);
    }
    check(n, transaction);
    return 0;
}