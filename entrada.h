#ifndef ENTRADA_H
#define ENTRADA_H
#include "ListaOcorrencia.h"

typedef struct 
{
    int qtd_arq;
    char nomes[100][100];
}ListaArquivos;

typedef struct 
{
    char nome[100];
    ListaOcorrencias *ocorrencia;
}PalavraInd;

PalavraInd v[1000];
int total_p;

void IniciaPalavra (PalavraInd *p);
ListaArquivos leitura_arq(char *arq);
void Insere(PalavraInd *pal);
int insereOuAtualizaOcorrencia(ListaOcorrencias *lista, int idDoc);
void InserePalavraIndice(const char *palavra_texto, int idDoc);
void token_palavras(PalavraInd *pal);
void ler_pocs(ListaArquivos *lista);
void ImprimeIndiceInvertido();

#endif