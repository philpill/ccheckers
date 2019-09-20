#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "log.h"


char msg_log[5000][255];

int msg_ctr = 0;
int char_ctr = 0;

char input_buffer;

void insert_char(char ch) {
    msg_log[msg_ctr][char_ctr] = ch;
    char_ctr++;
}

void insert_msg(char *message) {
    strcpy(msg_log[msg_ctr], message);
    msg_ctr++;
    char_ctr = 0;
}

void log_msg(char *msg, int num, ...) {
    va_list valist;
    char buffer[256];
    va_start(valist, num);
    vsprintf(buffer, msg, valist);
    insert_msg(buffer);
    va_end(valist);
}

void delete_char() {
    char_ctr = char_ctr < 1 ? 0 : char_ctr - 1;
    msg_log[msg_ctr][char_ctr] = '\0';
}

char* get_last_msg() {
    return msg_log[msg_ctr-1];
}
