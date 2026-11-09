// Exemplo de implementação de função de hash de Horne

#include <stdio.h>
#include <stdlib.h>

#define M 101


unsigned hash_horner(char *s, int m) {
    unsigned long h=0;

    for(; *s!='\0'; s++)
        h = ( h*31 + (unsigned char)*s )%m;
    return h;
}

int main() {
    char nome[100];
    

    while(1) {
        printf("\nEntre com string: ");
        fgets(nome, 100, stdin);
        printf("Hash: %d\n", hash_horner(nome, M));
    }

}
