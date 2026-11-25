#include <stdio.h>
#define SIZE 23

int main(void) {
    
    FILE *fp = fopen("expenses.txt", "wb");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }
    fprintf(fp, "%-12s %9.2f\n", "Food", 1200.0);
    fprintf(fp, "%-12s %9.2f\n", "Transport", 500.0);
    fprintf(fp, "%-12s %9.2f\n", "Books", 850.0);
    fprintf(fp, "%-12s %9.2f\n", "Mobile", 300.0);
    fclose(fp);

    char cat[13], cat2[13];
    float amount, amount2, total = 0;
    int n;

    
    printf("Category: ");
    scanf("%12s", cat);
    printf("Amount: ");
    scanf("%f", &amount);
    fp = fopen("expenses.txt", "ab");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }
    fprintf(fp, "%-12s %9.2f\n", cat, amount);
    fclose(fp);

    
    fp = fopen("expenses.txt", "rb+");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }
    fseek(fp, -2 * SIZE, SEEK_END);
    fscanf(fp, "%s %f", cat, &amount);
    fscanf(fp, "%s %f", cat2, &amount2);
    printf("Latest two: %s %.2f, %s %.2f\n", cat, amount, cat2, amount2);

    
    printf("Entry to fix: ");
    scanf("%d", &n);
    printf("Correct amount: ");
    scanf("%f", &amount);
    fseek(fp, (n - 1) * SIZE, SEEK_SET);
    fscanf(fp, "%s %*f", cat);
    fseek(fp, (n - 1) * SIZE, SEEK_SET);
    fprintf(fp, "%-12s %9.2f\n", cat, amount);

    
    rewind(fp);
    while (fscanf(fp, "%s %f", cat, &amount) == 2) {
        printf("%s %.2f\n", cat, amount);
        total += amount;
    }
    printf("Total: %.2f\n", total);

    fclose(fp);
    return 0;
}