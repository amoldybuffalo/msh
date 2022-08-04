#define print_var(var) _Generic((var),\
   char*: printf(#var " is %s\n", var),\
	 int: printf(#var " is %d\n", var),\
  double: printf(#var " is %f\n", var))\
  
#define define_empty(str) str=malloc(2); strcpy(str, ""); 
