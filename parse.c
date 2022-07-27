#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

#include "defs.h"
#include "utils.h"
#include "io.h"
#include "hash_map.h"
#include "parse.h"

#ifndef GLOBALS
#define GLOBALS
#include "globals.h"
#endif
  

char* create_prompt(char* template)
{
	return template;
}
enum EXPRESSION_TYPE find_expression_type(char** expression, int length)
{
	
	if(str_includes_ch(expression[0], '='))
	{
		return DEFINITION;
	}
	
	return COMMAND;
}

char** resolve_arguments(char** argument_array, int length)
{

	enum SECTION_TYPE
	{
		VARIABLE,
		QUOTED
	};
	char** resolved_argument_array;
	for(int i = 0; i < length; i++);
	
}

char* parse(char* argument_string)
{	
	int length;
	char** argument_array = split(argument_string, " ", &length);
	char* result = NULL;
	enum EXPRESSION_TYPE ep = find_expression_type(argument_array, length);
	switch(ep)
	{
		case DEFINITION: {
			char** var_arr = split(argument_array[0], "=", NULL);
			print_var(var_arr[0]);
			print_var(var_arr[1]);
		
			if(variables->exists(variables, var_arr[0]))
			{
				variables->modify(variables, var_arr[0], var_arr[1]);
			}
			else
			{
				variables->add(variables, var_arr[0], var_arr[1]);
			}
			define_empty(result);
			
		}break;
		
		case COMMAND: {			
					
				fptr_builtin builtin = hash_fptr_find(builtins, argument_array[0]);  
				if(builtin == NULL) 
				{
					FILE* out;
					pid_t* process_pid = malloc(4);
					int ch;
					char** env = malloc(sizeof(char*));
					env[0] = malloc(3);
					strcpy(env[0], "TERM=linux");
					out = spawn(argument_array, length, env, process_pid);	
					while((ch = getc(out)) != EOF)
					{
						putc(ch, stderr);
					}
					kill(*process_pid, SIGKILL);
					pclose(out);
					define_empty(result);
					
				}
				else
				{
					result = builtin(argument_array, length);  	
				}
		} break;
		
		default: return result; break;
	}
	
	return result;
}
