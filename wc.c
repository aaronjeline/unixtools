#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct result{
  int newl;
  int wc;
  int bytes;
};


void print_result(struct result out, char* fn){
  if(fn == 0x0){
    printf("%d    %d    %d\n", out.newl, out.wc, out.bytes);
  }else{
    printf("%d  %d  %d  %s\n", out.newl, out.wc, out.bytes, fn);
  }
  return;
}

struct result new_result(void){
  struct result new;
  new.newl = 0;
  new.wc = 1;
  new.bytes = 0;
  return new;
}

struct result wc(char* text){
  int i, len = strlen(text);
  char last = 'x';

  struct result data  = new_result();
  for(i = 0; i<len; i++){
    switch(text[i]){
    case ' ': if(last != ' '){data.wc++;}break;
    case '\n': data.newl++;break;
    default: break;
    }
    last = text[i];
  }
  data.bytes = len;
  return data;
}

void load(char* fn, char** dest){
  int size;
  FILE* f = fopen(fn, "r");
  fseek(f, 0L, SEEK_END);
  size = ftell(f);
  rewind(f);
  *dest = calloc(1, size);
  fread(*dest, 1, size, f);
  fclose(f);
  return;
}
  



void files(char** files, int len){
  int i;
  char* dat;
  for(i = 0; i < len; i++){
    load(files[i], &dat);
    print_result(wc(dat), files[i]);
    free(dat);
  }
  return;
}

void fromStdIn(void){
  char buf[1024];
  fgets(buf, 1024, stdin);
  print_result(wc(buf), 0x0);
  return;
}


int main(int argc, char** argv){
  if(argc > 1){
    files(argv+1, argc-1);
  }else{
    fromStdIn();
  }
    

  return 0;
}
