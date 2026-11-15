# Notes C Programming

## Compiling and running C code
```
cd path/to/your/folder
gcc program.c -o program
./program
```

## Bitwise operators
- AND: &
- OR: |
- XOR: ^
- NOT: ~
- Shift left: <<
- Shift right: >>

## Arrays
### Basics
- Declaring an array of 4 floats: `float f[4];`
- Using `sizeof(array)` only works in the scope in which the array was defined
    - E.g. not when array was passed to a function because the point size gets measured
- Declaring array with constants: `int a[5] = {1, 2, 3, 4, 5};`
    - Same as `int a[5] = {1, 2, 3, 4, 5, 0, 0};`
- C does not stop you from accessing arrays out of bounds

### Arrays and Pointers
- Pointer to an array = point to first element of the array
Getting point to first element of an array
```c
int a[5] = {1, 2, 3, 4, 5};
int *p;
// 1st way
p = &a[0];
// 2nd way
p = a;
```

# Structs
Declaring struct:
```c
struct car {
    char *name;
    float price;
    int speed;
};
```
Initializing struct:
```c
struct car saturn = {"Saturn SL/2", 16000.99, 175};
```
Passing struct to function:
- Pass by value: Pass the struct: `function(struct);`
    - Changes made inside the function will not affect the original structure
- Pass by reference: Pass a pointer: `function(&struct);`
    - Changes made inside the function will affect the original 
    - Modify data using `->` operator


# Switch statements
```c
int goat_count = 2;

switch (goat_count) {
    case 0:
        printf("You have no goats.\n");            
        break;

    case 1:
        printf("You have a singular goat.\n");
        break;

    case 2:
        printf("You have a brace of goats.\n");
        break;

    default:
        printf("You have a bona fide plethora of goats!\n");
        break;
}
```

# Reading file line by line
```c
#include <stdio.h>

FILE *f = fopen("programs/sum.asm", "r");   // "r" = read mode
if (f == NULL) {
    perror("fopen");   // prints why, e.g. "No such file or directory"
    return 1;
}

char line[256];
int line_num = 0;
while (fgets(line, sizeof line, f) != NULL) {
    line_num++;
    // process line here
}
fclose(f);
```
- `fgets`: 
    - Reads one line at a time into buffer and returns NULL at end of file
    - Reads at most `sizeof line - 1` characters so it can't overflow the buffer
    - Keeps newline character at end of file

# Splitting a string into tokens separated by a delimiter character
```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "apple,banana,cherry";

    char *token = strtok(text, ",");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    return 0;
}
```
# Splitting code across .c and .h files
- `.h` file: for struct and type definitions, function declarations, constants and enums
- `.c` file: for function bodies, helper functions only this file uses, variables

# Makefile
