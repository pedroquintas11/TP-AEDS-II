#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "entrada.h"
int total_p = 0;

ListaArquivos leitura_arq(char *arq) {
    int i;
    ListaArquivos lista;
    lista.qtd_arq = 0;

    FILE *entrada = fopen(arq, "r");
    if (!entrada) {
        printf("Erro ao abrir os arquivo(s).\n");
        exit(1);
    }

    fscanf(entrada, "%d", &lista.qtd_arq);

    for (i=0; i<lista.qtd_arq; i++) {
        fscanf(entrada, "%s", lista.nomes[i]);
    }
    fclose(entrada);
    return(lista);
}

void Insere(Palavras *pal) {
    int i;
    for (i=0; i<total_p; i++) {
        if (strcmp(v[i].nome, pal->nome) == 0 && v[i].id == pal->id) {
            v[i].qtde++;
            return;
        }
    }
    strcpy(v[total_p].nome, pal->nome);
    v[total_p].id = pal->id;
    v[total_p].qtde = 1;
    total_p++;
}

void token_palavras(Palavras *pal){
    int i, j = 0;
    char c;
    for (i = 0; pal->nome[i] != '\0'; i++) {
        c = pal->nome[i];
        if (c >= 'A' && c <= 'Z') c += 32; // minúscula
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            pal->nome[j++] = c;
        }
    }
    pal->nome[j] = '\0';
}

void ler_pocs(ListaArquivos *lista) {
    int i;
    for (i=0; i<lista->qtd_arq; i++) {
        FILE *arq = fopen(lista->nomes[i], "r");
        Palavras pal;
        pal.id = i + 1;
        while (fscanf(arq, "%s", pal.nome) == 1) {
            token_palavras(&pal);
            Insere(&pal); // tem que adptar para inserir na hash e na patricia
        }
    }
}