#include <stdio.h>
#define SIZE 24

int main(void) {
    FILE *fp = fopen("attendance.txt", "wb");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    char *names[] = {"Ayesha", "Bilal", "Hamza", "Sana", "Zainab"};
    int att[] = {18, 14, 20, 12, 16};
    for (int i = 0; i < 5; i++)
        fprintf(fp, "%-3d %-15s %3d\n", i + 1, names[i], att[i]);
    fclose(fp);

    fp = fopen("attendance.txt", "rb+");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    int roll, id, lectures, leave;
    char name[16];
    float percent;

    
    printf("Roll number: ");
    scanf("%d", &roll);
    fseek(fp, (roll - 1) * SIZE, SEEK_SET);
    fscanf(fp, "%d %s %d", &id, name, &lectures);
    percent = lectures / 20.0 * 100;
    printf("%s: %d / 20 (%.1f%%)", name, lectures, percent);
    if (percent < 75) printf(" Short attendance");
    printf("\n");


    printf("Roll number for leave: ");
    scanf("%d", &roll);
    printf("Lectures: ");
    scanf("%d", &leave);
    fseek(fp, (roll - 1) * SIZE, SEEK_SET);
    fscanf(fp, "%d %s %d", &id, name, &lectures);
    lectures += leave;
    fseek(fp, (roll - 1) * SIZE, SEEK_SET);
    fprintf(fp, "%-3d %-15s %3d\n", id, name, lectures);
    printf("%s: now %d / 20 (%.1f%%)\n", name, lectures, lectures / 20.0 * 100);

    
    fseek(fp, -SIZE, SEEK_END);
    fscanf(fp, "%d %s %d", &id, name, &lectures);
    printf("Last record: %d %s %d\n", id, name, lectures);

    fclose(fp);
    return 0;
}