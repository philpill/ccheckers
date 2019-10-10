#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

/**
 * Open file and read Piece data
 *
 * @param map array of 32 int to populate
 */
void load_file(int map[8][4]) {

    FILE *file;

    file = fopen("resources/1.txt", "r");
    if (file) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                fscanf(file,"%1d", &map[i][j]);
            }
        }
        fclose(file);
    }
}