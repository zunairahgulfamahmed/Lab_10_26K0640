#include <stdio.h>
#include <string.h>
#define SIZE 39
#define RATE 8000.0

int main(void) {
    
    FILE *fp = fopen("hotel.txt", "wb");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }
    for (int r = 101; r <= 110; r++)
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", r, 'F', "-", 0, RATE);
    fclose(fp);

    fp = fopen("hotel.txt", "rb+");
    if (fp == NULL) { printf("Cannot open file\n"); return 1; }

    int choice, room, nights, rno, n, i, found;
    char status, name[21], guest[21];
    float rate;
    char guests[10][21];
    int rooms[10];

    while (1) {
        printf("\n1 Check-in   2 Search   3 Check-out   0 Exit: ");
        scanf("%d", &choice);
        if (choice == 0) break;

        if (choice == 1) {                       
            printf("Check-in room: ");
            scanf("%d", &room);
            printf("Name: ");
            scanf("%20s", guest);
            printf("Nights: ");
            scanf("%d", &nights);
            if (room < 101 || room > 110) { printf("Invalid room\n"); continue; }

            fseek(fp, (room - 101) * SIZE, SEEK_SET);
            fscanf(fp, "%d %c %s %d %f", &rno, &status, name, &n, &rate);
            if (status == 'F') {
                fseek(fp, (room - 101) * SIZE, SEEK_SET);
                fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'B', guest, nights, RATE);
                printf("Room %d booked\n", room);
            } else {
                printf("Room already booked\n");
            }
        }
        else if (choice == 2) {                 
            rewind(fp);
            for (i = 0; i < 10; i++)
                fscanf(fp, "%d %c %s %d %f", &rooms[i], &status, guests[i], &n, &rate);

            printf("Search name: ");
            scanf("%20s", guest);
            found = 0;
            for (i = 0; i < 10; i++) {
                if (strcmp(guests[i], guest) == 0) {
                    printf("%s is in room %d\n", guest, rooms[i]);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Guest not found\n");
        }
        else if (choice == 3) {                 
            printf("Check-out room: ");
            scanf("%d", &room);
            if (room < 101 || room > 110) { printf("Invalid room\n"); continue; }

            fseek(fp, (room - 101) * SIZE, SEEK_SET);
            fscanf(fp, "%d %c %s %d %f", &rno, &status, name, &n, &rate);
            if (status == 'B') {
                printf("Bill: %d x %.2f = %.2f\n", n, rate, n * rate);
                fseek(fp, (room - 101) * SIZE, SEEK_SET);
                fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'F', "-", 0, RATE);
            } else {
                printf("Room is already free\n");
            }
        }
    }

    fclose(fp);
    return 0;
}