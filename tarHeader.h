#ifndef TAR_HEADER_H
#define TAR_HEADER_H

  
struct header{
  int fileNum;
  char** fileNames;
  FILE** filePs;
  int* fileSizes;
};


struct header* buildHeader(char** fileNames, int num);

void freeHeader(struct header **head);

int compFileSize(char* filename);

#endif

