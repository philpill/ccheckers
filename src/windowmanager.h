#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <stdbool.h>

WINDOW *get_windows(WINDOW **windows);

void delete_windows(WINDOW **windows);

void delete_window(WINDOW *windows);

#endif
