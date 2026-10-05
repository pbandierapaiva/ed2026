// Exemplo de árvore binária de busca

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NO {
    int valor;
    struct NO *fe, *fd;
} No;

int insereNo(No **r, int val){
    No *novo;
    No *ptr;

    ptr = *r;
    if(ptr!=NULL && val==ptr->valor) { //NÃO PODE VALORES REPETIDOS EM abb
        printf("Valores repetidos, desconsiderando\n");
        return(1);
    }
    novo = malloc( sizeof(No) );
    novo->valor = val;
    novo->fe = NULL;
    novo->fd = NULL;
    if(!novo) { // novo é NULL
        printf("Erro de alocação.\n");
        exit(-1);    
    }  

    if(*r ==NULL){
        *r = novo;
        return 0;
    }



    if( ptr->valor > val )  //val é menor que o valor no Nó
        insereNo( &(ptr->fe), val );
    else 
        insereNo( &(ptr->fd), val );
    return 0;
}

void imprimeEmOrdem(No *r) {
    if(r == NULL) // árvore vazia
        return;
    
    imprimeEmOrdem( r->fe );
    printf("%d\n", r->valor);
    imprimeEmOrdem( r->fd );
}

void imprimeAntiEmOrdem(No *r) {
    if(r == NULL) // árvore vazia
        return;
    imprimeAntiEmOrdem( r->fd );
    printf("%d\n", r->valor);
    imprimeAntiEmOrdem( r->fe );
}

void imprimePreOrdem(No *r){
    if(r == NULL) // árvore vazia
        return;
    printf("%d\n", r->valor);
    imprimePreOrdem( r->fe );
    imprimePreOrdem( r->fd );
}

void imprimePosOrdem(No *r){
    if(r == NULL) // árvore vazia
        return;
    imprimePosOrdem( r->fe );
    imprimePosOrdem( r->fd );
    printf("%d\n", r->valor);
}

//// Estrutura de dados para a fila de nós da árvore
typedef struct FILANO {
    No *p;
    struct FILANO *proximo;
} Fila;

void insereNoFila(Fila **f, No *p) {
    Fila *novo;
    Fila *ptr;

    novo = malloc( sizeof(Fila) );
    if(!novo) { // novo é NULL
        printf("Erro de alocação.\n");
        exit(-1);    
    }
    novo->p = p;
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

No *removeNoFila(Fila **f ) {
    Fila *p;
    No *val;

    if(*f == NULL ) return NULL;
    p = *f;
    *f = p->proximo;

    val = p->p;
    free(p);
    return val;
}
////

void imprimeNivel(No *r){
    if(r == NULL) // árvore vazia
        return;  
    
    Fila *fila=NULL;
    insereNoFila(&fila, r);
    while(fila!=NULL){
        No *p = removeNoFila(&fila);
        printf("%d\n", p->valor);
        if(p->fe!=NULL)
            insereNoFila(&fila, p->fe);
        if(p->fd!=NULL)
            insereNoFila(&fila, p->fd);
    }
}

int main() {
    No *raiz=NULL;

    insereNo(&raiz, 30);
    insereNo(&raiz, 60);
    insereNo(&raiz, 70);
    insereNo(&raiz, 20);
    insereNo(&raiz, 40);
    insereNo(&raiz, 50);

    imprimeEmOrdem(raiz);

    printf("\nAnti em-ordem:\n");
    imprimeAntiEmOrdem(raiz);

    printf("\nPré-ordem:\n");
    imprimePreOrdem(raiz);
    printf("\nPós-ordem:\n");
    imprimePosOrdem(raiz);

    printf("\nNível:\n");
    imprimeNivel(raiz);
}