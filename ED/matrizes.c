// Exemplo de uso de matrizes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSEQ  10000
#define MATCH       2
#define MISMATCH    0
#define GAP         -1

typedef struct {
    char *matriz;
    int nlin, ncol;
    char seq1[MAXSEQ], seq2[MAXSEQ];
} Matriz;

void checadim(Matriz m,int l, int c){
    if(l>=m.nlin || c>=m.ncol) {
        printf("Erro de índice\n");
        exit(-1);
    }
}

char get(Matriz m, int l, int c){
    checadim(m,l,c);
    if(l<0||c<0) return 0;
    return m.matriz[l*m.ncol + c];
}

char set(Matriz m, int l, int c, char valor){
    checadim(m,l,c);
    m.matriz[l*m.ncol + c] = valor;
}

void aloca(Matriz *m, int linhas, int colunas) {
    m->nlin = linhas;
    m->ncol = colunas;
    m->matriz = malloc(m->nlin * m->ncol * sizeof(char));
    if(!m->matriz) {
        printf("ERRO de alocação de memória\n");
        exit(-1);
    }
}

void imprime(Matriz m){
    printf("\n  %s", m.seq2);
    for(int l=0; l<m.nlin; l++) {
        printf("\n%c:", m.seq1[l]);
        for(int c=0; c<m.ncol; c++){
            printf("%d", get(m,l,c));
        }
    }
    printf("\n");
}

void criaMatSimilaridade(Matriz *mat) {
    aloca(mat, strlen(mat->seq1), strlen(mat->seq2));
    for(int l=0; l<mat->nlin; l++) {
        for(int c=0; c<mat->ncol; c++){
            if( mat->seq1[l] == mat->seq2[c] )
                set(*mat, l, c, 1);
            else
                set(*mat, l, c, 0);
        }
    }
}
int w(Matriz m, int i, int j) {
    if(m.seq1[i]==m.seq2[j])
        return MATCH;
    return MISMATCH;
}

void criaMatSW(Matriz *mat) {
    char caso1, caso2, caso3;
    char max;

    aloca(mat, strlen(mat->seq1), strlen(mat->seq2));

    for(int l=0; l<mat->nlin; l++) {
        for(int c=0; c<mat->ncol; c++){
            max = 0;
            //
            caso1 = get(*mat, l-1, c-1)+w(*mat,l,c);
            caso2 = get(*mat, l-1, c)+GAP;
            caso3 = get(*mat, l, c-1)+GAP;
            if(caso1>max) max=caso1;
            if(caso2>max) max=caso2;
            if(caso3>max) max=caso3;
            set(*mat, l, c, max );
        }
    }
}



int main(){
    Matriz mat;

    char *p;

    printf("Entre s1: ");
    fgets(mat.seq1, MAXSEQ, stdin);
    printf("Entre s1: ");    
    fgets(mat.seq2, MAXSEQ, stdin);
    for(p=mat.seq1; *p!='\n';p++);
    *p='\0';
    for(p=mat.seq2; *p!='\n';p++);
    *p='\0';
    criaMatSW(&mat);

    imprime(mat);
}