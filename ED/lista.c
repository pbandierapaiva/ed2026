// Exemplo de lista simplesmente ligada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NO {
    float valor;
    struct NO *proximo;
} No;

void insereValor(No **l, float valor) {
    No *novo;

    novo = malloc( sizeof(No) );
    if(!novo) { // novo é NULL
        printf("Erro de alocação.\n");
        exit(-1);    
    }

    novo->valor = valor;
    novo->proximo = *l;
    *l = novo;
}

void insereValorNoFinal(No **l, float valor) {
    No *novo;
    No *ptr;

    ptr = *l;

    novo = malloc( sizeof(No) );
    if(!novo) { // novo é NULL
        printf("Erro de alocação.\n");
        exit(-1);    
    }

    novo->valor = valor;
    novo->proximo= NULL;   

    if(ptr==NULL){  // raiz 'NULL'
        *l = novo;
        return;
    }

    while( ptr->proximo!=NULL )
        ptr = ptr->proximo;
    
    ptr->proximo = novo;
}

void removeNo( No **raiz, No *remover) {
    No *ptr, **ptrant;

    ptr = *raiz;
    if(!ptr){
        return;
    }
    ptrant = raiz;

    while( ptr != remover && ptr) {
        ptrant = &(ptr->proximo);
        ptr = ptr->proximo;
    }

    if(!ptr) return; // não achou

    *ptrant = ptr->proximo;
    free(ptr);
}
No *pegaIndice(No *r, int i){
    if(r==NULL) return NULL;

    while(i && r!=NULL) {
        r = r->proximo;
        i--;
    }
    return r;
}

int len(No *p){
    int conta = 0;

    if(p==NULL) return 0;
    do {
        conta++;
        p= p->proximo;
    } while(p);
    return conta;
}


void imprimeLista(No *l) {
    No *ptr;
    ptr = l;
    while(ptr) {
        printf("%f\n", ptr->valor);
        ptr = ptr->proximo;
    }
}

void imprimeListaInv(No *l) {
    No *p;

    for(int i=len(l)-1; i>=0; i--){
        p = pegaIndice(l, i);
        printf("%f\n", p->valor);
    }

}


int main() {
    // Lista vazia
    No *raiz=NULL;
    No *p;

    insereValorNoFinal( &raiz, 10 );
    insereValorNoFinal( &raiz, 20 );
    insereValorNoFinal( &raiz, 30 );

    removeNo(&raiz, raiz->proximo);

    insereValorNoFinal( &raiz, 40 );
    insereValorNoFinal( &raiz, 50 );

    insereValorNoFinal( &raiz, 60 );

    removeNo(&raiz, raiz);

    p = raiz;
    if(p==NULL) return 0;
    while(p->proximo!=NULL)
        p = p->proximo;

    removeNo(&raiz, p);

    printf("\nTamanho da lista: %d\n", len(raiz));
    imprimeLista(raiz);    
    printf("\nInvertida:\n");
    
    imprimeListaInv(raiz);

}