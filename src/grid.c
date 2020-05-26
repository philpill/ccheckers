#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// https://jrgraphix.net/r/Unicode/2500-257F

char a[] = "┌─┬┐";

char b[] = "│";

char c[] = "├─┼┤";

char d[] = "└─┴┘";

char e[] = "┏━┱┲┓┃┡┢┩┪┗┵┶┛╆╅╄╃";

void get_top_row(char row[], int cells, int vpad, int hpad) {
    // 1 cell for character
    // 1 cell for border
    // 2 * hpad per cell (either side)
    // 1 character for end border
    int length = cells + cells + (hpad * 2 * cells) + 1;
    char tmp[255];
    strncpy(tmp, &a[0], 3);
    strcat(row, tmp);
    for (int i = 0; i < cells - 1; i++) { 
        for (int j = 0; j < ((hpad * 2) + 1); j++) {
            strncpy(tmp, &a[3], 3);
            strcat(row, tmp);
        }
        strncpy(tmp, &a[6], 3);
        strcat(row, tmp);
    }
    for (int j = 0; j < ((hpad * 2) + 1); j++) {
        strncpy(tmp, &a[3], 3);
        strcat(row, tmp);
    }
    strncpy(tmp, &a[9], 3);
    strcat(row, tmp);
}

void get_spacer_row(char row[], int cells, int vpad, int hpad) {
    // 1 cell for character
    // 1 cell for border
    // 2 * hpad per cell (either side)
    // 1 character for end border
    int length = cells + cells + (hpad * 2 * cells) + 1;
    char tmp[255];
    strncpy(tmp, &b[0], 3);
    strcat(row, tmp);
    for (int i = 0; i < cells - 1; i++) { 
        for (int j = 0; j < ((hpad * 2) + 1); j++) {
            strcpy(tmp, " ");
            strcat(row, tmp);
        }
        strncpy(tmp, &b[0], 3);
        strcat(row, tmp);
    }
    for (int j = 0; j < ((hpad * 2) + 1); j++) {
        strcpy(tmp, " ");
        strcat(row, tmp);
    }
    strncpy(tmp, &b[0], 3);
    strcat(row, tmp);
}
