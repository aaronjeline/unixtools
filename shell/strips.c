#include <stdlib.h>
#include <string.h>


void stripFwd(char** c){
  int len, i;
  char *orig, *sp, *result = 0x0;
  orig = *c;
  sp = orig;
  len = strlen(orig);
  for(i=0;i<len;i++){
    if(' ' == orig[i]){
      sp++;
    }else{
      break;
    }
  }
  result = strdup(sp);
  free(orig);
  *c = result;
}

void stripBwd(char** c){
  int len, i;
  char *orig, *result = 0x0;
  orig = *c;
  len = strlen(orig) - 1;
  for(i=len;i>=0;i = i -1){
    if(' ' == orig[i]){
      orig[i] = '\0';
    }else{
      break;
    }
  }
  result = strdup(orig);
  free(orig);
  *c = result;
}


