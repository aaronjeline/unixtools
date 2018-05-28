#ifndef SHELL_H
#define SHELL_H

struct command{
  char* command;
  char** argv;
};

void freeCommand(struct command** c);

int compArgC(struct command* c);


#endif
