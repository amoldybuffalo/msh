typedef struct hash_element_str
{
	char key[500];
	char value[1000];
	int (*add)(struct hash_element_str*, char*, char*);
	int (*modify)(struct hash_element_str*, char*, char*);
	int (*exists)(struct hash_element_str*, char*);
	char* (*find)(struct hash_element_str*, char*);
} hash_element_str;

typedef char* (*fptr_builtin)(char**, int); 

typedef struct hash_element_fptr
{
	char key[500];
	fptr_builtin value;
	fptr_builtin (*find)(struct hash_element_fptr*, char*);
	int (*add)(struct hash_element_fptr*, char*, fptr_builtin);
	int (*modify)(struct hash_element_fptr*, char*, fptr_builtin);
} hash_element_fptr;

#define hash_map_end(hash_map, i) (hash_map[ i ].key[0] == '\n')

void hash_str_init(hash_element_str* hash_map, int size);
char* hash_str_find(hash_element_str* hash_map, char* key);
int hash_str_add(hash_element_str* hash_map, char* key, char* value);
int hash_str_modify(hash_element_str* hash_map, char* key, char* value);
int hash_str_exists(hash_element_str* hash_map, char* key);

void hash_fptr_init(hash_element_fptr* hash_map, int size);
fptr_builtin hash_fptr_find(hash_element_fptr* hash_map, char* key);
int hash_fptr_add(hash_element_fptr* hash_map, char* key, fptr_builtin value);
int hash_fptr_modify(hash_element_fptr* hash_map, char* key, fptr_builtin value);

