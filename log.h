#ifndef LOG_H
#define LOG_H

void log_msg(char *message);
void log_fmsg(char *message, int num, ...);
char *get_log(int index);
int get_log_count();

#endif
