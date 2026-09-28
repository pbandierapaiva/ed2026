// Exemplo de lista simplesmente ligada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct FILA {
    float valor;
    struct FILA *proximo;
} Fila;

void coloca(Fila **f, int valor ) {
    Fila *novo;
    Fila *ptr;

    novo = malloc( sizeof(Fila) );
    if(!novo) { // novo é NULL
        printf("Erro de alocação.\n");
        exit(-1);    
    }
    novo->valor = valor;
    novo->proximo = NULL;

    if(*f==NULL) {
        *f = novo;
        return;
    }
    ptr = *f;
    while( ptr->proximo != NULL ) 
        ptr = ptr->proximo;
    ptr->proximo = novo;
}

int retira(Fila **f ) {
    Fila *p;
    int val;

    if(*f == NULL ) return -99999;
    p = *f;
    *f = p->proximo;

    val = p->valor;
    free(p);
    return val;
}


int main(){

    Fila *fila; //fila vazia

    fila=NULL;
    coloca(&fila, 10);
    coloca(&fila, 20);
    coloca(&fila, 30);
    coloca(&fila, 40);

    printf("Retirado: %d\n", retira(&fila));
    printf("Retirado: %d\n", retira(&fila));
    printf("Retirado: %d\n", retira(&fila));

    coloca(&fila, 50);
    coloca(&fila, 60);

    while(fila)
        printf("Retirado: %d\n", retira(&fila));
}

