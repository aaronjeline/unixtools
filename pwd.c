#include <stdio.h>
#include <unistd.h>


int main(int argc, char** argv){
  printf("%s\n", getcwd(0x0, 0));
  return 0;
}
