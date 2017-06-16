#include <stdio.h>




int main(int argc, char* argv[]){
	if(argc!=2){
		printf("Incorrect arguments.\n");
		return -1;
	}
	FILE* file = fopen(argv[1], "rb");
	if(file==NULL){
		printf("Error opening file for reading\n");
		return -1;
	}

	fseek(file,0L,SEEK_END);
	int size = ftell(file);
	fseek(file,0L,SEEK_SET);

	char buffer[size];
	fread(buffer,1,size,file);
	fclose(file);
	printf(buffer);
	printf("\n");
	return 0;
}
