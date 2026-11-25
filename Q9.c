#include <stdio.h>


int markZone(char map[][5], int r, int c, char label) {
    if (r < 0 || r >= 5 || c < 0 || c >= 5) return 0;   
    if (map[r][c] != '*') return 0;                     
    map[r][c] = label;                                   
    return 1 + markZone(map, r - 1, c, label)           
             + markZone(map, r + 1, c, label)
             + markZone(map, r, c - 1, label)            
             + markZone(map, r, c + 1, label);           
}

int main(void) {
    float temp[5][5] = {
        { 2.1f, -1.5f, -2.0f,  3.0f,  4.2f},
        { 1.8f, -0.5f,  2.5f,  3.1f, -1.0f},
        { 3.3f,  2.0f,  1.5f, -0.8f, -2.0f},   
        {-1.2f,  3.4f,  4.0f,  3.8f, -0.6f},
        {-2.5f, -3.1f,  5.1f,  6.0f,  4.7f}
    };
    char map[5][5];

    for (int r = 0; r < 5; r++)
        for (int c = 0; c < 5; c++)
            map[r][c] = (temp[r][c] < 0) ? '*' : '.';

    char label = 'A';
    int zones = 0;
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (map[r][c] == '*') {
                int size = markZone(map, r, c, label);
                printf("Zone %c: %d stations\n", label, size);
                label++;
                zones++;
            }
        }
    }
    printf("Total zones: %d\n\n", zones);

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) printf("%c  ", map[r][c]);
        printf("\n");
    }
    return 0;
}