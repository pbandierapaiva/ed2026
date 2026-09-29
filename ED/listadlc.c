// Lista circular duplamente ligada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NO {
    int valor;
    struct NO *proximo;
    struct NO *anterior;
} ListaDLCircular;

void insere( ListaDLCircular **lista, int valor ) {
    ListaDLCircular *novo;
    ListaDLCircular *ptr, *paux;

    // criei um novo nó
    novo = malloc( sizeof(ListaDLCircular) );
    if(!novo) { // novo é NULL
        printf("Erro de alocação.\n");
        exit(-1);    
    }
    novo->valor = valor;
    novo->proximo = NULL;
    novo->anterior = NULL;

    ptr = *lista;
    if(ptr==NULL) { // lista vazia
        novo->proximo = novo;
        novo->anterior = novo;
        *lista = novo;
        return;
    }

    novo->proximo = ptr;
    novo->anterior = ptr->anterior;
    ptr->anterior->proximo = novo;
    ptr->anterior = novo;
    *lista = novo;
}

void imprime(ListaDLCircular *lista) {
    ListaDLCircular *ptr = lista;
    ListaDLCircular *paux = lista;

    if(ptr==NULL) return;
    do {
        printf("%d\n", ptr->valor);
        ptr = ptr->proximo;
    } while(ptr!=paux);
}

void imprime_reverso(ListaDLCircular *lista) {
    ListaDLCircular *ptr = lista;
    ListaDLCircular *paux = lista;

    if(ptr==NULL) return;

    // imprime de trás para frente
    do {
        printf("%d\n", ptr->valor);
        ptr = ptr->anterior;
    } while(ptr!=paux);
}


int main() {
    ListaDLCircular *l=NULL;

    insere(&l, 10);
    insere(&l, 20);
    insere(&l, 30);
    insere(&l, 40);
    insere(&l, 50);

    imprime(l);

    printf("\nImprimindo reverso:\n");
    imprime_reverso(l);


}