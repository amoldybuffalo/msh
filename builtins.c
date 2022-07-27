#include <stddef.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "hash_map.h"
#include "utils.h"
#include "builtins.h"
#ifndef GLOBALS
#define GLOBALS
#include "globals.h"
#endif
char* echo(char** args, int argc)
{
	char* result = join(args, " ", argc);
	return result;	
} 

char* cd(char** args, int argc)
{
	if(args[1] != NULL && strcmp(args[1], "") != 0) chdir(args[1]);
	return strcpy((char*)malloc(2),"");
	
}

char* pwd(char** args, int argc)
{	

	char* buff = malloc(PATH_MAX);
	getcwd(buff, PATH_MAX * sizeof(char));
	return buff;
}
char* exit_msh(char** args, int argc)
{
	exit(0);
}

/*char* ls(char** args, int argc)
{
	char* result = malloc(10000 * sizeof(char)); 
	DIR *d;
	struct dirent *dir;
	
	if(args[1]) d = opendir(args[1]);
	else
	{
		char* buff = malloc(PATH_MAX);
		getcwd(buff, PATH_MAX * sizeof(char));	
		d = opendir(buff);
		free(buff);

	} 
		
	
	if (d) {
	   while ((dir = readdir(d)) != NULL) {
	   	  if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
	   	  {
	      	strcat(result, dir->d_name);
	      	strcat(result, "\n");
	      }
	   }
	   closedir(d);
	}
	return result;
	
	
}*/

void init_builtins(hash_element_fptr* builtins, int length)
{
		hash_fptr_init(builtins, length);
		hash_fptr_add(builtins, "echo", echo);
		hash_fptr_add(builtins, "cd", cd);
		hash_fptr_add(builtins, "pwd", pwd);
		hash_fptr_add(builtins, "exit", exit_msh);
		//hash_fptr_add(builtin_arr, "ls", ls);
}
