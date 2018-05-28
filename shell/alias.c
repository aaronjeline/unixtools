#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "alias.h"
#include "dict.h"
#include "strips.h"


char* procAlias(char* in, struct Dict* aliases){
  char* res = 0x0, *t;
  t = strdup(in);
  t[strlen(t)-1] = '\0'; //Knock off newline
  struct Entry* query = lookup(t, aliases);
  if(0x0 == query){ //Not an alias
    res = strdup(in);
  }else{
    res = calloc(1,strlen(query->def)+1);
    res[strlen(query->def)] = '\n';
  }
  free(t);
  return res;
}

int containsEq(char* c, int len){
  int i;
  for(i=0;i<len;i++){
    if('=' == c[i]){return 1;}
    i++;
  }
  return 0;
}
  
struct Entry* parse(char* c, int len){
  int eqP = 0, i = 0;
  struct Entry* new = malloc(sizeof(struct Entry));
  while(1){
    if('=' == c[i]){break;}
    eqP++;
    i++;
  }
  new->ref = calloc(1,eqP);
  strncpy(new->ref, c, eqP);
  new->def = calloc(1,len-eqP);
  strcpy(new->def, (c + eqP + 1));
  stripFwd(&(new->def));
  stripBwd(&(new->ref));

  return new;
}

struct Dict* newAlias(struct command* c, struct Dict* ca){
  int parts = 0, totalSize = 0, *sizes = 0x0, i=0;
  char* op = 0x0, *sp = 0x0;
  struct Entry* new = 0x0;
  struct Dict* toReturn = 0x0;
  while(1){
    if(c->argv[i] == 0x0){break;}
    parts++;
    i++;
  }
  sizes = malloc(sizeof(int) * parts);
  for(i=0;i<parts;i++){
    int n = strlen(c->argv[i]);
    sizes[i] = n;
    totalSize += n;
  }
  totalSize += parts;
  op = calloc(1,totalSize);
  sp = op;
  for(i=0;i<parts;i++){
    strcpy(sp, c->argv[i]);
    sp += sizes[i];
    *sp = ' ';
    sp++;
  }
  sp[totalSize-1] = '\0';
  if(!containsEq(op, totalSize)){
    goto CLEANUP;
  }
  new = parse(op, totalSize);
  toReturn = consD(new, ca);
 CLEANUP: 
  free(op);
  free(sizes);
  return toReturn;
}
      
      
