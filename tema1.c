#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300

struct Dir;
struct File;

typedef struct Dir{
	char *name;
	struct Dir* parent;
	struct File* head_children_files;
	struct Dir* head_children_dirs;
	struct Dir* next;
} Dir;

typedef struct File {
	char *name;
	struct Dir* parent;
	struct File* next;
} File;

Dir* allocDir(char* name, struct Dir* parent, struct File* head_children_files, 
	struct Dir* head_children_dirs, struct Dir* next){

	Dir* thisDir = (Dir*) malloc(sizeof(Dir));
	thisDir->name = malloc(MAX_INPUT_LINE_SIZE);
	thisDir->parent = (Dir*) malloc(sizeof(Dir));
	thisDir->head_children_files = (File*) malloc(sizeof(File));
	thisDir->head_children_dirs = (Dir*) malloc(sizeof(Dir));
	thisDir->next = (Dir*) malloc(sizeof(Dir));

	strcpy(thisDir->name, name);
	thisDir->parent = parent;
	thisDir->head_children_files = head_children_files;
	thisDir->head_children_dirs = head_children_dirs;
	thisDir->next = next;

	return thisDir;

}

File* allocFile(char* name, struct Dir* parent, struct File* next){
	
	File* thisFile = (File*) malloc(sizeof(File));
	thisFile->name = malloc(MAX_INPUT_LINE_SIZE);
	thisFile->parent = (Dir*) malloc(sizeof(Dir));
	thisFile->next = (File*) malloc(sizeof(File));

	strcpy(thisFile->name, name);
	thisFile->parent = parent;
	thisFile->next = next;

	return thisFile;
}

void touch (Dir* parent, char* name) {

	File* thisFile = allocFile(name, parent, NULL);
	
	if (parent->head_children_files == NULL)
		parent->head_children_files = thisFile;
	else{

		File* toIterate = parent->head_children_files;
		
		while(1){

			if (strcmp(toIterate->name, name) == 0){

				puts("File already exists");
				return;
			}

			if (toIterate->next == NULL)
				break;
			toIterate = toIterate->next;
		}
		
		toIterate->next = thisFile;
	}
}

void mkdir (Dir* parent, char* name) {

	Dir* thisDir = allocDir(name, parent, NULL, NULL, NULL);
	
	if (parent->head_children_dirs == NULL)
		parent->head_children_dirs = thisDir;
	else{

		Dir* toIterate = parent->head_children_dirs;

		while (1){

			if (strcmp(toIterate->name, name) == 0){

				puts("Directory already exists");
				return;
			}

			if(toIterate->next == NULL)
				break;
			toIterate = toIterate->next;
		}

		toIterate->next = thisDir;
	}
}

void ls (Dir* parent) {

	Dir* toIterateDirs = parent->head_children_dirs;
	
	if (toIterateDirs != NULL){

		while(1){

			puts(toIterateDirs->name);
			toIterateDirs = toIterateDirs->next;
			if (toIterateDirs == NULL)
				break;
		}
	}

	File* toIterateFiles = parent->head_children_files;

	if (toIterateFiles != NULL){
		
		while(1){

			puts(toIterateFiles->name);
			toIterateFiles = toIterateFiles->next;
			if (toIterateFiles == NULL)
				break;
		}
	}

}

void rm (Dir* parent, char* name) {}

void rmdir (Dir* parent, char* name) {}

void cd(Dir** target, char *name) {}

char *pwd (Dir* target) {}

void stop (Dir* target) {}

void tree (Dir* target, int level) {}

void mv(Dir* parent, char *oldname, char *newname) {}

int main () {

	char* input = malloc(MAX_INPUT_LINE_SIZE);
	Dir* home = allocDir("home", NULL, NULL, NULL, NULL);
	Dir* currentDir = home;

	do
	{	
		puts("ASTA TRB PUSA NEAPARAT");
		char* token = malloc(MAX_INPUT_LINE_SIZE);

		fgets(input, MAX_INPUT_LINE_SIZE, stdin);
		input[strcspn(input, "\n")] = 0; //delete trailing \n;


		if (strstr(input, "touch") != NULL){
			
			token = strtok(input, " ");
			token = strtok(NULL, " ");
			
			touch(currentDir, token);
		}
		

		if (strstr(input, "mkdir") != NULL){

			token = strtok(input, " ");
			token = strtok(NULL, " ");

			mkdir(currentDir, token);
		}

		if (strstr(input, "ls") != NULL){
			ls(currentDir);
		}


		if (strcmp(input, "stop") == 0)
			break;

	} while (1);
		
	free(input);
	//free home;
	//free currentDir;
	return 0;
}
