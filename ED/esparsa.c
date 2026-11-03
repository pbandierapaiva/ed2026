// Exemplo de matriz esparsa

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT 0

typedef struct tempNo {
    int valor;
    int coluna;
    struct tempNo *proximo;
} NO;

typedef NO* PONT;

typedef struct {
    PONT *A;
    int linhas;
    int colunas;
} MATRIZ;

MATRIZ *novaMatriz(int l, int c) {
    MATRIZ *m;

    m = malloc(sizeof(MATRIZ));
    if(!m) {
        printf("\nERRO de alocação!\n");
        exit(-1);
    }

    m->linhas = l;
    m->colunas = c;
    m->A = malloc( m->linhas * sizeof(PONT));
    for(int i=0; i<m->linhas; i++) m->A[i]=NULL;
    return m;
}

int getM(MATRIZ *m, int l, int c) {
    PONT no;

    if( l > m->linhas || c > m->colunas) {
        printf("\nERRO de indíce\n");
        exit(-1);
    }
    no = m->A[l];
    while( no != NULL ) {
        if( no->coluna==c ) return no->valor;
        if( no->coluna > c ) break;
        no = no->proximo;
    }
    return DEFAULT;
}

void setM(MATRIZ *m, int l, int c, int v) {
    PONT no, *noAnt, novoNo;
   
    if( l > m->linhas || c > m->colunas) {
        printf("\nERRO de indíce\n");
        exit(-1);
    }

    novoNo = malloc(sizeof(NO));
    if(!novoNo) {
        printf("\nERRO de alocação!\n");
        exit(-1);
    }
    novoNo->proximo=NULL;
    novoNo->coluna=c;
    novoNo->valor=v;

    no = m->A[l];
    noAnt = &(m->A[l]);
    while( no!=NULL && no->coluna < novoNo->coluna ) {
        no = no->proximo;
        noAnt = &(no->proximo);
    }
    if(no==NULL) {
        *noAnt = novoNo;
        return;
    }
    if(no->coluna > novoNo->coluna) {
        novoNo->proximo = no;
        *noAnt = novoNo;
        return;
    }
    // no->coluna == novoNo->coluna
    no->valor = v;
    free(novoNo);
}


int main(){
    MATRIZ *mat;

    mat = novaMatriz(1000, 3000000);

    setM(mat, 100, 100000, 10);
    setM(mat, 100, 100010, 20);
    setM(mat, 100, 100005, 30);
    setM(mat, 100, 80000, 40);

    printf("Valor em 50,10: %d\n", getM(mat, 50, 10) );
    printf("Valor em 100,100000: %d\n", getM(mat, 100, 100000) );
    printf("Valor em 100,100010: %d\n", getM(mat, 100, 100010) );
    printf("Valor em 100,100005: %d\n", getM(mat, 100, 100005) );
    printf("Valor em 100,80000: %d\n", getM(mat, 100, 80000) );
}



