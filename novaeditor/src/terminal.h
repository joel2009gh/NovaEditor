#ifndef TERMINAL_H
#define TERMINAL_H

#include "editor.h"
#include <termios.h>
#include <unistd.h>

void enableRawMode();
void disableRawMode();
void die(const char *s);

#endif

