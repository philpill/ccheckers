#ifndef LOG_H
#define LOG_H

void   log_init(int game_id);
void   log_msg(char *message);
void   log_fmsg(char *message, int num, ...);
char*  log_get_last_entry();
int    log_get_count();
char** log_get_all(char **logs, size_t size);
void   log_clear();

#endif
