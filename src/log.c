#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "log.h"
#include "file.h"
#include "utilities.h"

static char msg_log[5000][255]; // const this value

static int msg_ctr = 0;

static char log_path[] = "log";
FILE *log_file;

static void insert_msg(char *message) {
    strcpy(msg_log[msg_ctr], message);
    fputs(msg_log[msg_ctr], log_file);
    msg_ctr++;
}

void log_msg(char *msg) {
    insert_msg(msg);
}

void init_log(int game_id) {
    char path_buf[30];
    char time_buf[30];
    snprintf(path_buf, 30, "log/%d", game_id);
    log_file = open_file(path_buf);
    get_timestamp(time_buf);
    log_msg(time_buf);
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