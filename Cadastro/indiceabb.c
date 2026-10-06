// Gera árvore binária de busca com índice para arquivo CSV
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"
#include "util.h"

void insereNo(IndiceABB **raiz, RegIndice reg){
    IndiceABB *novoNo;
    IndiceABB *ptr;

    ptr = *raiz;
    if(ptr!=NULL) {  // tem um nó
        if( ! strcmp( ptr->registro.nome, reg.nome )){ //nomes iguais
            printf("ERRO - Nome existente\n");
            return;
        }
    }

    if(ptr==NULL){
            novoNo = malloc(sizeof(IndiceABB));
            if(!novoNo) {
                printf("ERRO DE ALOCAÇÃO DE MEMÓRIA - ENCERRANDO\n");
                exit(-1);
            }
            novoNo->fd=NULL;
            novoNo->fe=NULL;
            novoNo->registro.avanco = reg.avanco;
            strcpy(novoNo->registro.nome,reg.nome);
        *raiz = novoNo;
        return;
    }
    if( strcmp(reg.nome, ptr->registro.nome)>0 ) {
        insereNo( &(ptr->fd), reg);
    }
    else
        insereNo( &(ptr->fe), reg);
}


int main(){
    IndiceABB *raiz=NULL;
    RegIndice regind;

    FILE *fp;

    fp = fopen("cadastro.ind", "r");
    if(!fp) {
        printf("ERRO DE ABERTURA DE ÍNDICE\n");
        exit(-1);
    }

    while( !feof(fp) ) {
        fread( &regind, sizeof(RegIndice), 1, fp);
        insereNo( &raiz, regind);
    }
    printf("FIM\n");


}