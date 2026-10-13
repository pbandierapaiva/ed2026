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

No *busca(No *r, int v) {
    if(r==NULL) // sub-árvore vazia
        return NULL;
    if( v == r->valor )
        return r;
    if( v < r->valor ) 
        return busca(r->fe, v);
    return busca(r->fd, v);
}

int altura(No *r){
    int altEsq, altDir;

    if(r==NULL) return 0;
    altEsq = altura(r->fe);
    altDir = altura(r->fd);
    if(altEsq>altDir)
        return altEsq + 1;
    else
        return altDir + 1;
}

void rotacaoEsq(No **raiz) {
    No *p, *z;
    p = *raiz;
    z = p->fd;
    p->fd = z->fe;
    z->fe = p;
    *raiz = z;
}

void rotacaoDir(No **raiz) {
    No *p, *u;
    p = *raiz;
    u = p->fe;
    p->fe = u->fd;
    u->fd = p;
    *raiz = u;
}

void rotacaoDDir(No **raiz){
    No *p;

    p = *raiz;

    rotacaoEsq( &(p->fe) );
    rotacaoDir( raiz );
}

void rotacaoDEsq(No **raiz){
    No *p;

    p = *raiz;

    rotacaoDir( &(p->fd) );
    rotacaoEsq( raiz );
}

int fb(No *r){
    return altura(r->fd) - altura(r->fe);
}

int checaAVL(No *r){
    int fatorBal;
    fatorBal = fb(r);
    if( fatorBal>1 || fatorBal<-1)
        return 0;
    if( checaAVL(r->fd) && checaAVL(r->fe) )
        return 1;
    return 0;
}


int main() {
    No *raiz=NULL;

    insereNo(&raiz, 10);
    insereNo(&raiz, 5);
    insereNo(&raiz, 7);
    // insereNo(&raiz, 40);
    // insereNo(&raiz, 50);
    // insereNo(&raiz, 60);

    printf("Altura: %d\n", altura(raiz));
    rotacaoDDir( &raiz );
    printf("Altura: %d\n", altura(raiz));
  

/*
    printf("É AVL: %d ", checaAVL(raiz) );
    printf("Altura: %d\n", altura(raiz));

    rotacaoEsq( &(raiz->fd->fd->fd) );
    rotacaoEsq(&raiz);
    
    printf("É AVL: %d ", checaAVL(raiz) );
    printf("Altura: %d\n", altura(raiz));   
    
    rotacaoEsq(&(raiz->fd));
    printf("É AVL: %d ", checaAVL(raiz) );
    printf("Altura: %d\n", altura(raiz));

    imprimeEmOrdem(raiz);

    printf("\nAnti em-ordem:\n");
    imprimeAntiEmOrdem(raiz);

    printf("\nPré-ordem:\n");
    imprimePreOrdem(raiz);
    printf("\nPós-ordem:\n");
    imprimePosOrdem(raiz);

    printf("\nNível:\n");
    imprimeNivel(raiz);

    No *p = busca(raiz,40);
    if(p) printf("Valor: %d\n", p->valor);
*/
}