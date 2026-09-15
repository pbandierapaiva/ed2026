// Procura nome usando arquivo de índice

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"
#include "util.h"

int main(int argc, char **argv) {
    Registro reg;
    RegIndice regind;

    FILE *fp, *indfp;
    char area[MAXLIN];
    char query[100];

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
        fread( &regind, sizeof(RegIndice), 1, indfp );
        if( strstr(regind.nome, query) ) {
            fseek( fp, regind.avanco, SEEK_SET );
            fgets(area, MAXLIN, fp);
            leRegistro(area, &reg);
            imprimeRegistro(&reg);
        }
    }
}