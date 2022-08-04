#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "defs.h"
#include "stdio.h"
#include "string.h"
#include "utils.h"


void draw_prompt(char* prompt)
{
	printf("%s ", prompt);
	fflush(stdout);
}

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
int get_line (char *buff, size_t sz) {
    int ch, extra;
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}

FILE* spawn(char** args, int argc, char** env_variables, pid_t *process_pid)
{	
		//my code to get the program and then the arguments to it.
		char* program = malloc(strlen(args[0] + 1));
		char** cut_args = sub_str_arr(args, 1, argc, argc);
		for(int i = 0; i < argc-1; i++)
		{
			print_var(cut_args[i]);
		}
		strcpy(program, args[0]);
		
		pid_t pid = 0;
		int pipefd[2];
		FILE* output;
		pipe(pipefd); //create a pipe
		pid = fork(); //spawn a child process
		if (pid == 0)
		{
			// Child. Let's redirect its standard output to our pipe and replace process with tail
			 close(pipefd[0]);
			 dup2(pipefd[1], STDOUT_FILENO);
		 	 dup2(pipefd[1], STDERR_FILENO);
		 	 execvpe(program, cut_args, env_variables);
		}
		
		//pass the pid to an outer process
		if(process_pid) *process_pid = pid;
		
		close(pipefd[1]);
		output = fdopen(pipefd[0], "r");
		return output;

}


