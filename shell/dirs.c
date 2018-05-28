#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dirs.h"
#include "shell.h"


char* addHome(char* path){
  char *home;
  char *result;
  home = getenv("HOME");
  result = calloc(1, strlen(home) + strlen(path));
  strcpy(result, home);
  strcpy(result + strlen(home), path + 1);
  return result;
}

char* addCWD(char* path){
  char cwd[256];
  char *result;
  getcwd(cwd, 256);
  result = calloc(1, strlen(path) + strlen(cwd)+2);
  strcpy(result, cwd);
  result[strlen(cwd)] = '/';
  strcpy(result + strlen(cwd)+1, path);
  return result;
}
  

char* expandPath(char* path){
  char *result;
  switch(path[0]){
  case '/': result = calloc(1,strlen(path)); strcpy(result,path);break;
  case '~': result = addHome(path);break;
  default: result = addCWD(path);break;
  }
  return result;
}
    

void cd(struct command *c){
  if(c->argv[0] == 0x0){
    chdir(getenv("HOME"));
  }else{
    char* toC = expandPath(c->argv[0]);
    switch(chdir(toC)){
    case -1: printf("Couldn't switch to %s\n",c->argv[0]);
    default:break;
    }
    free(toC);
    
  }
  return;
}

char* replaceHome(char* in, char* home){
  char* new;
  if(strncmp(in,home,strlen(home)) == 0){
    new = calloc(1, strlen(in) - strlen(home) + 2);
    new[0] = '~';
    strcpy(new+1,in+strlen(home));
  }else{
    new = calloc(1, strlen(in)+1);
    strcpy(new, in);
  }
  return new;
}
