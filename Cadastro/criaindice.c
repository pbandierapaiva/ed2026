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
    char *p;

    printf("Tamanho do RegIndice %ld\n\n", sizeof(RegIndice));

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
        
        p = regind.nome;
        for(int i =0;i<200;i++) p[i]=0;

        strcpy(regind.nome, reg.nome);
        // strcpy(regind.nome, "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
        fwrite(&regind, sizeof(RegIndice), 1, indfp);
    }

    fclose(indfp);
    fclose(fp);
}