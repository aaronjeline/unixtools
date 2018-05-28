#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "s_list.h"


struct cell* cons(char* first, struct cell* rest){
  struct cell* new = malloc(sizeof(struct cell));
  new->first = first;
  new->rest = rest;
  return new;
}

void freeLL(struct cell* c){
  struct cell* t;
  int done = 0;
  while(!done){
    t = c;
    done = c->rest == 0x0 ? 1 : 0;
    c = c->rest;
    free(t);
  }
  return;
}

struct cell* split(char* line){
  char* ref = line;
  int i, len = strlen(line);
  char *s;
  struct cell *list = 0x0, *result = 0x0;
  for(i=0;i<len;i++){
    switch(line[i]){
    case ' ':
      s = calloc(1, ((i + line) - ref) + 1);
      strncpy(s, ref, ((i + line) - ref));
      list = cons(s, list);
      ref = (line + i + 1);
      break;
    default: break;
    }
  }
  s = calloc(1, ((i + line) - ref) + 1);
  strncpy(s, ref, ((i + line) - ref));
  s[strlen(s)-1] = '\0'; // Null out the newline
  list = cons(s, list);
  result = reverse(list);
  freeLL(list);
  return result;
}

struct cell* reverse(struct cell* l){
  return reverseA(l, 0x0);
}

struct cell* reverseA(struct cell* l, struct cell *sofar){
  return l->rest == 0x0 ?
    cons(l->first, sofar) 
    : reverseA(l->rest, cons(l->first, sofar));
}
    
int length(struct cell* l){
  return l->rest == 0x0 ? 1 : 1 + length(l->rest);
}

struct command* fillCommand(struct cell* l){
  int len, i;
  struct command* cmd = malloc(sizeof(struct command));
  len = length(l);
  cmd->command = l->first;
  l = l->rest;
  cmd->argv = malloc(sizeof(char*) * len);
  for(i=1;i<len;i++){
    cmd->argv[i-1] = l->first;
    l = l->rest;
  }
  cmd->argv[i-1] = 0x0;
  return cmd;
}

void printCommand(struct command* c){
  int i = 0;
  printf("Command: %s\nArgs: ", c->command);
  while(1){
    if(c->argv[i] == 0x0){
      break;
    }
    printf("%s ", c->argv[i]);
    i++;
  }
  printf("\n");
  return;
}
  

void printLL(struct cell *l){
  int done = 0;
  while(!done){
    printf("%s ", l->first);
    done = l->rest == 0x0 ? 1 : 0;
    l = l->rest;
  }
  printf("\n");
}

struct command* process(char* line){
  struct cell* sp = split(line);
  struct command* res = fillCommand(sp);
  freeLL(sp);
  return res;
}


// Tests
/*
int main(void){
  char* in = "cat somefile.txt";
  struct command *c;
  struct cell *list = split(in);
  printLL(list);
  c = fillCommand(list);
  printCommand(c);
  freeLL(list);
  return 0;
}
*/ 
