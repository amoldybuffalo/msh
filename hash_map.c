#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "hash_map.h"

void hash_str_init(hash_element_str* hash_map, int size)
{	
	hash_map->add = &hash_str_add;
	hash_map->modify = &hash_str_modify;
	hash_map->find = &hash_str_find;
	hash_map->exists = &hash_str_exists;
	for(int i = 0; i < size; i++)
	{
		if(i == size - 1) hash_map[i].key[0] = '\n';
		else hash_map[i].key[0] = '\0';		
		strcpy(hash_map[i].value, "");
	}
}

char* hash_str_find(hash_element_str* hash_map, char* key)
{
	if(key[0] == '\0') { fprintf(stderr, "Error: empty string is not a valid key.\n"); return NULL; }
	if(key[0] == '\n') { fprintf(stderr, "Error: newline is not a valid key.\n"); return NULL; }
	
	for(int i = 0;  !hash_map_end(hash_map, i); i++)
	{	
		if(strcmp(hash_map[i].key, key) == 0)
		{	
			char* result = malloc(strlen(hash_map[i].value) + 1);
			strcpy(result, hash_map[i].value);
			printf(result);
			return result;
		}
	}
	return 0;
	
}

int hash_str_add(hash_element_str* hash_map, char* key, char* value)
{
	if(key[0] == '\0') { fprintf(stderr, "Error: empty string is not a valid key.\n"); return -1; }
	if(key[0] == '\n') { fprintf(stderr, "Error: newline is not a valid key.\n"); return -1; }
	for(int i = 0; i < (int) strlen(key); i++)
	{
		if(key[i] == '\n') {fprintf(stderr, "Errror: no newlines in keys. \n"); return -1;}
	}
	for(int i = 0; !hash_map_end(hash_map, i); i++)
	{
		if(hash_map[i].key[0] == '\0')
		{
			strcpy(hash_map[i].key, key);
		 	strncpy(hash_map[i].value, value, sizeof(char) * 1000);
			return 0;
		}
	}
	return -1;	
}

int hash_str_modify(hash_element_str* hash_map, char* key, char* value)
{
	for(int i = 0; !hash_map_end(hash_map, i); i++)
	{
				if(strcmp(key, hash_map[i].key) == 0)
				{
				 	strncpy(hash_map[i].value, value, sizeof(char) * 1000);
					return 0;
				}
	}
	return -1;		
}

int hash_str_exists(hash_element_str* hash_map, char* key)
{
	for(int i = 0; !hash_map_end(hash_map, i); i++)
	{
			if(strcmp(key, hash_map[i].key) == 0)
			{
				return 1;
			}
	}
	return 0;
	
}

void hash_fptr_init(hash_element_fptr* hash_map, int size)
{	
	for(int i = 0; i < size; i++)
	{
		if(i == size - 1) hash_map[i].key[0] = '\n';
		else hash_map[i].key[0] = '\0';		
	    hash_map[i].value = NULL;
	}
}


fptr_builtin hash_fptr_find(hash_element_fptr* hash_map, char* key)
{
	if(key[0] == '\0') { fprintf(stderr, "Error: empty string is not a valid key.\n"); return NULL; }
	if(key[0] == '\n') { fprintf(stderr, "Error: newline is not a valid key.\n"); return NULL; }
	
	for(int i = 0; hash_map[i].key[0] != '\n'; i++)
	{	
		if(strcmp(hash_map[i].key, key) == 0)
		{
			return hash_map[i].value;
		}
	}
	
	return NULL;
	
}

int hash_fptr_add(hash_element_fptr* hash_map, char* key, fptr_builtin value)
{
	if(key[0] == '\0') { fprintf(stderr, "Error: empty string is not a valid key.\n"); return -1; }
	if(key[0] == '\n') { fprintf(stderr, "Error: newline is not a valid key.\n"); return -1; }
	for(int i = 0; i < (int) strlen(key); i++)
	{
		if(key[i] == '\n') {fprintf(stderr, "Errror: no newlines in keys. \n"); return -1;}
	}
	for(int i = 0; hash_map[i].key[0] != '\n'; i++)
	{
		if(hash_map[i].key[0] == '\0')
		{
			strcpy(hash_map[i].key, key);
		 	hash_map[i].value = value;
			return 0;
		}
	}
	return -1;	
}
int hash_fptr_modify(hash_element_fptr* hash_map, char* key, fptr_builtin value);
