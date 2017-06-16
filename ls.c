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
	bool humanSize;
}flags;

typedef struct filesize_{
	int size;
	char unit;
}filesize;

//Prints and destroys a filesize struct, returns a null pointer
filesize* printFileSize(filesize* i){
	printf("%d %c", i->size,i->unit);
	free(i);
	return 0x0;
}


void handleArgs(char* arg, flags* flag){
	for(int i=1;i<strlen(arg);i++){
		switch(arg[i]){
			case 'a': flag->dotFiles = true;break;
			case 'l': flag->rawSize = true;break;
			case 'h': flag->humanSize = true;break;
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
		def->humanSize = false;
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

void printFormattedSize(struct dirent* file, flags* flag){
	if(!(flag->rawSize || flag->humanSize)){
		return;
	}
	printf(KWHT);
	printf(": ");
	//Exceptions
	switch(file->d_type){
		case DT_DIR: printf("Directory");return;
	}
	filesize* size = malloc(sizeof(filesize));
	size->unit = ' ';
	size->size = getFileSize(file);
	if(flag->humanSize){
		char* units = " KMG";
		int i = 0;
		while(size->size > 1000){
			size->size /= 1000;
			i++;
		}
		size->unit = units[i];
	}
	printFileSize(size);
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
				printFormattedSize(cur, flags);
				printf("\n");
			}
		}

	printf(KNRM);
	return 0;
}

