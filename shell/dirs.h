#ifndef DIRS_H
#define DIRS_H
#include "shell.h"

char* addHome(char* path);
char* addCWD(char* path);
char* expandPath(char* path);
void cd(struct command* c);
char* replaceHome(char* in, char* home);



#endif
