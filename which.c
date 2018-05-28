#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct path{
  char** paths;
  int length;
};

void freePath(struct path p){
  int i;
  for(i=0; i<p.length;i++){
    free(p.paths[i]);
  }
  free(p.paths);
  return;
}

int compLength(char* raw){
  int i, ans = 0, len = strlen(raw);
  for(i=0;i<len;i++){
    switch(raw[i]){
    case ':': ans++;break;
    default: break;
    }
  }
  return ++ans;
}

struct path parsePath(char* raw){
  int i,pp = 0;
  char* ref;
  struct path res;

  res.length = compLength(raw);
  res.paths = malloc(sizeof(char*) * res.length);
  ref = raw;

  for(i = 0; i<strlen(raw); i++){
    switch(raw[i]){
    case ':':
      res.paths[pp] = calloc(1, 1 + ((raw + i) - ref));
      strncpy(res.paths[pp], ref+1, ((raw + i) - ref) - 1);
      pp++;
      ref = raw + i;
      break;
    default: break;
    }
  }
  //Copy  the last string
  res.paths[pp] = calloc(1, 1 + ((raw + i) - ref));
  strncpy(res.paths[pp], ref+1, ((raw + i) - ref) - 1);

  return res;
}
  


int main(int argc, char** argv){
  int i;
  struct path p;
  char* path = getenv("PATH");
  if(argc != 1){
    return 1;
  }
  
}
