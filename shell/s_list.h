#ifndef S_LIST_H
#define S_LIST_H
#include "shell.h"


struct cell{
  char *first;
  struct cell* rest;
};


struct cell* cons(char* first, struct cell* rest); //Done

void freeLL(struct cell* c); //Done

struct cell* split(char* line);

struct cell* reverse(struct cell* l);

struct cell* reverseA(struct cell* l, struct cell* sofar);

int length(struct cell* l);

struct command* fillCommand(struct cell* l);

void printCommand(struct command* c);

struct command* process(char* line);

#endif
