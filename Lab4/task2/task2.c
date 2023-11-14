#include <stdio.h>
#include <stdlib.h>

/* Function declarations */
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int endProgram(int a, int b);

int main(void)
{
    int a = 6, b = 3, choice;
    int result = 0;

    /* Array of function pointers */
    int (*operations[5])(int, int) = {add, subtract, multiply, divide, endProgram};

    printf("Operand 'a' : %d | Operand 'b' : %d\n", a, b);
    printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit): ");
    scanf("%d", &choice);

    /* Call the appropriate function */
    result = (*operations[choice])(a, b);

    if (choice != 4) {
        printf("x = %d\n", result);
    }

    return 0;
}

/* Function definitions */
int add(int a, int b) { 
    printf("Adding 'a' and 'b'\n"); 
    return a + b; 
}

int subtract(int a, int b) { 
    printf("Subtracting 'b' from 'a'\n"); 
    return a - b; 
}

int multiply(int a, int b) { 
    printf("Multiplying 'a' and 'b'\n"); 
    return a * b; 
}

int divide(int a, int b) { 
    printf("Dividing 'a' by 'b'\n");
    // Avoid division by zero. Note: This leads to an incorrect result for b = 0
    return a / (b + !b); 
}

int endProgram(int a, int b) { 
    printf("Exiting program\n"); 
    exit(0); 
    return 0; // This return is just to satisfy the function signature and will never be executed
}
