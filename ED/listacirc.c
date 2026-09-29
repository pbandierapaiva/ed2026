// Lista circular implementada usando lista simplesmente ligada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NO {
    int valor;
    struct NO *proximo;
} ListaCirc;

void insere(ListaCirc **l, int valor ) {
    ListaCirc *novo;
    ListaCirc *ptr;

    novo = malloc( sizeof(ListaCirc) );
    if(!novo) { // novo é NULL
        printf("Erro de alocação.\n");
        exit(-1);    
    }
    novo->valor = valor;
    novo->proximo = NULL;

    if(*l==NULL) {
        *l = novo;
        novo->proximo = novo; // circular
        return;
    }
    ptr = *l;
    while( ptr->proximo != *l ) 
        ptr = ptr->proximo;
    ptr->proximo = novo;
    novo->proximo = *l; // circular
}

int proximo(ListaCirc **l ) {
    ListaCirc *p;
    int val;

    if(*l == NULL ) return -99999;
    p = *l;
    *l = p->proximo;

    val = p->valor;
    return val;
}


int main() {

    ListaCirc *l = NULL;

    insere(&l, 10);
    insere(&l, 20);
    insere(&l, 30);
    insere(&l, 40);

    for(int i=0; i<10; i++) {
        printf("%d\n", proximo(&l));
    }


}