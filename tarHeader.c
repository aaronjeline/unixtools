#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "tarHeader.h"

struct header* buildHeader(char** fileNames, int num){
  struct header *head;
  FILE* temp;
  int i;
  head = malloc(sizeof(struct header));
  head->fileNum = num;
  head->fileNames = fileNames;
  head->filePs = malloc(sizeof(FILE*) * num);
  head->fileSizes = malloc(sizeof(int) * num);
  for(i=0;i<num;i++){
    temp = fopen(fileNames[i], "r");
    if(0x0 == temp){
      head = 0x0;
      break;
    }
    head->filePs[i] = temp;
    head->fileSizes[i] = compFileSize(fileNames[i]);
  }
  return head;
}


void freeHeader(struct header **headp){
  int i;
  struct header *head = *headp;
  for(i=0;i<head->fileNum;i++){
    fclose(head->filePs[i]);
  }
  free(head->fileSizes);
  free(head->filePs);
  free(head);
  *headp = 0x0;
}

int compFileSize(char* filename){
  struct stat sb;
  stat(filename, &sb);
  return sb.st_size;
}
