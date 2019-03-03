#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"
#include "file.h"

/**
 * Open file and read Piece data
 *
 * @param map array of 32 int to populate
 */
void load_file(char *filename, int map[8][8]) {

    FILE *file;

    char path[255] = "res/";

    strcat(path, filename);

    strcat(path, ".txt");

    file = open_file(path, "r");

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fscanf(file,"%1d", &map[i][j]);
        }
    }
}