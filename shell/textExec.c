#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define CHUNK_SIZE 128


int getFileSize(char* path){
  struct stat sb;
  stat(path, &sb);
  return sb.st_size;
}

int isExeText(char* path){
  struct stat sb;
  FILE* fp;
  int err;
  int res;
  char ck[2];
  err = stat(path, &sb);
  if(err != 0 || !S_ISREG(sb.st_mode)){
    return 0;
  }
  printf("Potentially text\n");
  fp = fopen(path, "r");
  //Check if shebang exists
  fread(ck, 1, 2, fp);
  printf("%s\n",ck);
  res = 0 == strncmp("#!", ck, 2) ? 1 : 0;
  fclose(fp);
  return res;
}

char* getInt(char* path){
  FILE* fp;
  int chunks = 1, c, p = 0;
  char* buffer = malloc(CHUNK_SIZE);
  fp = fopen(path, "r");
  while((c = fgetc(file)) != EOF){
    buffer[p++] = (char) c;
    if(p > chunks * CHUNK_SIZE){
      realloc(buffer, (++chunks)*CHUNK_SIZE);
    }
    if((char) c == '\n'){break;}
  }
  buffer[p] = '\0';
  return buffer;
}
  
  
  
			 


  
  
  
  
  
