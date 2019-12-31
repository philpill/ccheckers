#include <stdio.h>


FILE *files[255];
int file_count = 0;

void init_file() {

}

FILE *open_file(char path[]) {

    FILE *fp;
    fp  = fopen (path, "w+");

    files[file_count] = fp;
    file_count++;

    return fp;
}

void destroy_file() {
    for (int i = 0; i < file_count; i++) {
        fclose(files[i]);
    }
}