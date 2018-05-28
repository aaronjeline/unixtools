#include <string.h>
#include <stdlib.h>
#include "dict.h"


struct Entry* buildEntry(char* ref, char* def){
  struct Entry* new = malloc(sizeof(struct Entry));
  new->ref = ref;
  new->def = def;
  return new;
}

void freeEntry(struct Entry** e){
  free((*e)->ref);
  free((*e)->def);
  free(*e);
  *e = 0x0;
}



struct Dict* consD(struct Entry* first, struct Dict* rest){
  struct Dict* new = malloc(sizeof(struct Dict));
  new->first = first;
  new->rest = rest;
  return new;
}

void freeDict(struct Dict** d){
  if(*d != 0x0){
    freeEntry(&(*d)->first);
    freeDict(&(*d)->rest);
    free(*d);
    *d = 0x0;
  }
}

struct Dict* insert(char* ref, char* value, struct Dict* dict){
  return consD(buildEntry(ref,value), dict);
}

struct Entry* lookup(char* ref, struct Dict* d){
  if(0x0 == d){
    return 0x0;
  }else if(strcmp(d->first->ref, ref) == 0){
    return d->first;
  }else{
    return lookup(ref, d->rest);
  }
}


    
