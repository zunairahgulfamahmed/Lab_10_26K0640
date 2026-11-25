#include <stdio.h>
#define SIZE 17

int main(void) {
    FILE *fp = fopen("temperature.txt", "wb");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    char city[11];
    float temp;
    for (int i = 0; i < 5; i++) {
        printf("City %d (name temperature): ", i + 1);
        scanf("%10s %f", city, &temp);
        fprintf(fp, "%-10s %5.1f\n", city, temp);
    }
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    int n;

    
    printf("City number: ");
    scanf("%d", &n);
    fseek(fp, (n - 1) * SIZE, SEEK_SET);
    fscanf(fp, "%s %f", city, &temp);
    printf("%s %.1f\n", city, temp);

    
    printf("City number to correct: ");
    scanf("%d", &n);
    printf("New temperature: ");
    scanf("%f", &temp);
    fseek(fp, (n - 1) * SIZE, SEEK_SET);
    fscanf(fp, "%s %*f", city);               
    fseek(fp, (n - 1) * SIZE, SEEK_SET);
    fprintf(fp, "%-10s %5.1f\n", city, temp);
    printf("%s updated to %.1f\n", city, temp);

    
    char hotName[11] = "";
    float hotTemp = -1000;
    rewind(fp);
    while (fscanf(fp, "%s %f", city, &temp) == 2) {
        if (temp > hotTemp) {
            hotTemp = temp;
            snprintf(hotName, sizeof hotName, "%s", city);
        }
    }
    printf("Hottest city: %s (%.1f)\n", hotName, hotTemp);

    fclose(fp);
    return 0;
}