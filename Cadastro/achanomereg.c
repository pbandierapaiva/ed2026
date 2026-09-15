// Trabalhando com arquivos - le Cadastro.csv 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"
#include "util.h"



int main(int argc, char **argv) {
    Registro reg;

    FILE *fp;

    char area[MAXLIN];
    char query[100];

    char *p;

    if(argc>1)
        strcpy(query, argv[1]);
    else {
        printf("Entre com parte do nome: ");
        scanf("%s", query);
    }
    convStr(query);

    fp = fopen("/home/pub/ed/Cadastro.csv", "r");
    if(fp==NULL) {
        printf("Erro de abertura de arquivo.\n");
        exit(-1);
    }



    while( !feof(fp) ) {
        fgets(area, MAXLIN, fp);

        p = pegacampo(area, NOME);
        convStr(p);
        if( strstr(p, query) ) {
            leRegistro(area, &reg);
            imprimeRegistro(&reg);
        }

    }
}

