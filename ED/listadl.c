// Lista duplamente ligada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NO {
    int valor;
    struct NO *proximo;
    struct NO *anterior;
} ListaDL;

void insere( ListaDL **lista, int valor ) {
    ListaDL *novo;
    ListaDL *ptr;

    // criei um novo nó
    novo = malloc( sizeof(ListaDL) );
    if(!novo) { // novo é NULL
        printf("Erro de alocação.\n");
        exit(-1);    
    }
    novo->valor = valor;
    novo->proximo = NULL;
    novo->anterior = NULL;

    ptr = *lista;
    if(ptr==NULL) { // lista vazia
        *lista = novo;
        return;
    }

    novo->proximo = ptr;
    ptr->anterior = novo;
    *lista = novo;
}

void imprime(ListaDL *lista) {
    ListaDL *ptr = lista;
    while(ptr) {
        printf("%d\n", ptr->valor);
        ptr = ptr->proximo;
    }
}

void imprime_reverso(ListaDL *lista) {
    ListaDL *ptr = lista;
    if(ptr==NULL) return;

    // vai até o final da lista
    while(ptr->proximo) 
        ptr = ptr->proximo;

    // imprime de trás para frente
    while(ptr) {
        printf("%d\n", ptr->valor);
        ptr = ptr->anterior;
    }
}


int main() {
    ListaDL *l=NULL;

    insere(&l, 10);
    insere(&l, 20);
    insere(&l, 30);
    insere(&l, 40);
    insere(&l, 50);

    imprime(l);

    printf("\nImprimindo reverso:\n");
    imprime_reverso(l);


}