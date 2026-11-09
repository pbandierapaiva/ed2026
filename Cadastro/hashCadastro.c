// Trabalhando com Cadastro.csv usando hash

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cadastro.h"
#include "util.h"

#define M 101


unsigned hash_horner(char *s, int m) {
    unsigned long h=0;

    for(; *s!='\0'; s++)
        h = ( h*31 + (unsigned char)*s )%m;
    return h;
}

int main() {
    int vetor[M];
    FILE *fp;
    char *p;
    char area[MAXLIN];

    for(int i=0;i<M;i++) vetor[i]=0;

    fp = fopen("/home/pub/ed/Cadastro.csv", "r");
    if(fp==NULL) {
        printf("Erro de abertura de arquivo.\n");
        exit(-1);
    }

    while( !feof(fp) ) {
        fgets(area, MAXLIN, fp);
        p = pegacampo(area, NOME);

        if(strcmp(p,"Sigiloso")==0) continue;
        vetor[ hash_horner(p, M) ]++ ;
        // if( hash_horner(p, M)==48 ) printf("%s\n",p);
    }

    for(int i=0;i<M;i++) printf("%d %d\n", i, vetor[i]);

}

