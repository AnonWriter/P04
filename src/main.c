#include <stdio.h>

int main(int argn, char *args[])
{
    // Esta es la funcion principal
    printf("Hola mundo.\n");

    for(int i = 0; i < 10; i++){
        printf("%d", i + 1);
    }
    printf("\n");

    return 0;
}
