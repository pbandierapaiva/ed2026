// Cria arquivo de índice de Cadastro.csv


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"
#include "util.h"



int main() {
    RegIndice regind;
    Registro reg;

    FILE *fp, *indfp;
    char area[MAXLIN];

    fp = fopen("/home/pub/ed/Cadastro.csv", "r");
    indfp = fopen("cadastro.ind","w");
    if(fp==NULL || indfp==NULL) {
        printf("Erro de abertura de arquivo.\n");
        exit(-1);
    }
    printf("Criando arquivo de índice.\n");
    while( !feof(fp) ) {
        regind.avanco = ftell(fp);

        fgets(area, MAXLIN, fp);
        leRegistro(area, &reg);
        strcpy(regind.nome, reg.nome);
        fwrite(&regind, sizeof(regind), 1, indfp);
    }

    fclose(indfp);
    fclose(fp);
}