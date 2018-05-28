#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tarHeader.h"

void printCreateMessage(struct header h, char* target){
  int i;
  printf("Creating Archive %s containing files: ", target);
  for(i=0;i<h.fileNum;i++){
    printf("%s ", h.fileNames[i]);
  }
  printf("\n");
}

int create(char *target, char** fileNames, int num){
  int status, i;
  FILE* output = 0x0;
  struct header *h = buildHeader(fileNames,num);
  if(0x0 == h){
    fprintf(stderr, "Couldn't open input files for reading\n");
    status = 1;
    goto CLEANUP;
  }
  output = fopen(target, "w");
  if(0x0 == output){
    fprintf(stderr, "Could open %s for writing\n", target);
    status = 1;
    goto CLEANUP;
  }

  printCreateMessage(*h, target);
  fwrite("TAR",1,3,output);
  fwrite(&h->fileNum,sizeof(int),1,output);
  for(i=0;i<h->fileNum;i++){
    int len = strlen(h->fileNames[i]);
    fwrite(&len,sizeof(int),1,output);
    fwrite(h->fileNames[i],1,len,output);
  }

  fclose(output);
 CLEANUP:
  freeHeader(&h);
  return status;
}


int main(int argc, char** argv){
  if(argv[1][0] == 'c'){
    return create(argv[2], argv+3, argc-3);
  }else{
    return 0; //extract();
  }
}
