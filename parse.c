
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define _XOPEN_SOURCE 700
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

void push_to_history(char* command);
char* pop_from_history();

void resolve_arguments(char** args, int argc)
{
	int resolved_length = argc;
	for(int i = 0; i < argc; i++) if(args[i][0] == '"' && args[i][strlen(args[0])] != '"') resolved_length--;
	char** resolved_argument_array = malloc(resolved_length * sizeof(char*));
	for(int i = 0; i < resolved_length; i++) resolved_argument_array[i] = malloc(strlen(args[0]) + 1);
	//first pass to resolve variables
	for(int i = 0; i < argc; i++)
	{
		if(args[i][0] == '$') 
		{
			if(variables->exists(variables, substr(args[i],1, strlen(args[i])))) 
				strcpy(args[i], variables->find(variables, substr(args[i], 1, strlen(args[i]))));
			else printf("ERROR VARIABLE UNDEFINED");
			
		}
		
	}
	
}

void assign_variable(char* variable, char* contents)
{
	if(variables->exists(variables, variable))
	{
		variables->modify(variables, variable, contents);
	}
	else
	{
		variables->add(variables, variable, contents);
	}
	
}

char* parse(char* argument_string)
{	
	int length;
	char** argument_array = split(argument_string, " ", &length);
	resolve_arguments(argument_array, length);
	char* result = NULL;
	enum EXPRESSION_TYPE ep = find_expression_type(argument_array, length);
	switch(ep)
	{
		case DEFINITION: {
			char** var_arr = split(argument_array[0], "=", NULL);
			assign_variable(var_arr[0], var_arr[1]);
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
