#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"

/**
 * Open file and read Piece data
 *
 * @param map array of 32 int to populate
 */
void load_file(char *filename, int map[8][8]) {

    FILE *file;

    char path[255] = "resources/";

    strcat(path, filename);

    strcat(path, ".txt");

    file = fopen(path, "r");
    if (file) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                fscanf(file,"%1d", &map[i][j]);
            }
        }
        fclose(file);
    }
}