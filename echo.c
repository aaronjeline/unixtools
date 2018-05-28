#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char** argv){
  int i,size=0;
  char* final, * ref;
  for(i=1;i<argc;i++){
    size += strlen(argv[i]);
  }
  final = calloc(1, size+1+argc-1);
  ref = final;
  for(i=1;i<argc;i++){
    char next[strlen(argv[i])+1];
    sprintf(next, "%s ", argv[i]);
    strcpy(ref,next);
    ref += strlen(next);
  }
  if(strlen(final) > 0){
    //Nock out the final space
    final[strlen(final)-1] = 0x0;
    printf("%s", final);
  }
  printf("\n");
  free(final);
  return 0;
}
