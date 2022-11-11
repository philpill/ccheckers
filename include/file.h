#ifndef FILE_H
#define FILE_H

void init_file();
FILE *open_file(char path[], char mode[]);
void destroy_file();

#endif