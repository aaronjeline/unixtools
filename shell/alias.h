#ifndef ALIAS_H
#define ALIAS_H
#include "dict.h"
#include "shell.h"
char* procAlias(char* in, struct Dict* aliases);

struct Dict* newAlias(struct command* c, struct Dict* ca);



#endif
