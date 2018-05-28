#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv){
  char* data = 0x0;
  int size;
  FILE* in = 0x0, *out = 0x0;
  if(argc!=3){
    fprintf(stderr, "Usage: %s src dst\n", argv[0]);
    return 1;
  }

  in = fopen(argv[1], "r");
  if(0x0 == in){
    fprintf(stderr, "Couldn't open %s for reading\n", argv[1]);
    return 1;
  }
  out = fopen(argv[2], "w");
  if(0x0 == out){
    fclose(in);
    fprintf(stderr, "Couldn't open %s for writing\n", argv[2]);
    return 1;
  }
  fseek(in, 0L, SEEK_END);
  size = ftell(in);
  rewind(in);

  data = malloc(size);
  fread(data, sizeof(char), size, in); 
  fwrite(data, sizeof(char), size, out);
  free(data);

  fclose(in);
  fclose(out);

  return 0;
}
