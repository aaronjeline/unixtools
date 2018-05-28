#ifndef DICT_H
#define DICT_H

struct Entry{
  char* ref;
  char* def;
};

struct Dict{
  struct Entry* first;
  struct Dict* rest;
};


struct Entry* buildEntry(char* ref, char* def);

void freeEntry(struct Entry** e);

struct Dict* consD(struct Entry* first, struct Dict* rest);

void freeDict(struct Dict** d);

struct Dict* insert(char* ref, char* value, struct Dict* dict);

struct Entry* lookup(char* ref, struct Dict* d);

  
#endif
