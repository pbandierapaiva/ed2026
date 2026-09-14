// Trabalhando com arquivos - le registro completo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"
#include "util.h"

#define MAXLIN 1000


int main(){
    FILE *fp;
    char area[MAXLIN];

    Registro reg;

    fp = fopen("/home/pub/ed/Cadastro.csv", "r");
    if(fp==NULL) {
        printf("Erro de abertura de arquivo.\n");
        exit(-1);
    }



    while( !feof(fp) ) {

        fgets(area, MAXLIN, fp);
        
        strcpy(reg.id, pegacampo(area, Id_SERVIDOR_PORTAL));
        strcpy(reg.nome, pegacampo(area, NOME));
        strcpy(reg.matricula, pegacampo(area, MATRICULA));
        strcpy(reg.descricao, pegacampo(area, DESCRICAO_CARGO));
        strcpy(reg.classe, pegacampo(area, CLASSE_CARGO));
        strcpy(reg.uorg, pegacampo(area, UORG_LOTACAO));
        strcpy(reg.org, pegacampo(area, ORG_LOTACAO));

        printf("ID %s - ", reg.id);
        printf("Nome:\t%s\n", reg.nome);
        printf("Matr.:\t%s\n", reg.matricula);
        printf("Descr:\t%s\n", reg.descricao);
        printf("%s\n", reg.classe);
        printf("%s\n", reg.uorg);
        printf("%s\n\n---", reg.org);

    }


}






