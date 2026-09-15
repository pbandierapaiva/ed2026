// Funções utilizadas por programas de cadastro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cadastro.h"
#include "util.h"

void leRegistro(char *linha, Registro *regptr) {
        strcpy(regptr->id, pegacampo(linha, Id_SERVIDOR_PORTAL));
        strcpy(regptr->nome, pegacampo(linha, NOME));
        strcpy(regptr->matricula, pegacampo(linha, MATRICULA));
        strcpy(regptr->descricao, pegacampo(linha, DESCRICAO_CARGO));
        strcpy(regptr->classe, pegacampo(linha, CLASSE_CARGO));
        strcpy(regptr->uorg, pegacampo(linha, UORG_LOTACAO));
        strcpy(regptr->org, pegacampo(linha, ORG_LOTACAO));
}

void imprimeRegistro(Registro *regptr){ 
        printf("---\nID %s - ", regptr->id);
        printf("    Nome:\t%s\n", regptr->nome);
        printf("Matrptr->:\t%s\n", regptr->matricula);
        printf("Descr:\t%s\n", regptr->descricao);
        printf("%s\n", regptr->classe);
        printf("%s\n", regptr->uorg);
        printf("%s---\n\n", regptr->org);
}

void convStr(char *p){
    if(p==NULL) return;
    while(*p) {
        *p = toupper(*p);
        p++;
    }
}


char *pegacampo(char *a, int i){
    char *ptr, *aux;
    int ncpo=0;
    aux = a;

    if(*aux!='"') {
        printf("ERRO - não sei o que aconteceu...\n");
        exit(-1);
    }

    while(1){
        aux++;
        ptr = aux;
        while(*aux!='"' && *aux!='\0') aux++;
        *aux='\0';
        if(ncpo==i)
            return ptr;
        aux++;
        while(*aux!='"' && *aux!='\0') aux++;
        if(*aux=='\0') return NULL;
        ncpo++;
    }
}
