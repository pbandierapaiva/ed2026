#include <stdio.h>
#include <setjmp.h>

jmp_buf exception_env;

void divide(int a, int b)
{
    if (b == 0)
        longjmp(exception_env, 1);   /* throw */

    printf("Result = %d\n", a / b);
}

int main(void)
{
    int exception = setjmp(exception_env);

    if (exception == 0) {
        /* try */
        printf("Try...\n");

        divide(10, 0);

        printf("Operação completada\n");
    }
    else {
        /* catch */
        printf("Exceção!\n");
    }

    printf("Program continues\n");
}