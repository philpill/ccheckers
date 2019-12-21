#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "log.h"

static char msg_log[5000][255]; // const this value

static int msg_ctr = 0;

static void insert_msg(char *message) {
    strcpy(msg_log[msg_ctr], message);
    msg_ctr++;
}

void log_msg(char *msg) {

    insert_msg(msg);

    // do something with all these logs
}

void log_fmsg(char *msg, int num, ...) {
    va_list valist;
    char buffer[256];

    if (num == 0) {
        log_msg(msg);
    } else {
        va_start(valist, num);
        vsprintf(buffer, msg, valist);
        insert_msg(buffer);
        va_end(valist);
    }

    // do something with all these logs
}

static char *get_log_entry(int index) {
    char *msg = NULL;
    if (index <= msg_ctr) {
        msg = msg_log[index];
    }
    return msg;
}

int get_log_count() {
    return msg_ctr + 1;
}

char *get_last_log_entry() {
    return get_log_entry(msg_ctr-1);
}

char **get_logs(char *logs[], size_t size) {
    for (int i = 0; i < size; i++) {
        logs[i] = msg_log[i];
    }
}