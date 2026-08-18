// Usando strings

#include <stdio.h>

#define MAXIMOSTR 10

int main() {

    char str[MAXIMOSTR];

    printf("Qual o seu nome: ");
    fgets( str, MAXIMOSTR, stdin);
    printf("\nAlo %s!\n\n", str);


    printf("Qual o seu nome: ");
    scanf( "%s", str);
    printf("\nAlo %s!\n\n", str);


}