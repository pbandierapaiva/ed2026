// Procura nome usando arquivo de índice

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"
#include "util.h"

#define TAMBUFFER  10000

int main(int argc, char **argv) {
    Registro reg;
    RegIndice regind[TAMBUFFER];

    FILE *fp, *indfp;
    char area[MAXLIN];
    char query[100];

    int reglidos=0;

    fp = fopen("/home/pub/ed/Cadastro.csv", "r");
    indfp = fopen("cadastro.ind","r");
    if(fp==NULL || indfp==NULL) {
        printf("Erro de abertura de arquivo.\n");
        exit(-1);
    }

    if(argc>1)
        strcpy(query, argv[1]);
    else {
        printf("Entre com parte do nome: ");
        scanf("%s", query);
    }
    convStr(query);
    
    while( !feof(indfp) ) {
        reglidos = fread( regind, sizeof(RegIndice), TAMBUFFER, indfp);
        for(int i=0; i<reglidos; i++) {

            if( strstr(regind[i].nome, query) ) {
                fseek( fp, regind[i].avanco, SEEK_SET );
                fgets(area, MAXLIN, fp);
                leRegistro(area, &reg);
                imprimeRegistro(&reg);
            }
        }
    }
}