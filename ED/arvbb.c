// Exemplo de árvore binária de busca

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NO {
    int valor;
    struct NO *fe, *fd;
} No;

int modulo(int v){
    if(v>=0) return v;
    return -v;
}

int insereNo(No **r, int val){
    No *novo;
    No *ptr;

    ptr = *r;
    if(ptr!=NULL && val==ptr->valor) { //NÃO PODE VALORES REPETIDOS EM abb
        printf("Valores repetidos, desconsiderando\n");
        return(1);
    }

    if(*r ==NULL){
        novo = malloc( sizeof(No) );
        novo->valor = val;
        novo->fe = NULL;
        novo->fd = NULL;
        if(!novo) { // novo é NULL
            printf("Erro de alocação.\n");
            exit(-1);    
        }  
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

//// Estrutura de dados para a fila de nós da árvore ////
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
////////////////////////////////////////////////////////

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
    if(r==NULL) return 1;
    fatorBal = fb(r);
    if( fatorBal>1 || fatorBal<-1)
        return 0;
    if( checaAVL(r->fd) && checaAVL(r->fe) )
        return 1;
    return 0;
}

void fazAVL(No **r){
    No *ptr;
    int fatbal;

    ptr = *r;
    if(ptr==NULL) return;

    if( checaAVL(ptr) ) return;

    fatbal =fb(ptr);

    if( modulo(fatbal)>1 ) {
        if(fatbal>0) {   // FB = +2
            if(fb(ptr->fd)<0)
                rotacaoDEsq( &(ptr->fd) );
            else
                rotacaoEsq( &(ptr->fd) );
        }
        else {
             if(fb(ptr->fe)<0)
                rotacaoDDir( &(ptr->fe) );
            else
                rotacaoDir( &(ptr->fe) );           

        }
    }
    fazAVL( &(ptr->fe) );
    fazAVL( &(ptr->fd) );
}

int insereNoAVL(No **r, int val){
    No *novo;
    No *ptr;
    int valfb;

    ptr = *r;
    if(ptr!=NULL && val==ptr->valor) { //NÃO PODE VALORES REPETIDOS EM abb
        printf("Valores repetidos, desconsiderando\n");
        return(1);
    }
    if(*r ==NULL){
        novo = malloc( sizeof(No) );
        novo->valor = val;
        novo->fe = NULL;
        novo->fd = NULL;
        if(!novo) { // novo é NULL
            printf("Erro de alocação.\n");
            exit(-1);    
        }  
        *r = novo;
        return 0;
    }
    if( ptr->valor > val )  //val é menor que o valor no Nó
        insereNoAVL( &(ptr->fe), val );
    else 
        insereNoAVL( &(ptr->fd), val );
    
    valfb = fb(*r);
    if( modulo( valfb ) >1 ) {
        if(valfb>0) {  // +2
            if( fb(ptr->fd) > 0 )
                rotacaoEsq(r);
            else
                rotacaoDEsq(r);
        }
        else {
            if( fb(ptr->fe) > 0 )
                rotacaoDDir(r);
            else
                rotacaoDir(r);
        }

    }
    return 0;
}

// void percorreArvInsereRaiz(No **raiz, No *arv, int valor ) {
//     if(arv==NULL) return;
//     insereNoAVL(raiz, arv->valor);
//     percorreArvInsereRaiz(raiz, &(arv->fe), valor);
//     percorreArvInsereRaiz(raiz, &(arv->fd), valor);
//     free(arv);
// }

void insereArvore(No **r, No *arv) {
    No *ptr;

    ptr=*r;

    if(!ptr) {
        *r = arv;
        return;
    }
    if( ptr->valor > arv->valor ) 
        insereArvore( &(ptr->fe), arv);
    else
        insereArvore( &(ptr->fd), arv);
}

No **achaPtrNo(No **raiz, int val){
    No *ptr;

    ptr = *raiz;
    if(!ptr) return NULL;

    if(ptr->valor==val)
        return raiz;
    if(ptr->valor < val) 
        achaPtrNo( &(ptr->fd), val);
    else
        achaPtrNo( &(ptr->fe), val); 
}

void removeNo(No **no) {
    No *ptr;

    ptr = *no;

    if(!ptr) return;

    if( !ptr->fe || !ptr->fd )   {  //
        if(!ptr->fe && !ptr->fd)
            *no = NULL;      //  NULL e NULL
        if( ptr->fe )
            *no = ptr->fe;   //  XXXX e NULL
        if( ptr->fd )
            *no = ptr->fd;   //  NULL e XXXX
    }
    else {   // ambos FE e FD estão populados
        if(fb(ptr)<0) {
            *no = ptr->fe;
            insereArvore(no, ptr->fd);
        }
        else {
            *no = ptr->fd;
            insereArvore(no, ptr->fe);
        }
    }
    free(ptr);

}

int main() {
    No *raiz=NULL;
    No *r2=NULL;

    No **ptr;
    insereNoAVL(&raiz, 10);
    insereNoAVL(&raiz, 5);
    insereNoAVL(&raiz, 16);  // *
    insereNoAVL(&raiz, 9);
    insereNoAVL(&raiz, 12);
    insereNoAVL(&raiz, 11);
    printf("Altura: %d\n", altura(raiz));

    removeNo(&raiz);
    printf("Altura: %d\n", altura(raiz));

    printf("Imprimindo - Em-ordem: \n");
    imprimeEmOrdem(raiz);

    if(checaAVL(raiz))
        printf("Árvore AVL!\n");
    else {
        printf("Árvore NÃO AVL! Corrigindo...\n");
        fazAVL(&raiz);
        if(checaAVL(raiz)){
            printf("Árvore AVL!\n");
        }
        else {
            printf("DEU PAU ===> Árvore NÃO AVL!\n");
        }
    }


    // *


    // insereNoAVL(&raiz, 1);
    // insereNoAVL(&raiz, 2);
    // insereNoAVL(&raiz, 3);  // *
    // insereNoAVL(&raiz, 4);
    // insereNoAVL(&raiz, 5);
    // insereNoAVL(&raiz, 6);
    // insereNoAVL(&raiz, 11);
    // insereNoAVL(&raiz, 12);
    // insereNoAVL(&raiz, 13);  // *
    // insereNoAVL(&raiz, 14);
    // insereNoAVL(&raiz, 15);
    // insereNoAVL(&raiz, 16);
    // // árvore r2
    // insereNoAVL(&r2, 7);
    // insereNoAVL(&r2, 8);
    // insereNoAVL(&r2, 9);
    // insereNoAVL(&r2, 10);        
    
    // insereArvore(&raiz, r2);

    // printf("Altura: %d\n", altura(raiz));
    // // imprimeNivel(raiz);
    // printf("Em ordem:\n");
    // imprimeEmOrdem(raiz);

    // ptr = achaPtrNo(&raiz, 8 );

    // if(ptr) {
    //     printf("Encontrou %d\n", (*ptr)->valor);
    //     removeNo(ptr);
    // }

    // ptr = achaPtrNo(&raiz, 12 );
    // if(ptr) {
    //     printf("Encontrou %d\n", (*ptr)->valor);
    //     removeNo(ptr);
    // }

    // imprimeEmOrdem(raiz);
    // if(checaAVL(raiz))
    //     printf("Árvore AVL!\n");
    // else 
    //     printf("Árvore NÃO AVL!\n");
        

    // printf("Altura: %d\n", altura(raiz));
    // rotacaoDDir( &raiz );
    // printf("Altura: %d\n", altura(raiz));
  

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