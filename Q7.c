#include <stdio.h>


int finalBalance(int trans[], int n, int balance) {
    if (n == 0) return balance;
    return finalBalance(trans, n - 1, balance + trans[n - 1]);
}


int totalDeposits(int trans[], int n) {
    if (n == 0) return 0;
    int mine = (trans[n - 1] > 0) ? trans[n - 1] : 0;
    return mine + totalDeposits(trans, n - 1);
}


int copyLarge(int trans[], int i, int n, int large[], int k) {
    if (i == n) return k;
    if (trans[i] <= -10000) {
        large[k] = trans[i];
        return copyLarge(trans, i + 1, n, large, k + 1);
    }
    return copyLarge(trans, i + 1, n, large, k);
}

int main(void) {
    int balance = 20000;
    int trans[7] = {20000, -5000, -12000, 8000, -25000, -2500, 15000};
    int large[7];

    printf("Final balance: %d\n", finalBalance(trans, 7, balance));
    printf("Total deposits: %d\n", totalDeposits(trans, 7));

    int count = copyLarge(trans, 0, 7, large, 0);
    printf("Large withdrawals (%d):", count);
    for (int i = 0; i < count; i++) printf(" %d", large[i]);
    printf("\n");
    return 0;
}