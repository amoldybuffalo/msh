void append_char(char* dest, char c);
void substr(char* dest, const char* source, size_t start, size_t end);
char** split(char* str, char* ch, int* length);
char* join(char** str_arr, char* ch, int arr_size);
int str_includes_ch(char* str, char ch);
char** sub_str_arr(char** source, int start, int end, int length);
