#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <assert.h>
#include <editline/readline.h>
#include <editline/history.h>
#include "shell.h"
#include "s_list.h"
#include "dirs.h"
#include "dict.h"
#include "alias.h"

struct Dict* aliases = 0x0;

void freeCommand(struct command **ci){
  int i = 0;
  struct command c = *(*ci);
  free(c.command);
  while(1){
    if(c.argv[i] == 0x0){break;}
    free(c.argv[i]);
    i++;
  }
  free(c.argv);
  free(*ci);
  *ci = 0x0;
  return;
}

char** packageArgs(struct command *c){
  int i = 0, len;
  char **pack;
  while(1){
    if(c->argv[i] == 0x0){break;}
    i++;
  }
  len = i;
  pack = calloc(sizeof(char *), i+2);
  pack[0] = c->command;
  for(i=0;i<len;i++){
    pack[i+1] = c->argv[i];
  }
  return pack;
}

void execute(struct command *c){
  if(fork()){
    wait(0x0);
  }else{
    char** pack = packageArgs(c);
    execvp(c->command, pack);
    free(pack);
    printf("Unknown command\n");
    exit(0);
    fprintf(stderr, "Child process did not terminate!\n");
  }
  return;
}



int compArgC(struct command *c){
  int i = 0;
  while(1){
    if(c->argv[i] == 0x0){break;}
    i++;
  }
  return i;
}

void replaceVars(struct command *c){
  int i, len = compArgC(c);
  char *this, *varValue;
  for(i=0;i<len;i++){
    this = c->argv[i];
    if(this[0] == '$'){
      varValue = getenv(this+1);
      c->argv[i] = varValue;
    }
  }
  return;
}

int evaluateLine(struct command *c){
  char *command = c->command;
  replaceVars(c);
  if(0 == strcmp("", command)){
    return 1;
  }else if(0 == strcmp("exit", command)){
    return 0;
  }else if(0 == strcmp("cd", command)){
    cd(c);
    return 1;
  }else if(0 == strcmp("export", command)){
    if(c->argv[0] == 0x0 || c->argv[1] == 0x0){
      printf("Export usage: export {varName} {varVal}\n");
    }else{
      setenv(c->argv[0],c->argv[1],1);
    }
    return 1;
  }else if(0 == strcmp("alias", command)){
    struct Dict* temp = newAlias(c,aliases);
    if(0x0 == temp){
      printf("Alias: alias {shortcut} = {expanded}\n");
    }else{
      printf("New Alias ref:%s}\n", temp->first->ref);
      printf("New Alias def:%s}\n", temp->first->def);
      aliases = temp;
    }
    return 1;
  }else{
    execute(c);
    return 1;
  }
}

char* getLine(char* prompt){
  char *raw, *new;
  raw = readline(prompt);
  new = calloc(1,strlen(raw) + 2);
  strcpy(new,raw);
  new[strlen(raw)] = '\n';
  free(raw);
  return new;
}
    



int main(void){
  char *line;
  char cwd[256];
  char pBuf[256];
  char *mwd, *ac;
  struct command *c;
  int running = 1;
  char *home = getenv("HOME");

  //REPL
  while(running){
    getcwd(cwd,256);
    mwd = replaceHome(cwd, home);
    //printf("%s>", mwd);
    bzero(pBuf,256);
    sprintf(pBuf,"%s>",mwd);
    line = getLine(pBuf);
    free(mwd); mwd = 0x0;
    add_history(line);
    c = process(line);
    running = evaluateLine(c);
    free(line);
    freeCommand(&c);
  }
  printf("Exiting...\n");
  return 0;
  
}
