#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
void append_char(char* dest, char c)
{
	char to_append[] = {c, '\0'};
	strcat(dest, to_append);
}

void substr(char* dest, const char* source, size_t start, size_t end)
{
	for(size_t i = 0; i < strlen(source); i++)
	{
		if(i >= start && i <= end)
		{	
			append_char(dest, source[i]);
		}
	}	
}

char* join(char** str_arr, char* ch, int arr_size)
{
	char* result = malloc(strlen(str_arr[0]) * arr_size + strlen(ch) * arr_size -1);
	for(int i = 0; i < arr_size; i++)
	{
		strcat(result, str_arr[i]);
		if(arr_size - 1 != i) strcat(result, ch);
	}	
	return result;
}

char** split(char* str, char* ch, int* length)
{	
	
	int character_count = 0;
	size_t str_length  = strlen(str);
	for(size_t i = 0; i < str_length; i++)
	{	
		if(str[i] == ch[0])
		{
			character_count++;
		}	
	}
    char** str_arr = malloc(sizeof(char*) * character_count);
    for(int i = 0; i < character_count; i++)
    {
    	str_arr[i] = malloc(sizeof(char) * 100);	
    } 

    str_arr[0] = strtok(str, ch);
    
    int i = 0;
    while(str_arr[i] != NULL)
    {	
    	i++;
    	str_arr[i] = strtok(NULL, ch);
    	
    }
    if(length != NULL) *length = character_count + 1;
    
	return str_arr;
}

int str_includes_ch(char* str, char ch)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		if(str[i] == ch) return 1;
	}
	return 0;
}

char** sub_str_arr(char** source, int start, int end, int length)
{
	int new_length = (end - start) + 1;
	char** new_str_arr;
	if( new_length < 1) 
	{
		printf("ERROR: invalid sub array!\n");
		exit(-1);
	}
	else
	{
		new_str_arr = malloc(new_length);
		for(int i = 0; i < new_length; i++)
		{
			new_str_arr[i] = malloc(strlen(source[0]) + 1);
			
		}
	}
	
	for(int i = 0, j = 0; i < length; i++)
	{
		if( i >= start)
		{	
			if(i <= end)
			{
				strncpy(new_str_arr[j], source[i], strlen(source[0]) + 1); 
				j++;
			}
			else
			{
				break;
			}
			
		}	
	}

	return new_str_arr;
	
	
}




