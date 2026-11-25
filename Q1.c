#include <stdio.h>
#define SIZE 42

int main(void) {
    FILE *fp = fopen("items.txt", "wb");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    char *names[] = {"Rice","Sugar","Milk","CookingOil","Tea"};
    float prices[] = {250, 160, 220, 560, 450};
    int stocks[] = {40, 25, 30, 12, 18};
    for (int i = 0; i < 5; i++)
        fprintf(fp, "%-4d %-20s %9.2f %5d\n", i+1, names[i], prices[i], stocks[i]);
    fclose(fp);

    fp = fopen("items.txt", "rb+");
    int no, qty, id, stock;
    char name[21];
    float price, total = 0;

    while (1) {
        printf("Item no: ");
        scanf("%d", &no);
        if (no == 0) break;
        printf("Quantity: ");
        scanf("%d", &qty);

        fseek(fp, (no-1)*SIZE, SEEK_SET);
        fscanf(fp, "%d %s %f %d", &id, name, &price, &stock);

        if (qty <= stock) {
            printf("%s %d x %.2f = %.2f\n", name, qty, price, qty*price);
            total += qty * price;
            stock -= qty;
            fseek(fp, (no-1)*SIZE, SEEK_SET);
            fprintf(fp, "%-4d %-20s %9.2f %5d\n", id, name, price, stock);
        } else {
            printf("Only %d %s in stock\n", stock, name);
        }
    }
    printf("Total bill: %.2f\n", total);
    fclose(fp);
    return 0;
}