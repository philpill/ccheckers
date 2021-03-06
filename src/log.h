#ifndef LOG_H
#define LOG_H

void init_log(int game_id);
void log_msg(char *message);
void log_fmsg(char *message, int num, ...);
char *get_last_log_entry();
int get_log_count();
char **get_logs(char **logs, size_t size);
void clear_log();

#endif
