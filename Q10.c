#include <stdio.h>
#include <string.h>


int countRepeat(char s[], int i) {
    if (s[i + 1] == s[i]) return 1 + countRepeat(s, i + 1);
    return 1;
}


void compress(char s[], int i, char out[], int j) {
    if (s[i] == '\0') { out[j] = '\0'; return; }
    int cnt = countRepeat(s, i);
    out[j] = s[i];
    out[j + 1] = '0' + cnt;                   
    compress(s, i + cnt, out, j + 2);         
}


void expand(char in[], int i, char out[], int j) {
    if (in[i] == '\0') { out[j] = '\0'; return; }
    int cnt = in[i + 1] - '0';                
    for (int k = 0; k < cnt; k++) out[j + k] = in[i];
    expand(in, i + 2, out, j + cnt);
}

int main(void) {
    char original[] = "AAAAAABBBCCCCD";
    char compressed[50], expanded[50];

    compress(original, 0, compressed, 0);
    expand(compressed, 0, expanded, 0);

    printf("Original:   %s\n", original);
    printf("Compressed: %s\n", compressed);
    printf("Expanded:   %s\n", expanded);
    printf("Match: %s\n", strcmp(original, expanded) == 0 ? "Yes" : "No");
    return 0;
}