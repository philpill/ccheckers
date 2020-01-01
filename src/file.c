#include <stdio.h>
#include <stdlib.h>

static FILE *files[255];
static int file_count = 0;

void init_file() {

}

/*
 * Open file at given path and store struct
 * in array for closing later
 * 
 * @param  path string of path to file open
 * @param  mode File mode to open file
 * @return FILE struct 
 */
FILE *open_file(char path[], char mode[]) {

    FILE *fp;
    fp  = fopen (path, mode);

    if (fp == NULL) {
        printf("Could not open file:  %s", path);   
        exit(1);             
    }

    files[file_count] = fp;
    file_count++;

    return fp;
}

/*
 * Close all previously open files
 */
void destroy_file() {
    for (int i = 0; i < file_count; i++) {
        fclose(files[i]);
    }
}