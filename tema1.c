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
	thisDir->head_children_dirs = head_children_dirs;
	thisDir->head_children_files = head_children_files;
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

	if (parent->head_children_files == NULL){
		
		parent->head_children_files = thisFile;
		return;
	}

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
	
	if (parent->head_children_dirs == NULL){
		
		toIterate->next = thisFile;
		return;
	}

	Dir* toIterateDirs = parent->head_children_dirs;

	while(1){

		if (strcmp(toIterateDirs->name, name) == 0){

			puts("File already exists");
			return;
		}

		if (toIterateDirs->next == NULL)
			break;
		toIterateDirs = toIterateDirs->next;
	}

	toIterate->next = thisFile;
	
}

void mkdir (Dir* parent, char* name) {

	Dir* thisDir = allocDir(name, parent, NULL, NULL, NULL);
	
	if (parent->head_children_dirs == NULL){

		parent->head_children_dirs = thisDir;
		return;
	}

	Dir* toIterate = parent->head_children_dirs;

	while (1){

		if (strcmp(toIterate->name, name) == 0){

			puts("Directory already exists");
			return;
		}

		if (toIterate->next == NULL)
			break;
		toIterate = toIterate->next;
	}
	
	if (parent->head_children_files == NULL){

		toIterate->next = thisDir;
		return;
	}

	File* toIterateFiles = parent->head_children_files;

	while (1){

		if (strcmp(toIterateFiles->name, name) == 0){

			puts("Directory already exists");
			return;
		}

		if (toIterateFiles->next == NULL)
			break;

		toIterateFiles = toIterateFiles->next;
	}

	toIterate->next = thisDir;
	
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

void rm (Dir* parent, char* name) {

	if (parent->head_children_files == NULL){

		puts("Could not find the file");
		return;
	}

	File* toIterate = parent->head_children_files;
	File* toIteratePrev = parent->head_children_files;
	
	while (1){

		if (strcmp(toIterate->name, name) == 0){

			if (toIteratePrev == toIterate){ //cazul in care avem primul fisier din lista

				if (toIterate->next == NULL)
					parent->head_children_files = NULL;
				else
					parent->head_children_files = toIterate->next;

				return;
			}

			if (toIterate->next == NULL){

				toIteratePrev->next = NULL;
				return;
			}
			else {

				toIteratePrev->next = toIterate->next;
				//+dealoc;
				return;
			}
			return; //just 2 be safe :D
		}

		if (toIterate->next == NULL){

			puts("Could not find the file");
			return;
		}

		toIteratePrev = toIterate;
		toIterate = toIterate->next;
	}	

}

void rmdir (Dir* parent, char* name) {

	if (parent->head_children_dirs == NULL){

		puts("Could not find the dir");
		return;
	}

	Dir* toIterate = parent->head_children_dirs;
	Dir* toIteratePrev = parent->head_children_dirs;
	
	while (1){

		if (strcmp(toIterate->name, name) == 0){

			if (toIteratePrev == toIterate){ //cazul in care avem primul fisier din lista

				if (toIterate->next == NULL)
					parent->head_children_dirs = NULL;
				else
					parent->head_children_dirs = toIterate->next;

				return;
			}

			if (toIterate->next == NULL){

				toIteratePrev->next = NULL;
				return;
			}
			else {

				toIteratePrev->next = toIterate->next;
				//+dealoc;
				return;
			}
			return; //just 2 be safe :D
		}

		if (toIterate->next == NULL){

			puts("Could not find the dir");
			return;
		}

		toIteratePrev = toIterate;
		toIterate = toIterate->next;
	}

}

void cd(Dir** target, char *name) {

	Dir* toIterateDirs = (*target)->head_children_dirs;
	
	if (strcmp(name, "..") == 0){

		if ((*target)->parent == NULL)
			return;

		*target = (*target)->parent;
		return;
	}

	if (toIterateDirs == NULL){

		puts("No directories found!");
		return;
	}

	while (1){

		if (strcmp(toIterateDirs->name, name) == 0){

			*target = toIterateDirs;
			return;
		}

		if (toIterateDirs->next == NULL){

			puts("No directories found!");
			return;
		}

		toIterateDirs = toIterateDirs->next;
	}
}

char *pwd (Dir* target) {

	Dir* toIterateDirs = target;
	char* toPrint = malloc(MAX_INPUT_LINE_SIZE);
	int level = 0;

	while(1){

		if (strcmp(toIterateDirs->name, "home") == 0)
			break;

		level++;
		toIterateDirs = toIterateDirs->parent;
	}

	strcpy(toPrint, "/home"); //stiu sigur ca sunt la home,
							  //fac asa bcs char* stuff;
	toIterateDirs = toIterateDirs->head_children_dirs;

	for (int i = 0; i < level; i++){

		strcat(toPrint, "/");
		strcat(toPrint, toIterateDirs->name);
		toIterateDirs = toIterateDirs->head_children_dirs;
	}
	
	return toPrint;
}

void stop (Dir* target) {

	//delacoare memorie
}

void printTreeFiles (File* target, int level){

	char* spaces = malloc(100);

	for (int i = 0; i < level * 4; i++){

		if (spaces == NULL)
			strcpy(spaces, " ");
		else
			strcat(spaces, " ");
	}

	strcat(spaces, target->name);
	puts(spaces);

	if (target->next != NULL)
		printTreeFiles(target->next, level);
}

void tree (Dir* target, int level) {


	char* spaces = malloc(100);
	int level1 = level;

	for (int i = 0; i < level1 * 4; i++){

		if (spaces == NULL)
			strcpy(spaces, " ");
		else
			strcat(spaces, " ");
	}

	strcat(spaces, target->name);
	puts(spaces);

	if (target->head_children_dirs != NULL){ //if1

		int level2 = level1;
		tree(target->head_children_dirs, ++level2);
	} 

	if (target->head_children_files != NULL){ //if2

		int level2 = level1;
		printTreeFiles(target->head_children_files, ++level2);
	}

	if (target->next != NULL) //if3
		tree(target->next, level1);


	if (strcmp(target->parent->name, "home")  == 0 && target->parent->head_children_files != NULL) //if4, o atrocitate
		printTreeFiles(target->parent->head_children_files, level1);							   //FIX !! - L.E: I DIDNT :D
}

int checkIfNewnameExists (Dir* parent, char* name){

	Dir* toIterateDirs = parent->head_children_dirs;
	File* toIterateFiles = parent->head_children_files;

	while(1){

		if (toIterateDirs == NULL)
			break;

		if (strcmp(toIterateDirs->name, name) == 0)
			return 0; //newname already exists

		toIterateDirs = toIterateDirs->next;
	}	

	while(1){

		if (toIterateFiles == NULL)
			break;

		if (strcmp(toIterateFiles->name, name) == 0)
			return 0; //newname already exists

		toIterateFiles = toIterateFiles->next;
		
	}

	return 1; //newname doesn't exists
}

void mv(Dir* parent, char *oldname, char *newname) {

	Dir* toIterateDirs = parent->head_children_dirs;
	File* toIterateFiles = parent->head_children_files;


	while(1){

		if (toIterateDirs == NULL)
			break;
		
		if (strcmp(toIterateDirs->name, oldname) == 0){ //oldname exists - yey!;

			if (checkIfNewnameExists(parent, newname) == 0){

				puts("File/Director already exists");
				return;
			}
			//if we get here, all of the conditions are ok and we can do the mv;
			Dir* toMoveDir = allocDir(newname, parent, toIterateDirs->head_children_files, 
			 toIterateDirs->head_children_dirs, NULL);
			rmdir(parent, oldname);
			Dir* toIterateNewDirs = parent->head_children_dirs;
			if (toIterateNewDirs == NULL){

				parent->head_children_dirs = toMoveDir;
				return;
			}

			while(1){

				if (toIterateNewDirs->next == NULL){
					
					toIterateNewDirs->next = toMoveDir;
					return;
				}

				toIterateNewDirs = toIterateNewDirs->next;	
			}

			return;
		}

		toIterateDirs = toIterateDirs->next;
	}

	while(1){

		if (toIterateFiles == NULL)
			break;
		
		if (strcmp(toIterateFiles->name, oldname) == 0){ //oldname exists - yey!;

			if (checkIfNewnameExists(parent, newname) == 0){

				puts("File/Director already exists");
				return;
			}

			//if we get here, all of the conditions are ok and we can do the mv;
			File* toMoveFile = allocFile(newname, parent, NULL);
			rm(parent, oldname);
			File* toIterateNewFiles = parent->head_children_files;
			if (toIterateNewFiles == NULL){

				parent->head_children_files = toMoveFile;
				return;
			}

			while(1){

				if (toIterateNewFiles->next == NULL){
					
					toIterateNewFiles->next = toMoveFile;
					return;
				}

				toIterateNewFiles = toIterateNewFiles->next;	
			}

			return;
		}

		toIterateFiles = toIterateFiles->next;
	}
	// if we're here, oldname doesnt exist;
	puts("File/Director not found");
	return;

}

int main () {

	char* input = malloc(MAX_INPUT_LINE_SIZE);
	Dir* home = allocDir("home", NULL, NULL, NULL, NULL);
	Dir* currentDir = home;

	do
	{	
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

		if (strstr(input, "ls") != NULL)
			ls(currentDir);

		if (strstr(input, "rm") != NULL){

			if (strstr(input, "rmdir") != NULL){ //confusion
			
				token = strtok(input, " ");
				token = strtok(NULL, " ");
				
				rmdir(currentDir, token);	
			}
			else {
				token = strtok(input, " ");
				token = strtok(NULL, " ");

				rm(currentDir, token);
			}
		}

		if (strstr(input, "cd") != NULL){

			token = strtok(input, " ");
			token = strtok(NULL, " ");
			
			cd(&currentDir, token);
		}

		if (strstr(input, "tree") != NULL){

			if (currentDir->head_children_dirs != NULL)
				tree(currentDir->head_children_dirs, 0);
		}

		if (strstr(input, "pwd") != NULL){

			char* toPrint = pwd(currentDir);
			puts(toPrint);
		}

		if (strstr(input, "mv") != NULL){

			token = strtok(input, " ");
			token = strtok(NULL, " ");
			char* oldname = token;
			token = strtok(NULL, " ");
			char* newname = token;
			
			mv(currentDir, oldname, newname);
		}

		if (strcmp(input, "stop") == 0){

			stop(currentDir);
			break;
		}

	} while (1);
		
	free(input);
	//free home;
	//free currentDir;
	return 0;
}
