#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>

#include "colors.h"

typedef struct flags_{
	bool dotFiles;
	bool rawSize;
}flags;


void handleArgs(char* arg, flags* flag){
	for(int i=1;i<strlen(arg);i++){
		switch(arg[i]){
			case 'a': flag->dotFiles = true;break;
			case 'l': flag->rawSize = true;break;
			default: printf("Unknown arg %c passed\n",arg[i]);break;
		}
	}
	return;
}

//Initialize the flags struct, set all default values
flags* initFlags(){
	flags* def = malloc(sizeof(flags));
	if(def!=NULL){
		def->dotFiles = false;
		def->rawSize = false;
	}
	return def;
}

int getFileSize(struct dirent* file){
	FILE* stream = fopen(file->d_name, "rb");
	fseek(stream,0L,SEEK_END);
	int size = ftell(stream);
	fclose(stream);
	return size;
}

int main(int argc, char* argv[]){
	flags* flags = initFlags();
	char* abs = getcwd(NULL, 0);
	//Flags
	if(argc!=1){
		for(int i=1;i<argc;i++){
			if(argv[i][0]=='-'){
				handleArgs(argv[i],flags);
			}
		}
	}

	DIR* stream = opendir(abs);
	if(stream == NULL){
		return -1;
	}
	struct dirent* cur;
	while(true){
		cur = readdir(stream);
		if(cur==NULL){
			break;
		}
		if(
			(flags->dotFiles) ||
			((cur->d_name)[0]!='.')){

				switch(cur->d_type){
					case DT_DIR: printf(KBLU);break;
					case DT_REG: printf(KWHT);break;
				}
				printf(cur->d_name);
				//Size
				if(flags->rawSize){
					printf(KNRM);
					printf(": ");
					switch(cur->d_type){
						case DT_DIR: printf(" directory");break;
						default: printf(": %d bytes",getFileSize(cur));
					}
				}
				printf("\n");
			}
		}

	printf(KNRM);
	return 0;
}

