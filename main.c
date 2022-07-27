#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "io.h"
#include "hash_map.h"
#include "builtins.h"
#include "parse.h"
#include "main.h"
#ifndef GLOBALS
#define GLOBALS
#include "globals.h"
#endif
hash_element_str settings[500];
hash_element_str variables[500];
hash_element_fptr builtins[100];

void intHandler(int signal) {
	fwrite("ctrl-c pressed\n", sizeof(char),  15, stdout);
}

int main()
{	

	signal(SIGINT, intHandler);
	
	hash_str_init(settings, 500);
	hash_str_init(variables, 500);
	init_builtins(builtins, 100);
	hash_str_add(settings, "workingdir", "/");
 	char c[500];
	
 	while(1)
 	{
	 	draw_prompt(">");
	 	get_line(c, sizeof(c));
	 	if(strcmp(c, "") != 0)
	 	{
	 		char* output = parse(c);
	 		printf("%s", output);
	 		fflush(stdout);
	 		free(output);
	 	} 

	 	
 	}
 	
 	
}
