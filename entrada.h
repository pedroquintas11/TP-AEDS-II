#ifndef ENTRADA_H
#define ENTRADA_H

typedef struct 
{
    int qtd_arq;
    char nomes[100][100];
}ListaArquivos;

typedef struct 
{
    int id, qtde;
    char nome[20];
}Palavras;

Palavras v[10000];
int total_p;

ListaArquivos leitura_arq(char *arq);
void Insere(Palavras *pal);
void token_palavras(Palavras *pal);
void ler_pocs(ListaArquivos *lista);

#endif