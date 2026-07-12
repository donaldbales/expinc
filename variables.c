#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
Pointers

A pointer is a variable that holds a memory location, an address.

A pointer can serve as an argument in a function.

The address of a pointer is a valid construction in C, represented 
by using two asterisks.

A function that returns an address is classified as a pointer function.

You can return the address of any variable used in the function, 
providing that the variable is declared static.

It’s important to remember the dual nature of a pointer. Without the 
asterisk, it stores an address. With the asterisk, the pointer fetches 
the value stored at its address.




Pointer Operators

Asterisk.  The unary asterisk operator (*) declares a pointer.
           Also to obtain the value stored at the address stored 
           in the pointer variable. 
           Adding the asterisk is “dereferencing” the pointer.

Ampersand. The ampersand operator (&) returns a variable’s address.

sizeof.    The sizeof operator obtains the number of bytes a variable 
           or buffer occupies in memory.
           The sizeof operator returns a value as a size_t data type.

Symbolic Constants

NULL.      The NULL symbolic constant references an unassigned pointer.
           The NULL value is returned from functions when a pointer is
           expected but failed to be assigned.
           The symbolic constant NULL is not zero. It doesn’t represent 
           memory location zero. It’s also not the same thing as the 
           null character, \0.

size_t.    The size_t data type references a quantity of memory – storage. 
           This value is returned by several functions, as well as by the 
           sizeof operator.
           Data type size_t is an unsigned integer value. When outputting 
           this data type, use the %zu or %ul placeholder in a printf() 
           statement.

Pointers and Arrays

Arrays are buffers.
           An array is a buffer – a storage space. It’s declared with a 
           data type and the number of items, or elements, in the array:
           int ints[10];        // a buffer for ten integers
           float floats[10];    // a buffer for ten floats
           char characters[31]; // a buffer for 30 charcters + the null 
           terminator '\0'.
           char string[] = "This is auto initialized to hold this string";

The first element is zero.

The array name (with no brackets) represents the entire array.

Arrays cannot be re-dimensioned.
           Arrays are declared a fixed size and connot be re-dimensioned.

Array size. 
           int array_size = sizeof(array_name)/sizeof(array_type);
-OR-
           int array_size = sizeof(array_name)/sizeof(array_name[0]);

Similarities

Address.   A pointer and an array do not need to be prefixed by an 
           ampersand when obtaining their address.

An Array as an Argument.
    a

An Array as a Return Value.
           
An array isn’t a function data type. 

A function must declared as a pointer function
    char *ptr function_name()

Returning an array from a function requires that the array be 
be declared as static.

The calling function stores the returned array as a pointer.

An empty string is one that contains only the terminating null character. 

A null string is one that’s uninitialized.

When using pointer arithmetic, beware of buffer overflow! Other 
programming languages guard against overflow – but not C! It’s up 
to you, the programmer, to ensure that buffers don’t overflow.








*/

static void f_array_as_array_arg(char arr[])
{
	printf("%s\n", arr);
}

static void f_array_as_ptr_arg(char *arr)
{
	printf("%s\n", arr);
}

// OK, but flagged as a memory leak by splint
static char *f_return_an_array()
{
	static char local_array[] = "This is a function's static local array.";
	char *p = local_array;
	return p;
}
// Better
static char *f_return_a_pointer()
{
	char local_array[] = "This is a function's temporary local array.";
	char *la;

	la = malloc(strlen(local_array));
	if (la == NULL)
	{
		printf("Failed to allocate storage.");
		exit(EXIT_FAILURE);
	}

	strcpy(la, local_array);

	return la;
}

int main()
{
	size_t array_size;
	// base variables
	double d = 1.1;
	float f = 2.2;
	int i = 3;
	long l = 4;
	char c = 'a';
	char a[31] = "123456789012345678901234567890";

	// Pointers
	// Asterisk. The unary asterisk operator (*) declares a pointer.
	// After its declaration, however, the pointer is used with or 
	// without the asterisk operator.
	double *dp = NULL; // yes, you can do this here
	float *fp;
	int* ip;
	long *lp;
	char *cp;
	char *ap;
	void *vp;

	// initialize the pointers
	dp = NULL;
	fp = NULL;
	ip = NULL;
	lp = NULL;
	cp = NULL;
	ap = NULL;
	vp = NULL;

	// Ampersand. The ampersand operator (&) returns a variable’s address.
	dp = &d;
	fp = &f;
	ip = &i;
	lp = &l;
	cp = &c;
	ap = a; // no &, due to a special relationship between pointers and arrays.
	vp = malloc(31);

	// The array name represents the entire array:
	// a
	array_size = sizeof(a)/sizeof(char);
	// -or-
	array_size = sizeof(a)/sizeof(a[0]);

	f_array_as_array_arg(a);
	f_array_as_ptr_arg(a);

	ap = f_return_an_array();
	printf("%s\n", ap);
//	free(ap);	// callng free() on a static array causes an error, 
				// but splint doesn like that it is un-free-d.
	ap = NULL;
	
	// You can re-allocate stroage smaller of larger with this:
	// void *realloc(void *ptr, size_t size);
	
	ap = f_return_a_pointer();
	printf("%s\n", ap);
	free(ap);

	free(vp);
	return 0;
}